cmake_minimum_required(VERSION 3.22)

project(Resonance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
)

FetchContent_MakeAvailable(SFML)

add_executable(Resonance
    src/main.cpp

    src/Player.cpp
    src/Door.cpp
    src/Generator.cpp
    src/Terminal.cpp
    src/World.cpp
    src/ResonancePulse.cpp
    src/Anomaly.cpp
)

target_link_libraries(Resonance PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)