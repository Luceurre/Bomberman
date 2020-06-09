//
// Created by pglandon on 4/21/20.
//

#include "SceneManager.h"

SceneManager::SceneManager() {
}

std::string SceneManager::descriptor() {
    return "(SceneManager)";
}

void SceneManager::add_scene(Scene *scene) {
    this->scenes.push(scene);
}

bool SceneManager::isEmpty() {
    return scenes.empty();
}

