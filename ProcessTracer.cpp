/*
NAME
ProcessTracer

DESCRIPTION
About the simplest debugger which is useful!

COPYRIGHT
Copyright (C) 2011 by Roger Orr <rogero@howzatt.demon.co.uk>
Copyright (C) 2021 by Mehmet Ali Baykara <mehmetalibaykara@gmail.com>


This software is distributed in the hope that it will be useful, but
without WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
Permission is granted to anyone to make or distribute verbatim
copies of this software provided that the copyright notice and
this permission notice are preserved, and that the distributor
grants the recipent permission for further distribution as permitted
by this notice.
Comments and suggestions are always welcome.
Please report bugs to rogero@howzatt.demon.co.uk.
*/

#include "ProcessTracer.h"

#include <cassert>    // for assert
#include <exception>  // for std::runtime_exception
#include <ntstatus.h> // for STATUS_WX86_BREAKPOINT

using CString = std::basic_string<TCHAR>;

#ifdef _UNICODE
#define tcout wcout
#define tcerr wcerr
#else
#define tcout cout
#define tcerr cerr
#endif
#define SIZE (10)

ProcessTracer::ProcessTracer(std::string cmd) {
  _putenv("_NO_DEBUG_HEAP=1");
  this->PTraceCreateProcess(cmd);
}

/*
 * Depending on debug event code the corresponding case will be triggerd
 * Debug event code will be perform by minwinbase.h api
 * Modified function from @RogerOrr
 * Essential logic process creation is from @RogerOrr
 */

void ProcessTracer::Run() {
  bool attached = false;

  do {
    try {
      DEBUG_EVENT DebugEvent;
      DWORD continueFlag = DBG_CONTINUE;
      if (!WaitForDebugEvent(&DebugEvent, INFINITE)) {
        throw std::runtime_error("Debug loop aborted");
      }
      switch (DebugEvent.dwDebugEventCode) {
      case CREATE_PROCESS_DEBUG_EVENT:
        OnCreateProcess(DebugEvent.dwProcessId, DebugEvent.dwThreadId,
                        DebugEvent.u.CreateProcessInfo);
        break;
      case EXIT_PROCESS_DEBUG_EVENT:
        OnExitProcess(DebugEvent.dwProcessId, DebugEvent.u.ExitProcess,
                      m_isVerbose);
        break;
      case EXCEPTION_DEBUG_EVENT:
        if (!attached) {
          attached = true;
        } else if (DebugEvent.u.Exception.ExceptionRecord.ExceptionCode ==
                       STATUS_WX86_BREAKPOINT &&
                   m_isVerbose) {
          // std::cout << "WOW64 initialised"
          //           << "\n";
        } else {
          continueFlag = (DWORD)DBG_EXCEPTION_NOT_HANDLED;
        }
        break;
      default:
        // do nothing
        break;
        // if (m_isVerbose) {
        //   std::cerr << "Undefined debug event: " <<
        //   DebugEvent.dwDebugEventCode
        //             << "\n";
        // }
      }
      if (!ContinueDebugEvent(DebugEvent.dwProcessId, DebugEvent.dwThreadId,
                              continueFlag)) {
        throw std::runtime_error("Error continuing debug event");
      }

    } catch (const std::exception &e) {
      std::cerr << "[TRACER] ERROR: " << e.what() << " ... continuing\n";
      continue;
    }
  } while (!m_IsInitRunning);
}

void ProcessTracer::WriteToJSON(std::string outputPath) {
  std::ofstream f(outputPath);
  auto r = root.GetJSON();
  f << r.dump(2);
}

/*
 * @return the directory where the process triggerd by.
 */
std::string(ProcessTracer::GetCurrentDirectory)() {
  char buff[MAX_PATH];
  _getcwd(buff, MAX_PATH);
  std::string currentDir(buff);
  return currentDir;
}

/*
 * For each new process, retrieve all process information by invoking
 * corresponding methods Modified function from @RogerOrr Essential logic
 * process creation is from @RogerOrr
 */
void ProcessTracer::OnCreateProcess(
    DWORD processId, DWORD threadId,
    CREATE_PROCESS_DEBUG_INFO const &createProcess) {
  m_hProcess = createProcess.hProcess;
  threadHandles[threadId] = createProcess.hThread;
  m_engine.init(m_hProcess);
  m_engine.loadModule(createProcess.hFile, createProcess.lpBaseOfImage,
                      std::string());
  m_hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE,
                           processId);

  auto processAddress =
      m_engine.addressToString((void *)createProcess.lpStartAddress);
  GetProcessInformation(processId, processAddress);
  pids.push_back(processId);
  if (m_isVerbose)
    GetApplicationPath();

  std::string currentPath = GetCurrentDirectory();
  std::string args = GetCommandLineArgs(m_hProcess);
  Process newProcess(this->process_pid, this->parent_pid, args, currentPath);
  if (root.GetChildren().size() == 0) {
    root.InsertChild(newProcess);
  }
  root.TraverseAndInsertChild(newProcess);

  if (createProcess.hFile) {
    CloseHandle(createProcess.hFile);
  }
}
/*
 * Allows to get full path of running current application/process
 */
void ProcessTracer::GetApplicationPath() {
  TCHAR programPath[MAX_PATH];
  if (GetModuleFileNameEx(m_hProcess, NULL, programPath, MAX_PATH) == 0) {
    std::tcerr << "Failed to get path.\n";
  } else {
    std::tcout << "Application Path:  \n" << programPath << "\n";
  }
}

