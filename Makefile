CC=clang++
CFLAGS=-g -Wall -pedantic -O0 
# Lua compilation headers
CFLAGS+=-I/usr/include/lua5.2/
# Lua library for linking stage
LINKFLAGS=-llua5.2 -lluabind
SRCDIR=src
ODIR=build
EXECUTABLE=raytrace
SOURCES=main.cpp camera.cpp bitmap.cpp scene.cpp vec3.cpp ray.cpp object.cpp primitives.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(addprefix $(ODIR)/, $(OBJECTS)) $(EXECUTABLE)

debug: CFLAGS += -DDEBUG
debug: all

$(EXECUTABLE): $(addprefix $(ODIR)/, $(OBJECTS))
	$(CC) $(LINKFLAGS) $(addprefix $(ODIR)/, $(OBJECTS)) -o $@

$(addprefix $(ODIR)/, %.o): $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(EXECUTABLE)
	rm build/*
