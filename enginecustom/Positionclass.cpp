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
    m_horizontalTurnSpeed = 0.0f;
    m_verticalTurnSpeed = 0.0f;
    m_verticalTurnSpeed = 0.0f;
    m_cameraSpeed = 4.0f;
    m_speed = m_cameraSpeed;
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

void PositionClass::GetRotation(float& y, float& x) const
{
    y = m_rotationY;
    x = m_rotationX;
    return;
}

void PositionClass::GetPosition(float& x, float& y, float& z) const
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

void PositionClass::TurnMouse(float deltaX, float deltaY, float sensitivity, bool rightMouseDown)
{
    // The turning speed is proportional to the horizontal mouse movement
    m_horizontalTurnSpeed = deltaX * sensitivity;

    if (rightMouseDown)
    {
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
        m_verticalTurnSpeed = deltaY * sensitivity;

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
    }
    return;
}

void PositionClass::MoveCamera(bool forward, bool backward, bool left, bool right, bool up, bool down, bool scrollUp, bool scrollDown, bool rightClick)
{
    float radiansY, radiansX, speed;

    // Set the speed of the camera if the right click is down.
    if (scrollUp && rightClick)
    {
        m_cameraSpeed *= 1.1f;
    }
    if (scrollDown && rightClick)
    {
        m_cameraSpeed *= 0.9f;

        if (m_cameraSpeed < 0.25f) // Minimum speed.
        {
			m_cameraSpeed = 0.25f;
		}
	}

    // Convert degrees to radians.
    radiansY = m_rotationY * 0.0174532925f;
    radiansX = m_rotationX * 0.0174532925f;

    //////////////////////////
    // Update the position. //
    //////////////////////////

    // Moves the camera forward on a greater scale than the arrows.
    if (scrollUp && !rightClick)
    {
        speed = m_speed * 20 * m_frameTime;
        m_positionX += sinf(radiansY) * cosf(radiansX) * speed;
        m_positionZ += cosf(radiansY) * cosf(radiansX) * speed;
        m_positionY -= sinf(radiansX) * speed;
    }

    // Moves the camera backward on a greater scale than the arrows.
    if (scrollDown && !rightClick)
    {
        speed = m_speed * 20 * m_frameTime;
        m_positionX -= sinf(radiansY) * cosf(radiansX) * speed;
        m_positionZ -= cosf(radiansY) * cosf(radiansX) * speed;
        m_positionY += sinf(radiansX) * speed;
	}

    // Set the speed of the camera.
    speed = m_cameraSpeed * m_frameTime;

    // If moving forward, the position moves in the direction of the camera and accordingly to its angle.
    if (forward)
    {
        m_positionX += sinf(radiansY) * cosf(radiansX) * speed;
        m_positionZ += cosf(radiansY) * cosf(radiansX) * speed;
        m_positionY -= sinf(radiansX) * speed;
    }

    // If moving backward, the position moves in the opposite direction of the camera and accordingly to its angle.
    if (backward)
    {
        m_positionX -= sinf(radiansY) * cosf(radiansX) * speed;
        m_positionZ -= cosf(radiansY) * cosf(radiansX) * speed;
        m_positionY += sinf(radiansX) * speed;
    }

    // If moving left, the position moves to the left of the camera and accordingly to its angle.
    if (left)
    {
        m_positionX -= cosf(radiansY) * speed;
        m_positionZ += sinf(radiansY) * speed;
    }

    // If moving right, the position moves to the right of the camera and accordingly to its angle.
    if (right)
    {
        m_positionX += cosf(radiansY) * speed;
        m_positionZ -= sinf(radiansY) * speed;
    }

    // If moving up, the position moves up.
    if (up)
    {
		m_positionY += speed;
	}

    // If moving down, the position moves down.
    if (down)
    {
		m_positionY -= speed;
	}

	return;
}