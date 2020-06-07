//
// Created by pglan on 20/04/2020.
//

#include "WindowManager.h"

WindowManager::WindowManager() {
    hasPrimary = false;
    primaryWindow = nullptr;
}

void WindowManager::add_window(Window *window) {
    for(auto* win : windows) {
        if(win == window) {
            std::string msg = "La fenêtre a déjà été ajouté!";
            error(msg);
            return;
        }
    }

    std::string msg = "Ajout de la fenêtre " + Logger::pointer_str(window);
    info(msg);
    windows.push_back(window);
}

void WindowManager::add_primary_window(Window *window) {
    hasPrimary = true;
    primaryWindow = window;

    add_window(window);

    std::string msg = "La fenêtre principale est " + Logger::pointer_str(window);
    info(msg);
}

std::string WindowManager::descriptor() {
    return "(WindowManager)";
}

Window *WindowManager::get_primary_window() {
    if(hasPrimary) {
        return primaryWindow;
    } else {
        std::string msg("Pas de fenêtre principale!");
        error(msg);
        return nullptr;
    }
}
