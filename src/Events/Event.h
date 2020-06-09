//
// Created by xdiam on 13/05/2020.
//

#ifndef ATELIERPROG_EVENT_H
#define ATELIERPROG_EVENT_H

#include "EventCore.h"


class EventTypeManager
{
public:
    typedef int EventType;

    inline static EventType cursor = 0;

    inline static EventType NextEventType() {return cursor + 1;}

    static EventType RegisterEventType()
    {
        cursor = NextEventType();
        return cursor;
    };

    EventType   None                = 0,
                WindowClose         = RegisterEventType(),
                WindowResize        = RegisterEventType(),
                WindowFocus         = RegisterEventType(),
                WindowLostFocus     = RegisterEventType(),
                WindowMoved         = RegisterEventType(),
                AppTick             = RegisterEventType(),
                AppUpdate           = RegisterEventType(),
                AppRender           = RegisterEventType(),
                KeyPressed          = RegisterEventType(),
                KeyReleased         = RegisterEventType(),
                KeyTyped            = RegisterEventType(),
                MouseButtonPressed  = RegisterEventType(),
                MouseButtonReleased = RegisterEventType(),
                MouseMoved          = RegisterEventType(),
                MouseScrolled       = RegisterEventType();
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication    = BIT(0),
    EventCategoryInput          = BIT(1),
    EventCategoryKeyboard       = BIT(2),
    EventCategoryMouse          = BIT(3),
    EventCategoryMouseButton    = BIT(4)
};

class Event {
public:
    int32_t senderIdentity;
    int32_t intData,
            intData2;
    bool state;
    char buffer[256];
    EventTypeManager::EventType type;
    EventCategory category;
    void* special_data;

    Event() {
        senderIdentity = 0;
        intData = 0;
        intData2 = 0;
        state = false;
    }
};



#define KEY_PRESSED_EVENT(key,sender)   Event key_pressed_##key\
                                        key_pressed_##key.senderIdentity    = sender\
                                        key_pressed_##key.intData           = key\
                                        key_pressed_##key.type              = KeyPressed\
                                        key_pressed_##key.category          = EventCategoryKeyboard | EventCategoryInput



#endif //ATELIERPROG_EVENT_H
