cmake_minimum_required(VERSION 3.27)
project(c_programme)

set(CMAKE_CXX_STANDARD 14)

add_executable(c_programme
        main.cpp
        hpp/Menu.hpp
        cpp/Menu.cpp
        hpp/Stulist.hpp
        hpp/Student.hpp
        cpp/Student.cpp
        cpp/Stulist.cpp
        cpp/Manager.cpp
        hpp/Manlist.hpp
        cpp/Manlist.cpp)
