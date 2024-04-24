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

    if (!object->GetGrounded()) // Verify if the object is grounded
    {
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
}

void Physics::AddForce(Object* object, XMVECTOR force)
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

    std::string type1 = object1->GetName();
    std::string type2 = object2->GetName();

    if (type1 == "cube" && type2 == "cube")
    {
        return CubesOverlap(object1, object2);
    }

    // Add more collision checks for other types of objects here...

    return false;
}

bool Physics::CubesOverlap(Object* cube1, Object* cube2)
{
    XMVECTOR position1 = cube1->GetPosition();
    XMVECTOR position2 = cube2->GetPosition();

    XMVECTOR scale1 = cube1->GetScale();
    XMVECTOR scale2 = cube2->GetScale();

    XMVECTOR min1 = position1 - scale1;
    XMVECTOR max1 = position1 + scale1;
    XMVECTOR min2 = position2 - scale2;
    XMVECTOR max2 = position2 + scale2;

    return (min1.m128_f32[0] <= max2.m128_f32[0] && max1.m128_f32[0] >= min2.m128_f32[0] &&
        min1.m128_f32[1] <= max2.m128_f32[1] && max1.m128_f32[1] >= min2.m128_f32[1] &&
        min1.m128_f32[2] <= max2.m128_f32[2] && max1.m128_f32[2] >= min2.m128_f32[2]);
}
