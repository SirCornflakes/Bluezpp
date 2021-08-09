/**********************************************************************************
* 
* 
* ISubject
*
* 
* Simple behavioral design pattern
* 
* This class must be used with IObserver class
* 
/**********************************************************************************/

#pragma once

#include <list>
#include <memory>

#include "Miscs/IObserver.hpp"

class ISubject
{
    public:
        virtual void attach(IObserver *) = 0;
        virtual void detach(IObserver *) = 0;
        virtual void notifyAll() = 0;
        virtual ~ISubject() {};
};