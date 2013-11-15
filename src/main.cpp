#include "camera.h"
#include "scene.h"
#include "bitmap.h"

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
      class_<sphere>("sphere")
        .def(constructor<double,double,double,double,double,double,double>())
        .def_readwrite("x", &sphere::x)
        .def_readwrite("y", &sphere::y)
        .def_readwrite("z", &sphere::z)
        .def_readwrite("radius", &sphere::radius)
        .def_readwrite("red", &sphere::red)
        .def_readwrite("green", &sphere::green)
        .def_readwrite("blue", &sphere::blue),
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
        .def("add_sphere", &Scene::add_sphere)
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
