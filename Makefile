CC=clang++
CFLAGS=-g -Wall -pedantic -O0
SRCDIR=src
ODIR=build
EXECUTABLE=raytrace
SOURCES=main.cpp camera.cpp bitmap.cpp scene.cpp vec3.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(OBJECTS) $(EXECUTABLE)

debug: CFLAGS += -DDEBUG
debug: all

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(addprefix $(ODIR)/, $(OBJECTS)) -o $@

%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $(ODIR)/$@

clean:
	rm $(EXECUTABLE)
	rm build/*
