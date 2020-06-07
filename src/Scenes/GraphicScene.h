//
// Created by pglandon on 5/31/20.
//

#ifndef ATELIERPROG_GRAPHICSCENE_H
#define ATELIERPROG_GRAPHICSCENE_H


#include "Scene.h"
#include "../Windows/Window.h"
#include "../Managers/WindowManager.h"
#include "../Managers//TextureManager.h"

class GraphicScene : public Scene {
public:
    inline GraphicScene() : Scene() {
        sceneWindow = nullptr;
    }

    inline int initialize() override {
        Scene::initialize();

        sceneWindow = WindowManager::getInstance().get_primary_window();
        TextureManager::renderer = sceneWindow->renderer;

        return 0;
    }
protected:
    Window* sceneWindow;
};


#endif //ATELIERPROG_GRAPHICSCENE_H
