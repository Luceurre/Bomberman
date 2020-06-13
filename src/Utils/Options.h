//
// Created by mathis on 21/04/2020.
//

#ifndef ATELIERPROG_OPTIONS_H
#define ATELIERPROG_OPTIONS_H

#include "Parser.h"

class options : protected parser{
private:
    std::map<std::string, std::string> opt;

public:
    options(options const&)               = delete;
    void operator=(options const&)  = delete;

    options(); //Empty constructor for options
    explicit options(const std::string& nom);    //Constructor based on file reading

    void read(const std::string& nom);  //Method to redefine opt from a file
    void write(const std::string& nom); //Method to write file from opt
    void set_option(const std::string& key,const std::string& value);    //Change an option value
    std::string get_option(const std::string& key);     //Get a current option value
    void add_option(const std::string& key,const std::string& value);
};


#endif //ATELIERPROG_OPTIONS_H
