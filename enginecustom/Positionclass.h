#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: PositionClass
////////////////////////////////////////////////////////////////////////////////
class PositionClass
{
public:
    PositionClass();
    PositionClass(const PositionClass&);
    ~PositionClass();

    void SetFrameTime(float);
    void GetRotation(float&, float&) const;
    void GetPosition(float&, float&, float&) const;

    void TurnLeft(bool);
    void TurnRight(bool);
    void TurnMouse(float, float, float, bool);
    void MoveCamera(bool, bool, bool, bool, bool, bool, bool, bool, bool);

private:
    float m_frameTime;
    float m_rotationY, m_rotationX;
    float m_positionX, m_positionY, m_positionZ;
    float m_leftTurnSpeed, m_rightTurnSpeed, m_horizontalTurnSpeed, m_verticalTurnSpeed, m_cameraSpeed, m_speed;
};

#endif