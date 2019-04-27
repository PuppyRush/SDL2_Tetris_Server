cmake_minimum_required(VERSION 3.12)
project(sdl2_tetris_server)

set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR /usr/include)
set(BOOST_SOURCE /usr/include)
set(Boost_LIBRARIES /usr/lib/x86_64-linux-gnu/)

set(ACE_LINK_FLAGS "${ACE_LINK_FLAGS}" CACHE INTERNAL "ace link flags")

find_package(Boost 1.65.1 REQUIRED COMPONENTS system filesystem serialization)
find_package(PkgConfig REQUIRED)

add_library(boost::serialization INTERFACE IMPORTED)

pkg_check_modules(JSONCPP jsoncpp)

link_libraries(${JSONCPP_LIBRARIES})

########################################################################
##  general find

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
        src/Main.cpp
        src/GameInterface/Online/JsonHelper.cpp
        src/GameInterface/Online/JsonHelper.h
        src/GameInterface/Object/Player.cpp
        src/GameInterface/Object/Player.h
        src/GameInterface/Object/Room.cpp
        src/GameInterface/Object/Room.h
        src/GameInterface/Object/Atomic.h
        src/GameInterface/Object/Object.cpp
        src/GameInterface/Object/Object.h
        src/GameInterface/Object/GameRoom.cpp
        src/GameInterface/Object/GameRoom.h
        src/GameInterface/Object/WaitingRoom.cpp
        src/GameInterface/Object/WaitingRoom.h
        src/GameInterface/SubScription/Observer.h
        src/GameInterface/Online/ClientConnector.cpp
        src/GameInterface/Online/ClientConnector.h
        src/GameInterface/Online/ClientService.cpp
        src/GameInterface/Online/ClientService.h
        src/GameInterface/Online/MessageType.h
        src/GameInterface/Online/Packet.cpp
        src/GameInterface/Online/Packet.h
        src/GameInterface/Online/PacketQueue.h
        src/GameInterface/Online/PacketQueue.cpp
        src/GameInterface/Online/PacketCommander.cpp
        src/GameInterface/Online/PacketCommander.h
        src/GameInterface/SubScription/SubjectInterface.h
        src/GameInterface/SubScription/VectorSubject.h
        src/GameInterface/SubScription/MapSubject.h
        src/GameInterface/SubScription/ManagerController.cpp
        src/GameInterface/SubScription/ManagerController.h
        src/GameInterface/Tool/Timer.h
        src/Server/PlayerService.cpp
        src/Server/PlayerService.h
        src/Server/ServerAcceptor.cpp
        src/Server/ServerAcceptor.h
        src/Server/Quit.cpp
        src/Server/Quit.h
        src/Server/Object/ServerPlayer.cpp
        src/Server/Object/ServerPlayer.h
        src/Server/Object/ServerWaitingRoom.cpp
        src/Server/Object/ServerWaitingRoom.h
        src/Server/ObjectManager/PlayerManager.cpp
        src/Server/ObjectManager/PlayerManager.h
        src/Server/ObjectManager/WaitingRoomManager.cpp
        src/Server/ObjectManager/WaitingRoomManager.h
        src/Server/ObjectManager/ConnectingPlayerQueue.cpp
        src/Server/ObjectManager/ConnectingPlayerQueue.h
        src/GameInterface/SubScription/ManagerInterface.h
        src/Server/Object/ServerGameRoom.cpp
        src/Server/Object/ServerGameRoom.h
        src/Server/ObjectManager/GameRoomManager.cpp
        src/Server/ObjectManager/GameRoomManager.h)

include_directories(
        sdl2_tetris_server/src
        SYSTEM ${Boost_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${ACE_INCLUDE_DIR})

target_link_libraries(
        sdl2_tetris_server
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_LIBRARIES}
        ${ACE_LIBRARIES}
        Threads::Threads)

