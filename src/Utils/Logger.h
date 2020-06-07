//
// Created by pglandon on 4/17/20.
//

#ifndef ATELIERPROG_LOGGER_H
#define ATELIERPROG_LOGGER_H

#include <string>
#include <mutex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL.h>

#define LOG_FILE_PATH "logs/"

class Logger {
public:
    static inline void closeLogFile() {
        logFile.close();
    }
protected:
    enum LogLevel {
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    static LogLevel logLevel;
    static std::mutex mtx;
    static std::ofstream logFile;

    static std::string timestamp();
    static std::string pointer_str(void* ptr);

    // Generate a string that can describe the class. Should be override.
    virtual std::string descriptor();

    // Generate a string that describe the error level.
    static std::string error_descriptor(LogLevel ll);

    // Modifie le message pour le rendre plus compréhensible, ajoute les infos sur l'objet, la date, etc...
    void parse_log_message(LogLevel ll, std::string& msg);

    // Ajoute au log le message en fonction de la sévérité.
    void log(LogLevel ll, const std::string& msg);

    // Des p'tites fonctions pour éviter d'avoir à spécifier le niveau de log du message.
    void info(const std::string& msg);
    void warn(const std::string& msg);
    void error(const std::string& msg);
    void fatal(const std::string& msg);
    // Generate s string that can describe the object (by default memory address).
    std::string object_descriptor();

    static void static_log(LogLevel ll, const std::string& msg);
};


#endif //ATELIERPROG_LOGGER_H
