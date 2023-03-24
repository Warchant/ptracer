# ptracer

Compile:
```bash
make
```

Run:
```bash
ptracer.exe -o output.json -c "make"
```

Example output:
```json
{
  "children": [
    {
      "children": [
        {
          "children": [
            {
              "command": "C:/Users/warch/scoop/apps/mingw/current/bin/../libexec/gcc/x86_64-w64-mingw32/12.2.0/cc1plus.exe -quiet -iprefix C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/ -MD main.d -MP -MQ main.o -D_REENTRANT main.cpp -quiet -dumpbase main.cpp -dumpbase-ext .cpp -m64 -mtune=core2 -march=nocona -O3 -std=c++20 -o C:/Users/warch/AppData/Local/Temp/ccXwZUbn.s",
              "directory": "C:/tools/PTracer-Windows"
            },
            {
              "command": "C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/bin/as.exe --64 -o main.o C:/Users/warch/AppData/Local/Temp/ccXwZUbn.s",
              "directory": "C:/tools/PTracer-Windows"
            }
          ],
          "command": "g++ -MD -MP -std=c++20 -O3 -m64 -o main.o -c main.cpp",
          "directory": "C:/tools/PTracer-Windows"
        },
        {
          "children": [
            {
              "command": "C:/Users/warch/scoop/apps/mingw/current/bin/../libexec/gcc/x86_64-w64-mingw32/12.2.0/cc1plus.exe -quiet -iprefix C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/ -MD Process.d -MP -MQ Process.o -D_REENTRANT Process.cpp -quiet -dumpbase Process.cpp -dumpbase-ext .cpp -m64 -mtune=core2 -march=nocona -O3 -std=c++20 -o C:/Users/warch/AppData/Local/Temp/ccZrll5m.s",
              "directory": "C:/tools/PTracer-Windows"
            },
            {
              "command": "C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/bin/as.exe --64 -o Process.o C:/Users/warch/AppData/Local/Temp/ccZrll5m.s",
              "directory": "C:/tools/PTracer-Windows"
            }
          ],
          "command": "g++ -MD -MP -std=c++20 -O3 -m64 -o Process.o -c Process.cpp",
          "directory": "C:/tools/PTracer-Windows"
        },
        {
          "children": [
            {
              "command": "C:/Users/warch/scoop/apps/mingw/current/bin/../libexec/gcc/x86_64-w64-mingw32/12.2.0/cc1plus.exe -quiet -iprefix C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/ -MD ProcessTracer.d -MP -MQ ProcessTracer.o -D_REENTRANT ProcessTracer.cpp -quiet -dumpbase ProcessTracer.cpp -dumpbase-ext .cpp -m64 -mtune=core2 -march=nocona -O3 -std=c++20 -o C:/Users/warch/AppData/Local/Temp/cc1Qzf6m.s",
              "directory": "C:/tools/PTracer-Windows"
            },
            {
              "command": "C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/bin/as.exe --64 -o ProcessTracer.o C:/Users/warch/AppData/Local/Temp/cc1Qzf6m.s",
              "directory": "C:/tools/PTracer-Windows"
            }
          ],
          "command": "g++ -MD -MP -std=c++20 -O3 -m64 -o ProcessTracer.o -c ProcessTracer.cpp",
          "directory": "C:/tools/PTracer-Windows"
        },
        {
          "children": [
            {
              "command": "C:/Users/warch/scoop/apps/mingw/current/bin/../libexec/gcc/x86_64-w64-mingw32/12.2.0/cc1plus.exe -quiet -iprefix C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/ -MD SimpleSymbolEngine.d -MP -MQ SimpleSymbolEngine.o -D_REENTRANT SimpleSymbolEngine.cpp -quiet -dumpbase SimpleSymbolEngine.cpp -dumpbase-ext .cpp -m64 -mtune=core2 -march=nocona -O3 -std=c++20 -o C:/Users/warch/AppData/Local/Temp/cc3tzM5m.s",
              "directory": "C:/tools/PTracer-Windows"
            },
            {
              "command": "C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/bin/as.exe --64 -o SimpleSymbolEngine.o C:/Users/warch/AppData/Local/Temp/cc3tzM5m.s",
              "directory": "C:/tools/PTracer-Windows"
            }
          ],
          "command": "g++ -MD -MP -std=c++20 -O3 -m64 -o SimpleSymbolEngine.o -c SimpleSymbolEngine.cpp",
          "directory": "C:/tools/PTracer-Windows"
        },
        {
          "children": [
            {
              "children": [
                {
                  "command": "C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe -plugin C:/Users/warch/scoop/apps/mingw/current/bin/../libexec/gcc/x86_64-w64-mingw32/12.2.0/liblto_plugin.dll -plugin-opt=C:/Users/warch/scoop/apps/mingw/current/bin/../libexec/gcc/x86_64-w64-mingw32/12.2.0/lto-wrapper.exe -plugin-opt=-fresolution=C:/Users/warch/AppData/Local/Temp/ccTIXZqg.res -plugin-opt=-pass-through=-lmingw32 -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_eh -plugin-opt=-pass-through=-lmoldname -plugin-opt=-pass-through=-lmingwex -plugin-opt=-pass-through=-lmsvcrt -plugin-opt=-pass-through=-lkernel32 -plugin-opt=-pass-through=-lpthread -plugin-opt=-pass-through=-ladvapi32 -plugin-opt=-pass-through=-lshell32 -plugin-opt=-pass-through=-luser32 -plugin-opt=-pass-through=-lkernel32 -plugin-opt=-pass-through=-liconv -plugin-opt=-pass-through=-lmingw32 -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_eh -plugin-opt=-pass-through=-lmoldname -plugin-opt=-pass-through=-lmingwex -plugin-opt=-pass-through=-lmsvcrt -plugin-opt=-pass-through=-lkernel32 --sysroot=C:/buildroot/x86_64-1220-posix-seh-rt_v10-rev1/mingw64 -m i386pep -Bstatic -o tracer.exe C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/lib/../lib/crt2.o C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/crtbegin.o -LC:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0 -LC:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc -LC:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/lib/../lib -LC:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../lib -LC:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/lib -LC:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../.. main.o Process.o ProcessTracer.o SimpleSymbolEngine.o -limagehlp -lstdc++ -lmingw32 -lgcc -lgcc_eh -lmoldname -lmingwex -lmsvcrt -lkernel32 -lpthread -ladvapi32 -lshell32 -luser32 -lkernel32 -liconv -lmingw32 -lgcc -lgcc_eh -lmoldname -lmingwex -lmsvcrt -lkernel32 C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/crtend.o",
                  "directory": "C:/tools/PTracer-Windows"
                }
              ],
              "command": "C:/Users/warch/scoop/apps/mingw/current/bin/../libexec/gcc/x86_64-w64-mingw32/12.2.0/collect2.exe -plugin C:/Users/warch/scoop/apps/mingw/current/bin/../libexec/gcc/x86_64-w64-mingw32/12.2.0/liblto_plugin.dll -plugin-opt=C:/Users/warch/scoop/apps/mingw/current/bin/../libexec/gcc/x86_64-w64-mingw32/12.2.0/lto-wrapper.exe -plugin-opt=-fresolution=C:/Users/warch/AppData/Local/Temp/ccTIXZqg.res -plugin-opt=-pass-through=-lmingw32 -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_eh -plugin-opt=-pass-through=-lmoldname -plugin-opt=-pass-through=-lmingwex -plugin-opt=-pass-through=-lmsvcrt -plugin-opt=-pass-through=-lkernel32 -plugin-opt=-pass-through=-lpthread -plugin-opt=-pass-through=-ladvapi32 -plugin-opt=-pass-through=-lshell32 -plugin-opt=-pass-through=-luser32 -plugin-opt=-pass-through=-lkernel32 -plugin-opt=-pass-through=-liconv -plugin-opt=-pass-through=-lmingw32 -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_eh -plugin-opt=-pass-through=-lmoldname -plugin-opt=-pass-through=-lmingwex -plugin-opt=-pass-through=-lmsvcrt -plugin-opt=-pass-through=-lkernel32 --sysroot=C:/buildroot/x86_64-1220-posix-seh-rt_v10-rev1/mingw64 -m i386pep -Bstatic -o tracer.exe C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/lib/../lib/crt2.o C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/crtbegin.o -LC:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0 -LC:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc -LC:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/lib/../lib -LC:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../lib -LC:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../../../x86_64-w64-mingw32/lib -LC:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/../../.. main.o Process.o ProcessTracer.o SimpleSymbolEngine.o -limagehlp -lstdc++ -lmingw32 -lgcc -lgcc_eh -lmoldname -lmingwex -lmsvcrt -lkernel32 -lpthread -ladvapi32 -lshell32 -luser32 -lkernel32 -liconv -lmingw32 -lgcc -lgcc_eh -lmoldname -lmingwex -lmsvcrt -lkernel32 C:/Users/warch/scoop/apps/mingw/current/bin/../lib/gcc/x86_64-w64-mingw32/12.2.0/crtend.o",
              "directory": "C:/tools/PTracer-Windows"
            }
          ],
          "command": "g++ -MD -MP -o tracer main.o Process.o ProcessTracer.o SimpleSymbolEngine.o -static -limagehlp -static-libgcc -static-libstdc++",
          "directory": "C:/tools/PTracer-Windows"
        }
      ],
      "command": "make",
      "directory": "C:/tools/PTracer-Windows"
    }
  ],
  "command": "",
  "directory": ""
}
```
