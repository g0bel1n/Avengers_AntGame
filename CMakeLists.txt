cmake_minimum_required(VERSION 3.20)
project(ants_fight_club)

set(CMAKE_CXX_STANDARD 14)

add_executable(ants_fight_club main.cpp simulation/ants/Ant_.cpp simulation/ants/Ant_.h simulation/World.cpp simulation/World.h simulation/markers/Marker.cpp simulation/markers/Marker.h simulation/synch.cpp simulation/Renderer.cpp simulation/Renderer.h common/utils.h simulation/markers/MarkersPile.cpp simulation/markers/MarkersPile.h)
find_package(PkgConfig REQUIRED)

pkg_check_modules(SFML REQUIRED sfml-graphics)

target_link_libraries(ants_fight_club PRIVATE ${SFML_LIBRARIES})

# Add other flags to the compiler
target_compile_definitions(ants_fight_club PRIVATE ${SFML_CFLAGS_OTHER})

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
target_include_directories(ants_fight_club PRIVATE ${SFML_INCLUDE_DIRS})
target_link_directories(ants_fight_club PRIVATE ${SFML_LIBRARY_DIRS})

