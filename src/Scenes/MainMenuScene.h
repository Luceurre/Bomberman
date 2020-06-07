//
// Created by pglandon on 5/31/20.
//

#ifndef ATELIERPROG_MAINMENUSCENE_H
#define ATELIERPROG_MAINMENUSCENE_H

#include <string>

#include "GraphicScene.h"
#include "../ECS/ECS.h"


class MainMenuScene : public GraphicScene {
protected:
    inline std::string descriptor() override {
        return "(MainMenuScene)";
    }

    int model() override;
    int view() override;

    int selected_button;
    Manager manager;
    Entity* background;
public:
    inline MainMenuScene() : GraphicScene() {}
    int initialize() override;
};


#endif //ATELIERPROG_MAINMENUSCENE_H
