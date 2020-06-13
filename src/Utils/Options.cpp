//
// Created by mathis on 21/04/2020.
//

#include "Options.h"

void options::set_option(const std::string &key, const std::string &value) {
    opt[key] = value;
}

std::string options::get_option(const std::string &key) {
    return opt[key];
}

options::options() {
}

options::options(const std::string &nom) {
    parser par;
    opt = par.parser_read(nom);
}

void options::read(const std::string &nom) {
    parser par;
    opt = par.parser_read(nom);
}

void options::write(const std::string &nom) {
    parser par;
    par.parser_write(nom,opt);
}

void options::add_option(const std::string& key,const std::string& value) {
    opt.emplace(key,value);
}
