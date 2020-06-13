//
// Created by pglandon on 6/12/20.
//

#ifndef BOMBERMAN_OPTIONSMANAGER_H
#define BOMBERMAN_OPTIONSMANAGER_H


#include "../Utils/Logger.h"

class OptionsManager : public Logger {
protected:
    inline std::string descriptor() override {
        return "(OptionsManager)";
    }

    inline OptionsManager() = default;

public:
    int sizeMultiplier = 1;

    static OptionsManager& getInstance()
    {
        static OptionsManager instance;
        return instance;
    }

    OptionsManager(OptionsManager const&) = delete;
    void operator=(OptionsManager const&) = delete;
};


#endif //BOMBERMAN_OPTIONSMANAGER_H
