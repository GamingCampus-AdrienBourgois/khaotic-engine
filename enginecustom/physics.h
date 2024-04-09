#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "object.h"

class Physics : public Object
{
public:
    Physics();
    explicit Physics(const Physics&); // Use explicit to avoid implicit conversion
    ~Physics();

    XMVECTOR GetGravity(); // Get the gravity value
    void SetGravity(XMVECTOR gravity); // Define the gravity value
    void ApplyGravity(Object*, float); // Apply gravity to an object
    void ApplyDrag(Object*, float, float);

private:
    XMVECTOR m_gravity;
};

#endif