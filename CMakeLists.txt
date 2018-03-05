cmake_minimum_required(VERSION 3.9)
project(ECS)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR})

add_executable(ECS main.cpp ECS/Component.h ECS/Entity.h ECS/System.h AbstractFactory.h ECS/ECS.h SDL_Factory.cpp SDL_Factory.h SDL_Components.h SDL_RenderSystem.cpp SDL_RenderSystem.h SystemManager.cpp SystemManager.h Game.cpp Game.h MovementSystem.cpp MovementSystem.h)

target_link_libraries(ECS ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})