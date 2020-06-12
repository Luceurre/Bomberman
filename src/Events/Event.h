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

    inline static EventType   None                = 0,
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

struct Event {
public:
    // to identify the event type.
    std::string id;
    EventTypeManager::EventType eventType = EventTypeManager::None;

    inline friend bool operator==(Event l, Event r) {
        return l.id == r.id;
    }

    inline EventTypeManager::EventType GetEventType() {
        return eventType;
    }
};

struct SDLEvent : public Event {
public:
    SDL_Event event;

    inline SDLEvent(SDL_Event e) {
        id = "SDL";
        event = e;
    }

    inline friend bool operator==(SDLEvent l, SDLEvent r) {
        return l.event.type == r.event.type;
    }
};



#define KEY_PRESSED_EVENT(key,sender)   Event key_pressed_##key\
                                        key_pressed_##key.senderIdentity    = sender\
                                        key_pressed_##key.intData           = key\
                                        key_pressed_##key.type              = KeyPressed\
                                        key_pressed_##key.category          = EventCategoryKeyboard | EventCategoryInput



#endif //ATELIERPROG_EVENT_H
