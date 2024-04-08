#include "physics.h"

Physics::Physics()
{
	m_gravity = -9.81f;
}


Physics::Physics(const Physics& other)
{
	m_gravity = other.m_gravity; // Copy gravity value from the other object
}


Physics::~Physics()
{
}

float Physics::GetGravity() // Changed the method to return the gravity value
{
	return m_gravity;
}

void Physics::ApplyGravity(Object* object, float frameTime)
{
	// Update the position of the object by adding the change in position due to gravity.
	XMVECTOR position = object->GetPosition(); // Get the current position
	position = XMVectorSetY(position, XMVectorGetY(position) + m_gravity * frameTime); // Update the y value
	object->SetPosition(position); // Set the updated position

	return;
}