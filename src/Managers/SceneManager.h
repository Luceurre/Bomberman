//
// Created by pglandon on 4/21/20.
//

#ifndef ATELIERPROG_SCENEMANAGER_H
#define ATELIERPROG_SCENEMANAGER_H

#include <vector>

#include "../Utils/Logger.h"

// Forward Declaration to avoid Circular Definition
class Scene;

class SceneManager : protected Logger {
protected:
    std::string descriptor() override;

public:
    static SceneManager* getInstance()
    {
        static SceneManager instance;
        return &instance;
    }

    SceneManager(SceneManager const&) = delete;
    void operator=(SceneManager const&) = delete;

    void add_scene(Scene* scene);
    bool isEmpty();
    void updateScenes();

    SceneManager();

    std::vector<Scene*> scenes;
};


#endif //ATELIERPROG_SCENEMANAGER_H
