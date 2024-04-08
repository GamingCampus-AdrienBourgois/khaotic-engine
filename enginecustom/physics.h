#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "object.h"

class Physics : public Object
{
public:
    Physics();
    explicit Physics(const Physics&); // Use explicit to avoid implicit conversion
    ~Physics();

    float GetGravity(); // Get the gravity value
    void SetGravity(float gravity); // Define the gravity value
    void ApplyGravity(Object*, float); // Apply gravity to an object

private:
    float m_gravity;
};

#endif