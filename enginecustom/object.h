#pragma once
#include "modelclass.h"

class Object : public ModelClass
{
public:
	Object();
	~Object();

	void SetScaleMatrix(XMMATRIX scaleMatrix);
	void SetRotateMatrix(XMMATRIX rotateMatrix);
	void SetTranslateMatrix(XMMATRIX translateMatrix);
	void SetSRMatrix(XMMATRIX srMatrix);
	void SetWorldMatrix(XMMATRIX worldMatrix);

	void SetPosition(XMVECTOR position);
	void SetRotation(XMVECTOR rotation);
	void SetScale(XMVECTOR scale);

	XMMATRIX GetScaleMatrix();
	XMMATRIX GetRotateMatrix();
	XMMATRIX GetTranslateMatrix();
	XMMATRIX GetSRMatrix();
	XMMATRIX GetWorldMatrix();

	XMVECTOR GetPosition();
	XMVECTOR GetRotation();
	XMVECTOR GetScale();

	void SetVelocity(XMVECTOR);
	XMVECTOR GetVelocity();

	void UpdateWorldMatrix();
	void UpdateSRMatrix();
	void UpdateScaleMatrix();
	void UpdateRotateMatrix();
	void UpdateTranslateMatrix();

	void Update();

	std::string GetName();
	void SetName(std::string name);

public :
	bool m_demoSpinning = false;
	XMVECTOR m_previousPosition;
	XMVECTOR m_velocity;

private:
	XMMATRIX m_scaleMatrix;
	XMMATRIX m_rotateMatrix;
	XMMATRIX m_translateMatrix;
	XMMATRIX m_srMatrix;
	XMMATRIX m_worldMatrix;

	std::string m_name;
};
