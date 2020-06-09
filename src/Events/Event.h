//
// Created by pglandon on 6/8/20.
//

#ifndef BOMBERMAN_EVENT_H
#define BOMBERMAN_EVENT_H

#define EVENT_ID_SIZE 20

struct Event {
    // Permet d'identifier l'événement de manière unique lors de l'enregistrement
    char id[EVENT_ID_SIZE];

    inline friend bool operator==(const Event& r, const Event& l) {
        for (short i = 0; i < EVENT_ID_SIZE; ++i) {
            if (r.id[i] != l.id[i])
                return false;
        }
        return true;
    }

    inline friend bool operator<(const Event& r, const Event& l) {
        for (short i = 0; i < EVENT_ID_SIZE; ++i) {
            if (r.id[i] < l.id[i])
                return true;
            if (r.id[i] > l.id[i])
                return false;
        }

        return false;
    }
};


#endif //BOMBERMAN_EVENT_H
