//
// Created by Mathis on 21/04/2020.
//

#ifndef ATELIERPROG_PARSER_H
#define ATELIERPROG_PARSER_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "Logger.h"

//Parser Class to read/write from an unordered_map to .txt
//Use ; in txt to separate key from value

class parser : protected Logger{
public:
    void parser_write(const std::string& nom,const std::map<std::string,std::string>& dico); //Function to write from dico in nom.txt
    std::map<std::string,std::string> parser_read(const std::string& nom);            //Function to read form nom.txt in dico

    std::string descriptor() override;
};



#endif //ATELIERPROG_PARSER_H
