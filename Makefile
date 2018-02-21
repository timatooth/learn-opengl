CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-I=/usr/include/GLFW/ -Iinclude -Wall
LDFLAGS=
LDLIBS=-lglfw -lGL -lX11 -lpthread -ldl -lXrandr -lXi
SRCS=main.cpp glad.c
OBJS=$(subst .cc,.o,$(SRCS))

all: game

game: $(OBJS)
    $(CXX) $(LDFLAGS) -o main $(OBJS) $(LDLIBS)

main.o: tool.cpp glad.c

clean:
    $(RM) $(OBJS)

distclean: clean
    $(RM) main
