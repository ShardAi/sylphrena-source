CC=$(CC)#CC=gcc #THIS IS ACTUAL MAKEFILE
CXX=$(CXX)#CXX=g++
RM=rm -f
CXXFLAGS=-std=c++11 -pthread
LDFLAGS=
LDLIBS=-lstdc++ -lgcc

SRCS=syl_socketServer.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: syl_core

syl_core: $(OBJS) main.cpp syl_lib.h syl_lib.cpp syl_core.h syl_core.cpp
	$(CXX) $(CXXFLAGS) main.cpp syl_lib.cpp syl_lib.h syl_core.h syl_core.cpp -o syl_core $(OBJS) $(LDLIBS)

syl_socketServer.o: syl_socketServer.h syl_socketServer.cpp syl_core.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) syl_core
