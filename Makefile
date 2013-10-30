NAME=raytracer
CC=g++
CFLAGS=-c -Wall

all: raytracer

raytracer: main.o
	$(CC) main.o -o $(NAME)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
