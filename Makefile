CXX=g++
CPPFLAGS=-g -O2 -Wno-unused-result
LDFLAGS=-g
SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: mm-decompile

mm-decompile: $(OBJS)
	$(CXX) $(LDFLAGS) -o mm-decompile $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<
