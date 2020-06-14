//
// Created by pglandon on 4/17/20.
//

#include "Scene.h"

void Scene::set_state(SceneState newSceneState) {
    // const std::lock_guard<std::mutex> lock(this->mtx_state);

    std::string log_msg = "Scene went from " + scene_state_descriptor(this->sceneState) + " to " + scene_state_descriptor(newSceneState);
    this->log(Logger::LogLevel::INFO, log_msg);

    this->sceneState = newSceneState;
}

Scene::Scene() {
    this->sceneState = CREATED;

    this->model_refresh_rate = DEFAULT_MODEL_REFRESH_RATE;
    this->model_loop_time_ms = 1000 / DEFAULT_MODEL_REFRESH_RATE;
    this->fps = UNCAPPED;
    this->view_loop_time_ms = 0;
}

std::string Scene::descriptor() {
    return "(Scene)";
}

int Scene::initialize() {
    this->set_state(INITIALIZED);

    return 0;
}

int Scene::run() {
    std::string msg;
    if (this->get_state() == CREATED) {
        msg = "La scène n'a pas été initialisé avant!";
        this->warn(msg);
    }

    this->set_state(RUNNING);

    // this->thread_model = std::thread(&Scene::run_model, this);
    // this->thread_view = std::thread(&Scene::run_view, this);
    // this->thread_controller = std::thread(&Scene::run_controller, this);

    // On lance la vue dans le thread principal:
    // this->run_view();
    this->run_model();

    msg = "Waiting for threads to end...";
    this->info(msg);

    if (this->thread_model.joinable())
        this->thread_model.join();
    // this->thread_view.join();
    // this->thread_controller.join();

    msg = "Threads ended.";
    this->info(msg);

    this->quit();

    return 0;
}

int Scene::run_controller() {
    return 0;
}

int Scene::run_view() {
    int currentTime = SDL_GetTicks();
    int lastTime = 0;
    std::string msg;

    while (this->get_state() == RUNNING) {
        lastTime = currentTime;

        // Call the things to do...
        this->controller();
        this->view();
        this->controller();

        currentTime = SDL_GetTicks();
        int elapsed_time = currentTime - lastTime; // Temps passé à faire des trucs en ms
        if (this->fps != UNCAPPED) {
            if (elapsed_time <= this->view_loop_time_ms) {
                msg = "Waiting " + std::to_string(this->model_loop_time_ms - elapsed_time) + "ms";
                this->info(msg);
                SDL_Delay(this->model_loop_time_ms - elapsed_time);
                currentTime = SDL_GetTicks();
            } else {
                msg = "Can't keep up, run_view is " + std::to_string(elapsed_time - this->model_loop_time_ms) +
                      "ms late!";
                this->warn(msg);
            }
        }
    }

    return 0;
}

int Scene::run_model() {
    int currentTime = SDL_GetTicks();
    int lastTime = 0;
    std::string msg;

    while (this->get_state() == RUNNING) {
        lastTime = currentTime;

        // Call the things to do...
        this->model();
        this->view();

        currentTime = SDL_GetTicks();
        int elapsed_time = currentTime - lastTime; // Temps passé à faire des trucs en ms
        if(elapsed_time <= this->model_loop_time_ms) {
            msg = "Waiting " + std::to_string(this->model_loop_time_ms - elapsed_time) + "ms";
            // Juste pour vérifier la précision de l'horloge.
            // this->info(msg);
            SDL_Delay(this->model_loop_time_ms - elapsed_time);
            currentTime = SDL_GetTicks();
        } else {
            msg = "Can't keep up, run_model is "  + std::to_string(elapsed_time - this->model_loop_time_ms) + "ms late!";
            this->warn(msg);
        }
    }

    return 0;
}

SceneState Scene::get_state() {
    return this->sceneState;
}

int Scene::controller() {
    return 0;
}

int Scene::view() {
    return 0;
}

int Scene::model() {
    return 0;
}

void Scene::set_fps(int fps) {
    std::string log_msg;
    if (fps == UNCAPPED) {
        log_msg = "FPS set to UNCAPPED";
    } else {
        log_msg = "FPS set to " + std::to_string(fps);
    }
    this->info(log_msg);
    this->fps = fps;
    if (fps == UNCAPPED) {
        this->view_loop_time_ms = 0;
    } else {
        this->view_loop_time_ms = 1000 / fps;
    }
}

void Scene::set_model_refresh_rate(int model_refresh_rate) {
    std::string log_msg;

    log_msg = "Model refresh rate set to " + std::to_string(model_refresh_rate) +"Hz";
    this->info(log_msg);

    this->model_refresh_rate = model_refresh_rate;
    this->model_loop_time_ms = 1000 / model_refresh_rate;
}

int Scene::quit() {
    return 0;
}

std::string scene_state_descriptor(SceneState sceneState) {
    switch (sceneState) {
        case CREATED:
            return "CREATED";
        case DESTROYED:
            return "DESTROYED";
        case INITIALIZED:
            return "INITIALIZED";
        case RUNNING:
            return "RUNNING";
        case STOPPED:
            return "STOPPED";
        case PAUSED:
            return "PAUSED";
        default:
            return "";
    }
}
