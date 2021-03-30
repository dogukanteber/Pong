OBJECTS = src/Game.cpp

CC = g++

COMPILER_FLAGS = -w -Wall

LINKLER_FLAGS = -lncurses

OBJECT_NAME = pong

all : $(OBJECTS)
	$(CC) $(OBJECTS) $(COMPILER_FLAGS) $(LINKLER_FLAGS) -o $(OBJECT_NAME)