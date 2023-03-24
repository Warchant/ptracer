CC=gcc
CXX=g++

LDLIBS=-static -limagehlp -static-libgcc -static-libstdc++
CFLAGS=
CXXFLAGS=-std=c++20 -O3 -m64

HEADERS=\
	NtQueries.h \
	json.hpp \
	Process.h \
	ProcessTracer.h \
	SimpleSymbolEngine.h \
	argparse.h

SOURCES=\
	main.cpp \
	Process.cpp \
	ProcessTracer.cpp \
	SimpleSymbolEngine.cpp

OBJS=$(subst .cpp,.o,$(SOURCES))
D=$(subst .cpp,.d,$(SOURCES))

%.o: %.cpp
	$(CXX) -MD -MP $(CXXFLAGS) -o $@ -c $<

.PRECIOUS: ptracer.exe
ptracer.exe: $(OBJS)
	$(CXX) -MD -MP $(LDFLAGS) $(CXXFLAGS) -o ptracer $(OBJS) $(LDLIBS)

clean:
	-@rm *.o *.d ptracer.exe

test: ptracer.exe
	@echo "TESTING"
	powershell -Command Copy-Item -Path ptracer.exe -Destination t.exe
	make clean
	./t.exe -c "make"

-include $(D)
