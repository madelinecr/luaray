CC=clang++
CFLAGS=-g -Wall -pedantic -O0 -std=c++11

# Project configuration
SRCDIR=src
ODIR=build
LIBS=math render scene
SOURCES=math/ray.cpp math/vec3.cpp \
				render/bitmap.cpp \
				scene/camera.cpp scene/color.cpp scene/object.cpp scene/primitives.cpp \
				scene/scene.cpp \
				main.cpp
EXECUTABLE=raytrace

# Lua compilation headers
CFLAGS+=-I/usr/include/lua5.2/
# Lua library for linking stage
LINKFLAGS=-llua5.2 -lluabind
# Sources with .cpp replaced with .o
OBJECTS=$(SOURCES:.cpp=.o)
# Library folders with the build dir prepended
OLIBDIR=$(addprefix $(ODIR)/, $(LIBS))

all: build $(addprefix $(ODIR)/, $(OBJECTS)) $(EXECUTABLE)

debug: CFLAGS += -DDEBUG
debug: all

$(EXECUTABLE): $(addprefix $(ODIR)/, $(OBJECTS))
	$(CC) $(LINKFLAGS) $(addprefix $(ODIR)/, $(OBJECTS)) -o $@

$(addprefix $(ODIR)/, %.o): $(SRCDIR)/%.cpp
	$(CC) $(addprefix -I$(SRCDIR)/, $(LIBS)) $(CFLAGS) -c $^ -o $@

build:
	mkdir $(ODIR)
	mkdir $(OLIBDIR)

.PHONY: clean
clean:
	rm -r $(ODIR)
	rm $(EXECUTABLE)
