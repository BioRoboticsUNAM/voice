cmake_minimum_required(VERSION 2.8.3)
project(voice)

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# uRobotics
set(Robotics_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/")
set(Robotics_LIBRARY ${PROJECT_SOURCE_DIR}/lib/uRobotics.a)

set(CONFIG_DIR "${PROJECT_SOURCE_DIR}/config/")

set(LibSndFile_DIR "${CONFIG_DIR}")
find_package(LibSndFile REQUIRED)

set(PortAudio_DIR "${CONFIG_DIR}")
find_package(PortAudio REQUIRED)

## Festival and dependencies
# set(CURSES_USE_NCURSES TRUE)
# FIND_PACKAGE(Curses REQUIRED)

set(EST_DIR "${CONFIG_DIR}")
find_package(EST REQUIRED)

set(Festival_DIR "${CONFIG_DIR}")
find_package(Festival REQUIRED)

## Boost

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
FIND_PACKAGE( Boost 1.40 COMPONENTS program_options system filesystem regex thread date_time REQUIRED )

INCLUDE_DIRECTORIES(include	${CMAKE_SOURCE_DIR}
							${Boost_INCLUDE_DIR}
							${EST_INCLUDE_DIR}
							${Robotics_INCLUDE_DIR}
							${Festival_INCLUDE_DIR}
							${PortAudio_INCLUDE_DIR}
					)

file(GLOB_RECURSE headers "src/*.h*")
file(GLOB_RECURSE sources "src/*.c*")

add_executable(voice ${sources} ${headers} )
target_link_libraries(voice	${Boost_LIBRARIES}
							${Robotics_LIBRARY}
							${Festival_LIBRARIES}
							${LibSndFile_LIBRARY}
							${PortAudio_LIBRARY}
							${EST_LIBRARIES}
			)
