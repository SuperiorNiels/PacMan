cmake_minimum_required(VERSION 3.9)
project(PacMan)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR})

add_executable(PacMan main.cpp ECS/Component.h ECS/Entity.h ECS/System.h AbstractFactory.h ECS/ECS.h SDL_Factory.cpp SDL_Factory.h SDL_Components.h SDL_Systems/SDL_RenderSystem.cpp SDL_Systems/SDL_RenderSystem.h ECS/SystemManager.cpp ECS/SystemManager.h Game.cpp Game.h Systems/MovementSystem.cpp Systems/MovementSystem.h PacMan_Components.h SDL_Systems/SDL_EventSystem.cpp SDL_Systems/SDL_EventSystem.h Systems/EventSystem.h Systems/AISystem.cpp Systems/AISystem.h PacMan_Constants.h Systems/CollisionSystem.cpp Systems/CollisionSystem.h Systems/TimerSystem.h SDL_Systems/SDL_TimerSystem.cpp SDL_Systems/SDL_TimerSystem.h World.cpp World.h Systems/RenderSystem.h ECS/Entity.cpp Config.cpp Config.h TinyXML/tinyxml2.h TinyXML/tinyxml2.cpp SDL_Text.cpp SDL_Text.h Systems/GameplaySystem.cpp Systems/GameplaySystem.h)

target_link_libraries(PacMan ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})