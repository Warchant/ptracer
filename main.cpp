/*
MIT License

Copyright (c) 2021 Mehmet Ali Baykara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "ProcessTracer.h"
#include <memory>
#include "argparse.hpp"

using namespace argparse;

int main(int argc, const char**argv) {
  ArgumentParser parser("tracer", "Trace subprocess cration to produce compile database json file");
  parser.add_argument()
      .names({"-c", "--cmd"})
      .description("command to run")
      .required(true);

  parser.add_argument()
      .names({"-o", "--outut"})
      .description("path to output file")
      .required(false);

  parser.enable_help();
  auto err = parser.parse(argc, argv);
  if (err) {
    std::cout << err << std::endl;
    return 1;
  }
  if (parser.exists("help")) {
    parser.print_help();
    return 0;
  }

  std::string output = "compile_db.json";
  if(parser.exists("o")) {
    output = parser.get<std::string>("o");
  }

  std::string cmd;
  if(parser.exists("c")) {
    cmd = parser.get<std::string>("c");
  }

  auto handler = std::make_unique<ProcessTracer>(cmd);
  try {
    handler->Run();
    std::cout << "[TRACER] Success! Writing to json file: " << output << "\n";
  } catch (const std::exception &e) {
    std::cerr << ("EXCEPTION: \n") << e.what();
  }

  handler->WriteToJSON(output);

  return 0;
}