/*
 evaluated from
 https://stackoverflow.com/questions/7446887/get-command-line-string-of-64-bit-process-from-32-bit-process
*/
std::string ProcessTracer::GetCommandLineArgs(HANDLE handle) {
  SYSTEM_INFO system_info;
  GetNativeSystemInfo(&system_info);

  PROCESS_BASIC_INFORMATION pbi{};

  size_t nRead = 0;
  // get process information
  auto query = (_NtQueryInformationProcess)GetProcAddress(
      GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");
  DWORD err = query(handle, 0, &pbi, sizeof(pbi), NULL);
  if (err != 0) {
    throw std::runtime_error("Cannot query ntdll.dll");
  }

  // read PEB
  PEB peb;
  if (!ReadProcessMemory(handle, pbi.PebBaseAddress, &peb, sizeof(peb),
                         &nRead)) {
    throw std::runtime_error("Cannot read peb");
  }
  assert(nRead == sizeof(peb));

  // read ProcessParameters
  RTL_USER_PROCESS_PARAMETERS upp;
  if (!ReadProcessMemory(handle, peb.ProcessParameters, &upp, sizeof(upp),
                         &nRead)) {
    throw std::runtime_error("Cannot read upp");
  }
  assert(nRead == sizeof(upp));

  // read command line
  auto pCommandLine = &upp.CommandLine;
  std::vector<wchar_t> cmdLine(pCommandLine->MaximumLength, '\0');
  if (!ReadProcessMemory(handle, pCommandLine->Buffer, cmdLine.data(),
                         pCommandLine->MaximumLength, &nRead)) {
    throw std::runtime_error("Cannot read command line");
  }

  // TODO(Bohdan): read env vars also

  return ToString(cmdLine.data());
}

/*
 * Takes current process snapshot  via Windows Tool Help Library
 */
void ProcessTracer::GetProcessInformation(DWORD processId,
                                          std::string processAddress) {
  HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hProcessSnap == INVALID_HANDLE_VALUE) {
    throw std::runtime_error("CreateToolhelp32Snapshot failed");
  }

  PROCESSENTRY32 pe32;
  pe32.dwSize = sizeof(PROCESSENTRY32);

  if (!Process32First(hProcessSnap, &pe32)) {
    throw std::runtime_error("Process32First failed");
  }

  while (Process32Next(hProcessSnap, &pe32)) {
    if (pe32.th32ProcessID == processId) {
      this->parent_pid = pe32.th32ParentProcessID;
      parent.push_back(this->parent_pid);
      this->process_pid = pe32.th32ProcessID;
      if (this->m_isVerbose) {
        std::wcout << "Process ID      : " << pe32.th32ProcessID << "\n";
        std::wcout << "Process name    : " << pe32.szExeFile << "\n";
        std::wcout << "Thread counts   : " << pe32.cntThreads << "\n";
        std::wcout << "Parent ID       : " << pe32.th32ParentProcessID << "\n";
      }
    }
  }

  CloseHandle(hProcessSnap);
}

/*
 * catch exit code for terminated process
 * Modified function from @RogerOrr
 */
void ProcessTracer::OnExitProcess(DWORD processId,
                                  EXIT_PROCESS_DEBUG_INFO const &exitProcess,
                                  bool m_isVerbose) {

  if (pids.front() == processId) {
    m_IsInitRunning = true;
  }
}

/*
 * Process creating trigger with cli arguments.
 * Windows Debug API will be attached here.
 * By changing DEBUG_PROCESS, other option for Debug API could be used as needed
 * Modified function from @RogerOrr
 */
void ProcessTracer::PTraceCreateProcess(std::string cmd) {

  STARTUPINFO startupInfo = {sizeof(startupInfo)};
  startupInfo.dwFlags = STARTF_USESHOWWINDOW;
  startupInfo.wShowWindow = SW_SHOWNORMAL;
  PROCESS_INFORMATION ProcessInformation = {0};

  if (!CreateProcess(0, const_cast<TCHAR *>(cmd.data()), 0, 0, true,
                     DEBUG_PROCESS, 0, 0, &startupInfo, &ProcessInformation)) {
    std::ostringstream oss;
    oss << GetLastError();
#ifdef UNICODE
    size_t len = _tcslen(*begin) + 1;
    char *str = new char[len];
    wcstombs(str, *begin, len);
    throw std::runtime_error(std::string("No such an application to start: ") +
                             str + ": " + oss.str());
    delete str;
#else
    throw std::runtime_error(std::string("Unable to start ") + cmd + ": " +
                             oss.str());
#endif
  }
  CloseHandle(ProcessInformation.hProcess);
  CloseHandle(ProcessInformation.hThread);
}

// /*
//  * Windows specific data type conversion
//  * This case WChar to std::string
//  */
// std::string ProcessTracer::GetArgs() {
//   LPWSTR *arguments;
//   int numberArgs;
//   std::string cliArgs;
//   arguments = CommandLineToArgvW(GetCommandLineW(), &numberArgs);
//   if (NULL == arguments) {
//     throw std::runtime_error("CommandLineToArgvW failed");
//   }

//   for (int i = 1; i < numberArgs; i++) {
//     std::wstring w(arguments[i]);
//     cliArgs += ToString(w);
//   }
//   return cliArgs;
// }
