#pragma once

#ifdef _M_X64
#include <ntstatus.h>
#define WIN32_NO_STATUS
#endif // _M_X64

#include <direct.h>
#include <climits>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <windows.h>
#include <tchar.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <stdint.h>
#include <iomanip>
#include <codecvt>
#include <locale>

#include "SimpleSymbolEngine.h"
#include "NtQueries.h"
#include"Process.h"
#include "json.hpp"



#define BUFSIZE 4096


class ProcessTracer
{
private:
	HANDLE m_hProcess;
	DWORD m_parent;
	bool m_isVerbose = true;
	bool m_isEnabledInfo = false;
	bool m_isExecuting = true;
	bool m_IsInitRunning = false;
	std::map<DWORD, HANDLE> threadHandles;
	std::map <LPVOID, std::string > dllFileName;
	SimpleSymbolEngine m_engine;
	std::vector<int> pids;
	std::vector<int> parent;
	DWORD process_pid;
	DWORD parent_pid;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> strconverter;
	Process root; // root process

public:
	ProcessTracer();
	~ProcessTracer() = default;
	ProcessTracer(int argc, TCHAR **argv);
	void Run(bool isDllEnabled);
	void WriteToJSON();
	void OnCreateProcess(DWORD processId, DWORD threadId, CREATE_PROCESS_DEBUG_INFO const & createProcess);
	void GetApplicationPath();
	void OnExitProcess(DWORD threadId, EXIT_PROCESS_DEBUG_INFO const & exitProcess, bool m_isVerbose);
	void PTraceCreateProcess(int argc, TCHAR ** begin);
	void OnException(DWORD threadId, DWORD firstChance, EXCEPTION_RECORD const& exception);
	void GetProcessInformation(DWORD pid,std::string processAddress);
	void ParseArgs(std::string str);
	std::string GetCommandLineArgs(HANDLE handle);
	std::string GetArgs();
	std::string ToString(std::wstring wstr){ return strconverter.to_bytes(wstr);}
	std::string (GetCurrentDirectory)();
	std::ofstream output_file{ "compile_db.json" };
};
