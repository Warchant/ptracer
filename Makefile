CC=gcc
CXX=g++

LDLIBS=-static -limagehlp
CFLAGS=
CXXFLAGS=-std=c++17 -O3

HEADERS=\
	NtQueries.h \
	json.hpp \
	Process.h \
	ProcessTracer.h \
	resource.h \
	SimpleSymbolEngine.h

SOURCES=\
	main.cpp \
	Process.cpp \
	ProcessTracer.cpp \
	SimpleSymbolEngine.cpp

OBJS=$(subst .cpp,.o,$(SOURCES))
D=$(subst .cpp,.d,$(SOURCES))

# -include $(D)

%.o: %.cpp
	$(CXX) -MD -MP $(CXXFLAGS) -o $@ -c $<

tracer.exe: $(OBJS)
	$(CXX) $(LDFLAGS) -o tracer $(OBJS) $(LDLIBS)

t.exe: tracer.exe
	cp $< $@

clean:
	-@rm *.o *.d tracer.exe

test: t.exe
	@echo "TESTING"
	make clean
	t.exe "make"
