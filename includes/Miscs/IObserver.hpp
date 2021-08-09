/**********************************************************************************
* 
* 
* IObserver
*
* 
* Simple behavioral design pattern
* 
* This class must be used with ISubject class
* 
/**********************************************************************************/

#pragma once

class ISubject;

class IObserver
{
    public:
        virtual void update(ISubject *) = 0;
        virtual ~IObserver() {}
};