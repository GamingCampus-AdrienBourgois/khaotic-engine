#include "positionclass.h"

PositionClass::PositionClass()
{
    m_frameTime = 0.0f;
    m_rotationY = 0.0f;
    m_rotationX = 0.0f;
    m_positionX = 0.0f;
    m_positionY = 0.0f;
    m_positionZ = 0.0f;
    m_leftTurnSpeed = 0.0f;
    m_rightTurnSpeed = 0.0f;
}


PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}

void PositionClass::SetFrameTime(float time)
{
    m_frameTime = time;
    return;
}

void PositionClass::GetRotation(float& y, float& x)
{
    y = m_rotationY;
    x = m_rotationX;
    return;
}

void PositionClass::GetPosition(float& x, float& y, float& z)
{
    x = m_positionX;
    y = m_positionY;
    z = m_positionZ;
    return;
}

void PositionClass::TurnLeft(bool keydown)
{
    // If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
    if (keydown)
    {
        m_leftTurnSpeed += m_frameTime * 1.5f;

        if (m_leftTurnSpeed > (m_frameTime * 200.0f))
        {
            m_leftTurnSpeed = m_frameTime * 200.0f;
        }
    }
    else
    {
        m_leftTurnSpeed -= m_frameTime * 1.0f;

        if (m_leftTurnSpeed < 0.0f)
        {
            m_leftTurnSpeed = 0.0f;
        }
    }

    // Update the rotation using the turning speed.
    m_rotationY -= m_leftTurnSpeed;
    if (m_rotationY < 0.0f)
    {
        m_rotationY += 360.0f;
    }

    return;
}


void PositionClass::TurnRight(bool keydown)
{
    // If the key is pressed increase the speed at which the camera turns right.  If not slow down the turn speed.
    if (keydown)
    {
        m_rightTurnSpeed += m_frameTime * 1.5f;

        if (m_rightTurnSpeed > (m_frameTime * 200.0f))
        {
            m_rightTurnSpeed = m_frameTime * 200.0f;
        }
    }
    else
    {
        m_rightTurnSpeed -= m_frameTime * 1.0f;

        if (m_rightTurnSpeed < 0.0f)
        {
            m_rightTurnSpeed = 0.0f;
        }
    }

    // Update the rotation using the turning speed.
    m_rotationY += m_rightTurnSpeed;
    if (m_rotationY > 360.0f)
    {
        m_rotationY -= 360.0f;
    }

    return;
}

void PositionClass::TurnMouse(float deltaX, float deltaY)
{
    // The turning speed is proportional to the horizontal mouse movement
    m_horizontalTurnSpeed = deltaX * 0.1f;

    // Update the rotation using the turning speed
    m_rotationY += m_horizontalTurnSpeed;
    if (m_rotationY < 0.0f)
    {
        m_rotationY += 360.0f;
    }
    else if (m_rotationY > 360.0f)
    {
        m_rotationY -= 360.0f;
    }

    // The turning speed is proportional to the vertical mouse movement
    m_verticalTurnSpeed = deltaY * 0.1f;

    // Update the rotation using the turning speed
    m_rotationX += m_verticalTurnSpeed;
    if (m_rotationX < -90.0f)
    {
        m_rotationX = -90.0f;
    }
    else if (m_rotationX > 90.0f)
    {
        m_rotationX = 90.0f;
    }

    return;
}

void PositionClass::MoveCamera(bool forward, bool backward, bool left, bool right, bool up, bool down)
{
	float radians;
	float speed;

	// Set the speed of the camera.
	speed = 0.1f;

	// Convert degrees to radians.
	radians = m_rotationY * 0.0174532925f;

	// Update the position.
    if (forward)
    {
		m_positionX += sinf(radians) * speed;
		m_positionZ += cosf(radians) * speed;
	}

    if (backward)
    {
		m_positionX -= sinf(radians) * speed;
		m_positionZ -= cosf(radians) * speed;
	}

    if (left)
    {
		m_positionX -= cosf(radians) * speed;
		m_positionZ += sinf(radians) * speed;
	}

    if (right)
    {
		m_positionX += cosf(radians) * speed;
		m_positionZ -= sinf(radians) * speed;
	}

    if (up)
    {
		m_positionY += speed;
	}

    if (down)
    {
		m_positionY -= speed;
	}

	return;
}