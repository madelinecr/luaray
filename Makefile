CC=clang++
CFLAGS=-g -Wall -pedantic -O0 -std=c++11

# Project configuration
SRCDIR=src
ODIR=build
LIBS=math render scene
SOURCES=math/ray.cpp math/vec3.cpp \
				render/bitmap.cpp \
				scene/camera.cpp scene/color.cpp scene/object.cpp scene/sphere.cpp \
				scene/scene.cpp \
				main.cpp
EXECUTABLE=raytrace

# Lua compilation headers
CFLAGS+=-I/usr/local/Cellar/lua51/5.1.5_4/include/lua-5.1/
# Luabind compilation headers
CFLAGS+=-I/usr/local/Cellar/luabind/0.9.1_1/include
CFLAGS+=-I/usr/local/Cellar/boost/1.60.0_2/include
# Lua library for linking stage
LINKFLAGS=-L/usr/local/Cellar/lua51/5.1.5_4/lib/
LINKFLAGS+=-L/usr/local/Cellar/luabind/0.9.1_1/lib/
LINKFLAGS+=-L/usr/local/Cellar/boost/1.60.0_2/lib/

# Library flags
LIBFLAGS=-llua5.1
LIBFLAGS+=-lluabind

# Sources with .cpp replaced with .o
OBJECTS=$(SOURCES:.cpp=.o)
# Library folders with the build dir prepended
OLIBDIR=$(addprefix $(ODIR)/, $(LIBS))

all: build $(addprefix $(ODIR)/, $(OBJECTS)) $(EXECUTABLE)

debug: CFLAGS += -DDEBUG
debug: all

$(EXECUTABLE): $(addprefix $(ODIR)/, $(OBJECTS))
	$(CC) $(LINKFLAGS) $(addprefix $(ODIR)/, $(OBJECTS)) -o $@ $(LIBFLAGS)

$(addprefix $(ODIR)/, %.o): $(SRCDIR)/%.cpp
	$(CC) $(addprefix -I$(SRCDIR)/, $(LIBS)) $(CFLAGS) -c $^ -o $@

build:
	mkdir $(ODIR)
	mkdir $(OLIBDIR)

.PHONY: clean
clean:
	rm -r $(ODIR)
	rm $(EXECUTABLE)
