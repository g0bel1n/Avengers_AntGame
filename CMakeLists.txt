cmake_minimum_required(VERSION 3.20)
project(Avengers_AntGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(Avengers_AntGame main.cpp simulation/ants/Ant_.cpp simulation/ants/Ant_.h simulation/World.cpp simulation/World.h simulation/markers/Marker.cpp simulation/markers/Marker.h common/utils.h simulation/obstacles/Obstacle.cpp simulation/obstacles/Obstacle.h simulation/parameters.h)
find_package(PkgConfig REQUIRED)

pkg_check_modules(SFML REQUIRED sfml-graphics sfml-window)

target_link_libraries(Avengers_AntGame PRIVATE ${SFML_LIBRARIES})

# Add other flags to the compiler
target_compile_definitions(Avengers_AntGame PRIVATE ${SFML_CFLAGS_OTHER})

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
target_include_directories(Avengers_AntGame PRIVATE ${SFML_INCLUDE_DIRS})
target_link_directories(Avengers_AntGame PRIVATE ${SFML_LIBRARY_DIRS})

#add_subdirectory(tests)
