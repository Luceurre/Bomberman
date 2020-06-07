cmake_minimum_required(VERSION 3.16)
project(Bomberman)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS -pthread)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_image REQUIRED)
INCLUDE(FindPkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS})

link_directories (${SDL2_LIBRARY_DIRS}
        ${SDL2_IMAGE_LIBRARY_DIRS})

add_executable(Bomberman main.cpp src/Scenes/Scene.cpp src/Scenes/Scene.h src/Utils/Logger.cpp src/Utils/Logger.h
        src/ECS/ECS.cpp src/ECS/ECS.h src/ECS/Components/Components.h src/Managers/SceneManager.cpp src/Managers/SceneManager.h
        src/Managers/TextureManager.cpp src/Managers/TextureManager.h src/Managers/WindowManager.cpp src/Managers/WindowManager.h
        src/Scenes/LoadingScene.cpp src/Scenes/LoadingScene.h src/Scenes/MainMenuScene.cpp src/Scenes/MainMenuScene.h
        src/Scenes/GraphicScene.h src/ECS/Components/PositionComponent.h src/ECS/Components/VelocityComponent.h
        src/ECS/Components/BasicSpriteComponent.h src/ECS/Components/HitboxComponent.h src/ECS/Components/SpriteComponent.h
        src/ECS/Components/MousePositionComponent.h src/Utils/Functor.h src/ECS/Components/ClickableComponent.h src/ECS/Entities/Button.h)

target_link_libraries(Bomberman ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})