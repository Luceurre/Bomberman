//
// Created by pglandon on 4/17/20.
//

#ifndef ATELIERPROG_SCENE_H
#define ATELIERPROG_SCENE_H

#include <string>
#include <thread>
#include <mutex>
#include <thread>
#include <sstream>

#include <SDL.h>

#include "../Utils/Logger.h"

#define UNCAPPED 0
#define DEFAULT_FPS UNCAPPED
#define DEFAULT_MODEL_REFRESH_RATE 1

// Une scène le plus général possible.
// sert de base à l'ensemble de l'API
// ATTENTION : l'affichage DOIT se faire dans le thread principale ou SEGFAULT!!
// ATTENTION 2 : La gestion des évènements doit également être faites dans le thread principale!
// heureusement les évènements arrivent de façon désynchronisés donc should be OK.
enum SceneState {
    CREATED,
    INITIALIZED,
    RUNNING,
    STOPPED,
    DESTROYED,
    PAUSED
};

std::string scene_state_descriptor(SceneState sceneState);

class Scene : protected Logger {
public:
    // Nothing should be done here, virtual methods can't be called.
    Scene();
    // Change l'état de la scène. Thread friendly.
    void set_state(SceneState newSceneState);
    SceneState get_state();
    // Charge les images et les données relatives à la scène.
    virtual int initialize();
    // Quitte la scène, libère la mémoire.
    virtual int quit();
    // Lance 3 threads -> run_model, run_view et run_controller
    virtual int run();

    void set_fps(int fps);
    void set_model_refresh_rate(int model_refresh_rate);
protected:
    std::string descriptor() override;


    // Fonctions de lancement et de gestions des threads
    int run_model();
    int run_view();
    int run_controller();

    // Fonctions propres à chaque scène
    virtual int model();
    virtual int view();
    virtual int controller();

    // Multithreading
    // On va peut être devoir utiliser le thread principal pour l'affichage... à voir....
    std::thread thread_model;
    std::thread thread_view;
    std::thread thread_controller;

    // Permet la gestion propre des threads entre la vue et le modèle
    std::mutex mtx_state;
    std::mutex mtx_data;
private:
    // L'état dans lequel se trouve la scène.
    SceneState sceneState;
    // à quelle fréquence la logique de la scène doit s'effectuer.
    int model_refresh_rate;
    int model_loop_time_ms;
    // Combien d'image par seconde est attendu, peut être infini si défini par UNCAPPED
    int fps;
    int view_loop_time_ms;
};


#endif //ATELIERPROG_SCENE_H
