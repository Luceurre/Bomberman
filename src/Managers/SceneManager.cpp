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
    this->scenes.push_back(scene);
}

bool SceneManager::isEmpty() {
    return scenes.empty();
}

