#include "physics.h"


Physics::Physics()
{
	m_gravity = -9.81f; // Initilize the gravity value
}

Physics::Physics(const Physics& other)
{
	m_gravity = other.m_gravity; // Copy the gravity value
}

Physics::~Physics()
{
}

// Get the gravity value
float Physics::GetGravity()
{
	return m_gravity;
}

// Define the gravity value
void Physics::SetGravity(float gravity)
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

	// Update the object position
	XMVECTOR position = object->GetPosition();
	position = XMVectorSetY(position, XMVectorGetY(position) + m_gravity * frameTime); // Update the Y position
	object->SetPosition(position);
}