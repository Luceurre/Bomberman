//
// Created by pglandon on 4/17/20.
//

#include "Logger.h"

Logger::LogLevel Logger::logLevel = Logger::LogLevel::INFO;
std::mutex Logger::mtx;
std::ofstream Logger::logFile;

std::string Logger::descriptor() {
    return "(Logger)";
}

std::string Logger::object_descriptor() {
    return Logger::pointer_str(this);
}

std::string Logger::error_descriptor(Logger::LogLevel ll) {
    switch (ll) {
        case INFO:
            return "[INFO]";
        case WARNING:
            return "[WARNING]";
        case ERROR:
            return "[ERROR]";
        case FATAL:
            return "[FATAL]";
        default:
            return "";
    }
}

void Logger::parse_log_message(Logger::LogLevel ll, std::string& msg) {
    msg = error_descriptor(ll) + " " + descriptor() + " " + object_descriptor() + " " + Logger::timestamp() + " " + msg;
}

void Logger::log(Logger::LogLevel ll, const std::string& msg) {
    if (!Logger::logFile.is_open()) {
        auto seconds  = time(NULL);
        logFile.open(LOG_FILE_PATH + std::to_string(seconds) + ".log");
    }
    if(ll >= Logger::logLevel) {
        const std::lock_guard<std::mutex> lock(Logger::mtx);
        std::string copy = msg;
        this->parse_log_message(ll, copy);
        std::cout << copy << std::endl;
        logFile << copy << std::endl;
    }
}

void Logger::info(const std::string& msg) {
    this->log(Logger::LogLevel::INFO, msg);
}

void Logger::warn(const std::string& msg) {
    this->log(Logger::LogLevel::WARNING, msg);
}

void Logger::error(const std::string& msg) {
    this->log(Logger::LogLevel::ERROR, msg);
}

void Logger::fatal(const std::string& msg) {
    this->log(Logger::LogLevel::FATAL, msg);
}

std::string Logger::timestamp() {
    return "(" + std::to_string(SDL_GetTicks()) + ")";
}

std::string Logger::pointer_str(void* ptr) {
    std::stringstream ss;
    ss << ptr;
    return "{" + ss.str() + "}";
}

void Logger::static_log(LogLevel ll, const std::string& msg) {
    // Tout ce qui se passe ici, reste ici
    Logger l;
    l.log(ll, msg);
}
