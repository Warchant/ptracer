CC=gcc
CXX=g++

LDLIBS=
CFLAGS=
CPPFLAGS=

HEADERS=NtQueries.h \
	json.hpp \
	Process.h \
	ProcessTracer.h \
	resource.h \
	SimpleSymbolEngine.h

SOURCES=main.cpp \
	Process.cpp \
	ProcessTracer.cpp \
	SimpleSymbolEngine.cpp

OBJS=$(subst .cpp,.o,$(SOURCES))

app: $(OBJS)
	$(CXX) $(LDFLAGS) -o tracer $(OBJS) $(LDLIBS)

clean:
	rm $(OBJS)
