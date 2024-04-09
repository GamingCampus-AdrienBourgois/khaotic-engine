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
XMVECTOR Physics::GetGravity()
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

	// Get the object velocity
	XMVECTOR velocity = object->GetVelocity();

	// Update the velocity with gravity
	velocity += m_gravity * frameTime;

	// Set the new velocity
	object->SetVelocity(velocity);
}

void Physics::ApplyDrag(Object* object, float dragValue, float frameTime)
{
	if (object == nullptr) // Verify if the object is not null
	{
		return;
	}

	// Get the velocity of the object
	XMVECTOR velocity = object->GetVelocity();

	// Calculate the new velocity
	XMVECTOR newVelocity = velocity - (velocity * dragValue * frameTime);

	// Update the velocity of the object
	object->SetVelocity(newVelocity);
}