cmake_minimum_required(VERSION 3.16) 
project(SpaceInvadersEsame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
)
FetchContent_MakeAvailable(glm)

add_library(common INTERFACE)
target_compile_features(common INTERFACE cxx_std_20)

# find_package(OpenGL REQUIRED)
# find_package(SFML 3.0 COMPONENTS graphics window audio system REQUIRED)

# --- TAPPA 01 ---
add_executable(Tappa01
    Cartella-Tappa01/main.cpp
    Cartella-Tappa01/Game.cpp
    Cartella-Tappa01/Player.cpp
)
target_link_libraries(Tappa01 PRIVATE SFML::Graphics SFML::Window SFML::System)

# --- TAPPA 02 ---
add_executable(Tappa02
    Cartella-Tappa02/main.cpp
    Cartella-Tappa02/Game.cpp
    Cartella-Tappa02/Player.cpp
)
target_link_libraries(Tappa02 PRIVATE SFML::Graphics SFML::Window SFML::System)

# --- TAPPA 03 ---
add_executable(Tappa03
    Cartella-Tappa03/main.cpp
    Cartella-Tappa03/Game.cpp
    Cartella-Tappa03/Player.cpp
)
target_link_libraries(Tappa03 PRIVATE SFML::Graphics SFML::Window SFML::System)

# --- TAPPA 04 ---
add_executable(Tappa04
    Cartella-Tappa04/main.cpp
    Cartella-Tappa04/Game.cpp
    Cartella-Tappa04/Player.cpp
)
target_link_libraries(Tappa04 PRIVATE SFML::Graphics SFML::Window SFML::System)

# --- TAPPA 05 ---
add_executable(Tappa05
    Cartella-Tappa05/main.cpp
    Cartella-Tappa05/Game.cpp
    Cartella-Tappa05/Player.cpp
    Cartella-Tappa05/Enemy.cpp
)
target_link_libraries(Tappa05 PRIVATE SFML::Graphics SFML::Window SFML::System)

# --- TAPPA 06 ---
add_executable(Tappa06
    Cartella-Tappa06/main.cpp
    Cartella-Tappa06/Game.cpp
    Cartella-Tappa06/Player.cpp
    Cartella-Tappa06/Enemy.cpp
)
target_link_libraries(Tappa06 PRIVATE SFML::Graphics SFML::Window SFML::System)

# --- TAPPA 07 ---
add_executable(Tappa07
    Cartella-Tappa07/main.cpp
    Cartella-Tappa07/Game.cpp
    Cartella-Tappa07/Player.cpp
    Cartella-Tappa07/Enemy.cpp
    Cartella-Tappa07/PowerUp.cpp
)
target_link_libraries(Tappa07 PRIVATE SFML::Graphics SFML::Window SFML::System)

# --- TAPPA 08 ---
add_executable(Tappa08
    Cartella-Tappa08/main.cpp
    Cartella-Tappa08/Game.cpp
    Cartella-Tappa08/Player.cpp
    Cartella-Tappa08/Enemy.cpp
    Cartella-Tappa08/PowerUp.cpp
)
target_link_libraries(Tappa08 PRIVATE SFML::Graphics SFML::Window SFML::System)

# --- TAPPA 09 ---
add_executable(Tappa09
    Cartella-Tappa09/main.cpp
    Cartella-Tappa09/Game.cpp
    Cartella-Tappa09/Player.cpp
    Cartella-Tappa09/Enemy.cpp
    Cartella-Tappa09/PowerUp.cpp
)
target_link_libraries(Tappa09 PRIVATE SFML::Graphics SFML::Window SFML::System)

# --- TAPPA 10 ---
add_executable(Tappa10
    Cartella-Tappa10/main.cpp
    Cartella-Tappa10/Game.cpp
    Cartella-Tappa10/Player.cpp
    Cartella-Tappa10/Enemy.cpp
    Cartella-Tappa10/PowerUp.cpp
)
target_link_libraries(Tappa10 PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)