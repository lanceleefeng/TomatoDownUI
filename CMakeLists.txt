cmake_minimum_required(VERSION 3.6)
project(TomatoDownUI)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        mainwindow.cpp
        mainwindow.h )

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)

add_executable(TomatoDownUI ${SOURCE_FILES})

target_link_libraries(TomatoDownUI Qt5::Core Qt5::Widgets Qt5::Sql)

