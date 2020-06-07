//
// Created by pglan on 20/04/2020.
//

#ifndef ATELIERPROG_WINDOWMANAGER_H
#define ATELIERPROG_WINDOWMANAGER_H

#include <vector>

#include "../Windows/Window.h"
#include "../Utils/Logger.h"

// Singleton class to manage windows between scene.
class WindowManager : protected Logger {
private:
    bool hasPrimary;
    Window* primaryWindow;
    std::vector<Window*> windows;

protected:
    std::string descriptor() override;
public:
    static WindowManager& getInstance()
    {
        static WindowManager instance;
        return instance;
    }
    WindowManager(WindowManager const&) = delete;
    void operator=(WindowManager const&) = delete;

    void add_window(Window* window);
    void add_primary_window(Window* window);
    Window* get_primary_window();
    WindowManager();
};


#endif //ATELIERPROG_WINDOWMANAGER_H
