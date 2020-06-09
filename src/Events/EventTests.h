//
// Created by xdiam on 14/05/2020.
//

#ifndef ATELIERPROG_EVENTTESTS_H
#define ATELIERPROG_EVENTTESTS_H
#include "EventCore.h"


class Dog {
public:
    void notify(Event& e) {
        std::cout<<"Je notifie tmtc"<<std::endl;
    }
};

class Cat {
public:
    void notify(Event& e) {
        std::cout<<"Wallah c'est moi le 2"<<std::endl;
    }
};

#endif //ATELIERPROG_EVENTTESTS_H
