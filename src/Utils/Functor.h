//
// Created by pglandon on 6/1/20.
//

#ifndef ATELIERPROG_FUNCTOR_H
#define ATELIERPROG_FUNCTOR_H

#include <stdexcept>
#include <string>

#define UNSET_CALL_ERROR "Attempting to invoke null callback."


// Functor taking 0 arguments, returning type R
// must be an object method
template<typename R>
class Functor0 {
public:
    template<typename C>
    Functor0(C* object, R (C::*method)()) {
        functor = new ChildMethod<C>(object, method);
    }

    R operator()() const {
        if (functor)
            return (*functor)();
        else
            throw std::runtime_error(UNSET_CALL_ERROR);
    }

private:
    // used to store functor, whatever the object type is!
    class Base {
    public:
        Base()= default;
        virtual R operator()() = 0;
    };

    template<typename C>
    class ChildMethod : public Base {
    public:
        ChildMethod(C* object, R (C::*method)()) {
            objCallee = object;
            methodCallee = method;
        }

        R operator()() override {
            return (objCallee->*methodCallee)();
        }

    private:
        C* objCallee;
        R (C::* methodCallee)();
    };

    Base* functor;
};

template<typename R, typename A0>
class Functor1 {
public:
    template<typename C>
    Functor1(C* object, R (C::*method)(A0 a0)) {
        functor = new ChildMethod<C>(object, method);
    }

    R operator()(A0 a0) const {
        if (functor)
            return (*functor)(a0);
        else
            throw std::runtime_error(UNSET_CALL_ERROR);
    }

private:
    // used to store functor, whatever the object type is!
    class Base {
    public:
        Base()= default;
        virtual R operator()(A0 a0) = 0;
    };

    template<typename C>
    class ChildMethod : public Base {
    public:
        ChildMethod(C* object, R (C::*method)(A0 a0)) {
            objCallee = object;
            methodCallee = method;
        }

        R operator()(A0 a0) override {
            return (objCallee->*methodCallee)(a0);
        }

    private:
        C* objCallee;
        R (C::* methodCallee)(A0 a0);
    };

    Base* functor;
};


#endif //ATELIERPROG_FUNCTOR_H
