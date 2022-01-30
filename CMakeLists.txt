cmake_minimum_required(VERSION 3.20)
project(Avengers_AntGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(Avengers_AntGame main.cpp simulation/ants/Ant_.cpp simulation/ants/Ant_.h simulation/Colony.cpp simulation/Colony.h simulation/Elements/Marker.cpp simulation/Elements/Marker.h common/utils.h simulation/obstacles/Obstacle.cpp simulation/obstacles/Obstacle.h simulation/parameters.h simulation/chunks/chunk.cpp simulation/chunks/chunk.h simulation/Elements/Food.cpp simulation/Elements/Food.h simulation/Elements/BaseElement.h simulation/World.cpp simulation/World.h)
find_package(PkgConfig REQUIRED)





#set(CMAKE_C_COMPILER "/opt/homebrew/Cellar/llvm/13.0.0_2/bin/clang")
#set(CMAKE_CXX_COMPILER "/opt/homebrew/Cellar/llvm/13.0.0_2/bin/clang++")
#set(OPENMP_LIBRARIES "/opt/homebrew/Cellar/llvm/13.0.0_2/lib")
#set(OPENMP_INCLUDES "/opt/homebrew/Cellar/llvm/13.0.0_2/include")

#OPTION (USE_OpenMP "Use OpenMP to enable <omp.h>" ON)
#
# Find OpenMP
#if(APPLE AND USE_OpenMP)
#    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
#        set(OpenMP_C "${CMAKE_C_COMPILER}")
#        set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
#        set(OpenMP_C_LIB_NAMES "libomp" "libgomp" "libiomp5")
#        set(OpenMP_libomp_LIBRARY ${OpenMP_C_LIB_NAMES})
#        set(OpenMP_libgomp_LIBRARY ${OpenMP_C_LIB_NAMES})
#        set(OpenMP_libiomp5_LIBRARY ${OpenMP_C_LIB_NAMES})
#    endif()
#    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#        set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
#        set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument -L/opt/homebrew/Cellar/llvm/13.0.0_2/lib ")
#        set(OpenMP_CXX_LIB_NAMES "libomp" "libgomp" "libiomp5")
#        set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
#        set(OpenMP_libgomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
#        set(OpenMP_libiomp5_LIBRARY ${OpenMP_CXX_LIB_NAMES})
#    endif()
#endif()

#if(USE_OpenMP)
#    find_package(OpenMP REQUIRED)
#endif(USE_OpenMP)

#if (OPENMP_FOUND)
#    include_directories("${OPENMP_INCLUDES}")
#    link_directories("${OPENMP_LIBRARIES}")
#    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#    # set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
#endif(OPENMP_FOUND)





pkg_check_modules(SFML REQUIRED sfml-graphics sfml-window)

target_link_libraries(Avengers_AntGame PRIVATE ${SFML_LIBRARIES})

# Add other flags to the compiler
target_compile_definitions(Avengers_AntGame PRIVATE ${SFML_CFLAGS_OTHER})

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
target_include_directories(Avengers_AntGame PRIVATE ${SFML_INCLUDE_DIRS})
target_link_directories(Avengers_AntGame PRIVATE ${SFML_LIBRARY_DIRS})