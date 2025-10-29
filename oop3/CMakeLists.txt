cmake_minimum_required(VERSION 3.25)
project(oop_prog)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(json)

add_executable(oop_prog main.cpp
        field.cpp
        manager.cpp
        ship.cpp
        abilities/ability_manager.cpp
        abilities/Double_damage.cpp
        abilities/scanner.cpp
        abilities/rocket.cpp
        abilities/exception.cpp
        abilities/ability_registry.cpp
        abilities/player.cpp
        game_state.cpp
        game.cpp
)

target_link_libraries(oop_prog nlohmann_json::nlohmann_json)
