cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)
project(HW1)

add_executable(HW1
        HW1.cpp
        Containers/DoublyLinkedList.hpp
        Containers/Hashtable.hpp
        Containers/LinkedList.hpp)
