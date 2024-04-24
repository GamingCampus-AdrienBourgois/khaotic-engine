#pragma once
#include "modelclass.h"
#include <Python.h>

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

	void UpdateWorldMatrix();
	void UpdateSRMatrix();
	void UpdateScaleMatrix();
	void UpdateRotateMatrix();
	void UpdateTranslateMatrix();

	void Update();

	std::string GetName();
	void SetName(std::string name);

	// SCRIPTING FUNCTIONS // 
	std::string GetScriptName() const { return m_scriptName; }
	void SetScriptName(const std::string scriptName);
	void ExecuteScript();

public :
	bool m_demoSpinning = false;

private:
	XMMATRIX m_scaleMatrix;
	XMMATRIX m_rotateMatrix;
	XMMATRIX m_translateMatrix;
	XMMATRIX m_srMatrix;
	XMMATRIX m_worldMatrix;

	std::string m_name;
	std::string m_scriptName;

};
