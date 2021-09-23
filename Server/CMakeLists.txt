cmake_minimum_required(VERSION 3.12)
project(sdl2_tetris_server)

message("----------------server_module START----------------")

set(CMAKE_CXX_STANDARD 17)

set(ACE_LINK_FLAGS "${ACE_LINK_FLAGS}" CACHE INTERNAL "ace link flags")

link_libraries(${JSONCPP_LIBRARIES})

########################################################################
##  general find

#find_package(ace CONFIG REQUIRED)

SET(ACE_LIBRARY  $ENV{VCPKG_ROOT}\\installed\\${PLATFORM}\\${CMAKE_BUILD_TYPE}\\lib\\ACEd.lib)
SET(ACE_INCLUDE_DIR ${VCPKG_PLATFORM}/include)

find_path(ACE_INCLUDE_DIR ace/ACE.h ${CMAKE_SOURCE_DIR}/../ACE_wrappers/ /usr/include /usr/local/include $ENV{ACE_ROOT} $ENV{ACE_ROOT}/include DOC "directory containing ace/*.h for ACE library")
find_library(ACE_LIBRARY NAMES ACE ace PATHS ${CMAKE_SOURCE_DIR}/../ACE_wrappers/lib/ /usr/lib /usr/local/lib $ENV{ACE_ROOT}/lib $ENV{ACE_ROOT} DOC "ACE library file")

########################################################################
## finished - now just set up flags and complain to user if necessary

if (ACE_INCLUDE_DIR AND ACE_LIBRARY)
    set(ACE_FOUND TRUE)
else ()
    set(ACE_FOUND FALSE)
endif ()

if (ACE_DEBUG_LIBRARY)
    set(ACE_DEBUG_FOUND TRUE)
else ()
    set(ACE_DEBUG_LIBRARY ${ACE_LIBRARY})
endif ()

if (ACE_FOUND)
    if (NOT Ace_FIND_QUIETLY)
        message(STATUS "Found ACE library: ${ACE_LIBRARY}")
        message(STATUS "Found ACE include: ${ACE_INCLUDE_DIR}")
    endif ()
else ()
    if (Ace_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find ACE")
    endif ()
endif ()


# TSS: backwards compatibility
set(ACE_LIBRARIES ${ACE_LIBRARY})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
if (Threads_FOUND)
    message("-- OK.")
else ()
    message(FATAL_ERROR "Threads not found.")
endif ()

add_executable(sdl2_tetris_server
        Main.cpp
        include/PlayerService.h
        include/ServerAcceptor.h
        include/Quit.h
        include/ServerPlayer.h
        include/ServerWaitingRoom.h
        include/PlayerManager.h
        include/WaitingRoomManager.h
        include/ConnectingPlayerQueue.h
        include/ServerGameRoom.h
        include/GameRoomManager.h

        src/PlayerService.cpp
        src/ServerAcceptor.cpp
        src/Quit.cpp
        src/Object/ServerPlayer.cpp
        src/Object/ServerWaitingRoom.cpp
        src/ObjectManager/PlayerManager.cpp
        src/ObjectManager/WaitingRoomManager.cpp
        src/ObjectManager/ConnectingPlayerQueue.cpp
        src/Object/ServerGameRoom.cpp
        src/ObjectManager/GameRoomManager.cpp
        )

include_directories(
        include
        ../lib
        src
        SYSTEM ${Boost_INCLUDE_DIR}
        ${ACE_INCLUDE_DIR})

target_link_libraries(
        sdl2_tetris_server
        GameInterface
        TetrisModule
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_LIBRARIES}
        ${ACE_LIBRARY}
        Threads::Threads)

