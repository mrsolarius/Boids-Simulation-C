cmake_minimum_required(VERSION 3.15)
project(Fouloscopie_Louis_VOLAT)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra")


add_executable(Fouloscopie_Louis_VOLAT main.cpp main.cpp AllegroManager.cpp AllegroManager.h BoidsManager.cpp BoidsManager.h Boid.cpp Boid.h Vectors.cpp Vectors.h)

if(UNIX)
   find_library(LIBALLEGRO allegro)
   find_library(LIBALLEGRO_PRIMITIVES allegro_primitives)
   target_link_libraries(Fouloscopie_Louis_VOLAT ${LIBALLEGRO} ${LIBALLEGRO_PRIMITIVES})
endif(UNIX)

# Attempt at configuring Allegro for MinGW, not tested...
if(MINGW)
   # À mettre à jour en fonction de où vous avez installé Allegro
   include_directories( "C:/MinGW/include" )
   link_directories( "C:/MinGW/lib" )
   target_link_libraries(miniCrowd liballegro.dll.a liballegro_primitives.dll.a)
endif(MINGW)


