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

int _tmain(int argc, TCHAR **argv) {

  if (argc <= 1) {
    std::cout << "See options via -h or --help\n";
    return 1;
  }

  try {
    std::unique_ptr<ProcessTracer> handler =
        std::unique_ptr<ProcessTracer>(new ProcessTracer(argc, argv));
    handler->Run(false);
  } catch (const std::exception &e) {
    std::cerr << ("EXCEPTION: \n") << e.what();
    return 1;
  }

  return 0;
}
