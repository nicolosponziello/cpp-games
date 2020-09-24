#ifndef COMP
#define COMP

#include "Actor.h"

class Component 
{
    public:
        //update order is the priority with which to update
        Component(class Actor* owner, int updateOrder = 100);
        virtual ~Component();
        virtual void Update(float deltaTime);
        int GetUpdateOrder() const {
            return mUpdateOrder;
        }
    protected:
        class Actor* mOwner;
        int mUpdateOrder;
};

#endif