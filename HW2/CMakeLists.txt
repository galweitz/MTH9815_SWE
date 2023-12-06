cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)
project(HW2)

add_executable(HW2
        HW2.cpp
        products.hpp
        productservice.hpp
        boost/interprocess/shared_memory_object.hpp
        boost/interprocess/mapped_region.hpp
        soa.hpp)
