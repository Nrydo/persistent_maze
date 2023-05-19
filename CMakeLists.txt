cmake_minimum_required(VERSION 3.25)
project(persistent_maze)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia REQUIRED)

file(GLOB SRC_FILES *.cpp Items/*.cpp Objects/*.cpp)
add_executable(persistent_maze ${SRC_FILES} resources.qrc)
target_link_libraries(persistent_maze Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia)
