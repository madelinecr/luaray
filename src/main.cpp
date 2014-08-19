#include "camera.h"
#include "scene.h"
#include "bitmap.h"
#include "primitives.h"
#include "color.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>

extern "C" {
#include "lua.h"
#include "lualib.h"
}

#include <luabind/luabind.hpp>

using namespace luabind;

int main(int argc, char** argv) {
  if(argc == 2) {
    lua_State* L = luaL_newstate();
    open(L);
    module(L) [
      class_<Color>("Color")
        .def(constructor<uint16_t,uint16_t,uint16_t>())
        .def("r", &Color::r)
        .def("g", &Color::g)
        .def("b", &Color::b),
      class_<Object>("Object")
        .def(constructor<Vec3, Color>()),
      class_<Sphere, Object>("Sphere")
        .def(constructor<Vec3,Color,double>()),
      class_<light>("light")
        .def(constructor<Vec3*,double>())
        .def_readwrite("position", &light::pos)
        .def_readwrite("intensity", &light::intensity),
      class_<Vec3>("Vec3")
        .def(constructor<double,double,double>())
        .def_readwrite("x", &Vec3::m_x)
        .def_readwrite("y", &Vec3::m_y)
        .def_readwrite("z", &Vec3::m_z),
      class_<Camera>("Camera")
        .def(constructor<uint16_t,uint16_t,Scene*>())
        .def("render", &Camera::render),
      class_<Scene>("Scene")
        .def(constructor<>())
        .def("add_object", &Scene::add_object)
        .def("add_light", &Scene::add_light)
    ];

    luaL_openlibs(L);
    if(luaL_dofile(L, argv[1])) {
      std::cout << lua_tostring(L, -1) << std::endl;
    }

    std::cout << "Execution finished." << std::endl;
    lua_close(L);
  } else {
    std::cout << "raytrace" << std::endl;
    std::cout << "Usage: raytrace scenefile.lua" << std::endl << std::endl;
  }
  return 0;
}
