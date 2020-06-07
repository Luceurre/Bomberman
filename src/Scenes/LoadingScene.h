//
// Created by pglandon on 5/31/20.
//

#ifndef ATELIERPROG_LOADINGSCENE_H
#define ATELIERPROG_LOADINGSCENE_H

#include "GraphicScene.h"

// S'occupe de créer la fenêtre et le renderer principal à partir des options
// charge les assets (son, image)
// affiche deux, trois logos histoire de faire pro!
class LoadingScene : public GraphicScene {
protected:
    int model() override;
    inline std::string descriptor() override {
        return "(LoadingScene)";
    }
public:
    int initialize() override;
    int quit() override;
};


#endif //ATELIERPROG_LOADINGSCENE_H
