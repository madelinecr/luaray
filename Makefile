CC=clang++
CFLAGS=-g -Wall -pedantic -O0
SRCDIR=src
ODIR=build
EXECUTABLE=raytrace
SOURCES=main.cpp view.cpp bitmap.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(addprefix $(ODIR)/, $(OBJECTS)) -o $@

%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $(ODIR)/$@

clean:
	rm $(EXECUTABLE)
	rm build/*
