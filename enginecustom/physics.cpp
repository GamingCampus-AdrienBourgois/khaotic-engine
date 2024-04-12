#include "physics.h"


Physics::Physics() : m_gravity(XMVectorSet(0.0f, -9.81f, 0.0f, 0.0f)) // Initialize the gravity vector
{
}

Physics::Physics(const Physics& other)
{
	m_gravity = other.m_gravity; // Copy the gravity value
}

Physics::~Physics()
{
}

// Get the gravity value
XMVECTOR Physics::GetGravity() const
{
	return m_gravity;
}

// Define the gravity value
void Physics::SetGravity(XMVECTOR gravity)
{
	m_gravity = gravity;
}

// Apply gravity to an object
void Physics::ApplyGravity(Object* object, float frameTime)
{
    if (object == nullptr) // Verify if the object is not null
    {
        return;
    }

    // Calculate the acceleration caused by gravity
    XMVECTOR gravityAcceleration = m_gravity / object->GetMass();

    // Add the gravity acceleration to the object's current acceleration
    object->SetAcceleration(object->GetAcceleration() + gravityAcceleration);

    // Get the object velocity
    XMVECTOR velocity = object->GetVelocity();

    // Update the velocity with the object's acceleration
    velocity += object->GetAcceleration() * frameTime;

    // Set the new velocity
    object->SetVelocity(velocity);
}

void Physics::ApplyDrag(Object* object, float dragValue, float frameTime)
{
    if (object == nullptr) // Verify if the object is not null
    {
        return;
    }

    // Calculate the acceleration caused by drag
    XMVECTOR dragAcceleration = -object->GetVelocity() * dragValue / object->GetMass();

    // Add the drag acceleration to the object's current acceleration
    object->SetAcceleration(object->GetAcceleration() + dragAcceleration);

    // Get the velocity of the object
    XMVECTOR velocity = object->GetVelocity();

    // Update the velocity with the object's acceleration
    velocity += object->GetAcceleration() * frameTime;

    // Set the new velocity
    object->SetVelocity(velocity);
}

void Physics::ApplyForce(Object* object, XMVECTOR force)
{
	if (object == nullptr) // Verify if the object is not null
	{
		return;
	}

	// Get the mass of the object
	float mass = object->GetMass();

	// Calculate the acceleration caused by the force
	XMVECTOR acceleration = force / mass;

	// Add the acceleration to the object's current acceleration
	object->SetAcceleration(object->GetAcceleration() + acceleration);
}