#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "object.h"

class Physics
{
public:
    public:
    Physics();
    Physics(const Physics&);
    ~Physics();

    float GetGravity();
    void ApplyGravity(Object*, float);

private:
    float m_gravity;
};

#endif

