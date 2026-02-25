cmake_minimum_required(VERSION 3.10)

project(PacMan)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR})

add_executable(PacMan src/main.cpp include/ECS/Component.h include/ECS/Entity.h include/ECS/System.h include/AbstractFactory.h include/ECS/ECS.h src/SDL_Factory.cpp include/SDL_Factory.h include/Pacman/SDL_Components.h src/SDL_Systems/SDL_RenderSystem.cpp include/SDL_Systems/SDL_RenderSystem.h src/ECS/SystemManager.cpp include/ECS/SystemManager.h src/Pacman/Game.cpp include/Pacman/Game.h src/Systems/MovementSystem.cpp include/Systems/MovementSystem.h include/Pacman/PacMan_Components.h src/SDL_Systems/SDL_EventSystem.cpp include/SDL_Systems/SDL_EventSystem.h include/Systems/EventSystem.h src/Systems/AISystem.cpp include/Systems/AISystem.h include/Pacman/PacMan_Constants.h src/Systems/CollisionSystem.cpp include/Systems/CollisionSystem.h include/Systems/TimerSystem.h src/SDL_Systems/SDL_TimerSystem.cpp include/SDL_Systems/SDL_TimerSystem.h src/Pacman/World.cpp include/Pacman/World.h include/Systems/RenderSystem.h src/ECS/Entity.cpp src/Config.cpp include/Config.h include/TinyXML/tinyxml2.h include/TinyXML/tinyxml2.cpp src/Pacman/SDL_Text.cpp include/Pacman/SDL_Text.h)

target_link_libraries(PacMan ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})