CC=gcc#CC=$(CC)
CXX=g++#CXX=$(CXX)
RM=rm -f
CXXFLAGS=-std=c++11 -pthread
LDFLAGS=
LDLIBS=-lstdc++ -lgcc

SRCS=sylphrena-core/syl_socketServer.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: syl_core syl_input

syl_core: $(OBJS) sylphrena-core/main.cpp sylphrena-core/syl_lib.h sylphrena-core/syl_lib.cpp sylphrena-core/syl_core.h sylphrena-core/syl_core.cpp
	$(CXX) $(CXXFLAGS) sylphrena-core/main.cpp sylphrena-core/syl_lib.cpp sylphrena-core/syl_lib.h sylphrena-core/syl_core.h sylphrena-core/syl_core.cpp -o sylphrena-core/syl_core $(OBJS) $(LDLIBS)

syl_input: sylphrena-input/main.cpp sylphrena-input/syl_socketClient.h sylphrena-input/syl_socketClient.cpp
	$(CXX) $(CXXFLAGS) sylphrena-input/main.cpp sylphrena-input/syl_socketClient.cpp sylphrena-input/syl_socketClient.h  -o sylphrena-input/syl_input $(LDLIBS)

syl_socketServer.o: sylphrena-core/syl_socketServer.h sylphrena-core/syl_socketServer.cpp sylphrena-core/syl_core.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) syl_core
