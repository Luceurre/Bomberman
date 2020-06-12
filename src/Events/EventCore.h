//
// Created by xdiam on 13/05/2020.
//

#ifndef ATELIERPROG_EVENTCORE_H
#define ATELIERPROG_EVENTCORE_H


#define BIT(x) (1 << x)

#define EVENT_CLASS_TYPE(type) static EventTypeManager::EventType GetStaticType() { return EventTypeManager::None; }\
								virtual EventTypeManager::EventType GetEventType() const  { return GetStaticType(); }\
								virtual const char* GetName() const  { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const { return category; }

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>

#include "Event.h"
#include "Callback.hpp"
#include "EventTests.h"
#include "KeyEvent.h"
#include "SDL.h"


#endif //ATELIERPROG_EVENTCORE_H
