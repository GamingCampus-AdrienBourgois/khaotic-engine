#include "physics.h"


Physics::Physics() 
{
    m_gravity = XMVectorSet(0.0f, -9.81f, 0.0f, 0.0f); // Initialize the gravity vector
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
void Physics::ApplyGravity(Object* object, float dragValue, float frameTime)
{
    if (object == nullptr) // Verify if the object is not null
    {
        return;
    }

    // Calculate the acceleration caused by gravity
    XMVECTOR gravityAcceleration = m_gravity / object->GetMass();

    // Add the gravity acceleration to the object's current acceleration
    object->SetAcceleration(object->GetAcceleration() + gravityAcceleration);

    // Calculate the acceleration caused by drag
    XMVECTOR dragAcceleration = -object->GetVelocity() * dragValue / object->GetMass();

    // Add the drag acceleration to the object's current acceleration
    object->SetAcceleration(object->GetAcceleration() + dragAcceleration);

    // Get the object velocity
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

bool Physics::IsColliding(Object* object1, Object* object2)
{

    if (object1 == nullptr || object2 == nullptr) // Verify if the objects are not null
    {
		return false;
	}

    // Get the positions of the two objects
    XMVECTOR position1 = object1->GetPosition();
    XMVECTOR position2 = object2->GetPosition();

    // Get the scale of the two objects (assuming the scale represents the size of the cube)
    XMVECTOR scale1 = object1->GetScale();
    XMVECTOR scale2 = object2->GetScale();

    // Calculate the min and max coordinates of the two cubes
    XMVECTOR min1 = position1 - scale1 / 2.0f;
    XMVECTOR max1 = position1 + scale1 / 2.0f;
    XMVECTOR min2 = position2 - scale2 / 2.0f;
    XMVECTOR max2 = position2 + scale2 / 2.0f;

    // Check if the two cubes overlap on all three axes
    bool overlapX = max1.m128_f32[0] > min2.m128_f32[0] && min1.m128_f32[0] < max2.m128_f32[0];
    bool overlapY = max1.m128_f32[1] > min2.m128_f32[1] && min1.m128_f32[1] < max2.m128_f32[1];
    bool overlapZ = max1.m128_f32[2] > min2.m128_f32[2] && min1.m128_f32[2] < max2.m128_f32[2];

    // If the cubes overlap on all three axes, they are colliding
    return overlapX && overlapY && overlapZ;
}
