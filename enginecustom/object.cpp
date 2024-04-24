#include "object.h"

Object::Object() : ModelClass()
{
	m_scaleMatrix = XMMatrixIdentity();
	m_rotateMatrix = XMMatrixIdentity();
	m_translateMatrix = XMMatrixIdentity();
	m_srMatrix = XMMatrixIdentity();
	m_worldMatrix = XMMatrixIdentity();
}

Object::~Object()
{
}

void Object::SetScaleMatrix(XMMATRIX scaleMatrix)
{
	m_scaleMatrix = scaleMatrix;
}

void Object::SetRotateMatrix(XMMATRIX rotateMatrix)
{
	m_rotateMatrix = rotateMatrix;
}

void Object::SetTranslateMatrix(XMMATRIX translateMatrix)
{
	m_translateMatrix = translateMatrix;
}

void Object::SetSRMatrix(XMMATRIX srMatrix)
{
	m_srMatrix = srMatrix;
}

void Object::SetWorldMatrix(XMMATRIX worldMatrix)
{
	m_worldMatrix = worldMatrix;
}

XMMATRIX Object::GetScaleMatrix()
{
	return m_scaleMatrix;
}

XMMATRIX Object::GetRotateMatrix()
{
	return m_rotateMatrix;
}

XMMATRIX Object::GetTranslateMatrix()
{
	return m_translateMatrix;
}

XMMATRIX Object::GetSRMatrix()
{
	return m_srMatrix;
}

XMMATRIX Object::GetWorldMatrix()
{
	return m_worldMatrix;
}

XMVECTOR Object::GetPosition()
{
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, m_translateMatrix);
	return XMVectorSet(matrix._41, matrix._42, matrix._43, 0.0f);
}

XMVECTOR Object::GetRotation()
{
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, m_rotateMatrix);
	float rotationX = atan2f(matrix._32, matrix._33);
	float rotationY = atan2f(-matrix._31, sqrtf(matrix._32 * matrix._32 + matrix._33 * matrix._33));
	float rotationZ = atan2f(matrix._21, matrix._11);
	return XMVectorSet(rotationX, rotationY, rotationZ, 0.0f);
}


XMVECTOR Object::GetScale()
{
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, m_scaleMatrix);
	float scaleX = XMVectorGetX(XMVector3Length(XMVectorSet(matrix._11, matrix._12, matrix._13, 0.0f)));
	float scaleY = XMVectorGetX(XMVector3Length(XMVectorSet(matrix._21, matrix._22, matrix._23, 0.0f)));
	float scaleZ = XMVectorGetX(XMVector3Length(XMVectorSet(matrix._31, matrix._32, matrix._33, 0.0f)));
	return XMVectorSet(scaleX, scaleY, scaleZ, 0.0f);
}

void Object::SetPosition(XMVECTOR position)
{
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, m_translateMatrix);
	matrix._41 = XMVectorGetX(position);
	matrix._42 = XMVectorGetY(position);
	matrix._43 = XMVectorGetZ(position);
	m_translateMatrix = XMLoadFloat4x4(&matrix);
}

void Object::SetRotation(XMVECTOR rotation)
{
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, m_rotateMatrix);
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(XMVectorGetX(rotation), XMVectorGetY(rotation), XMVectorGetZ(rotation));
	m_rotateMatrix = rotationMatrix;
}

void Object::SetScale(XMVECTOR scale)
{
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, m_scaleMatrix);
	matrix._11 = XMVectorGetX(scale);
	matrix._22 = XMVectorGetY(scale);
	matrix._33 = XMVectorGetZ(scale);
	m_scaleMatrix = XMLoadFloat4x4(&matrix);
}

void Object::UpdateWorldMatrix()
{
	m_worldMatrix = m_scaleMatrix * m_rotateMatrix * m_translateMatrix;
}

void Object::UpdateSRMatrix()
{
	m_srMatrix = m_scaleMatrix * m_rotateMatrix;
}

void Object::UpdateTranslateMatrix()
{
	m_translateMatrix = XMMatrixTranslationFromVector(GetPosition());
}

void Object::UpdateRotateMatrix()
{
	m_rotateMatrix = XMMatrixRotationRollPitchYawFromVector(GetRotation());
}

void Object::UpdateScaleMatrix()
{
	m_scaleMatrix = XMMatrixScalingFromVector(GetScale());
}

void Object::Update()
{
	UpdateWorldMatrix();
	UpdateSRMatrix();
	UpdateTranslateMatrix();
	UpdateRotateMatrix();
	UpdateScaleMatrix();
	ExecutePythonScript(GetScriptName());
}

std::string Object::GetName()
{
	return m_name;
}

void Object::SetName(std::string name)
{
	m_name = name;
}

void Object::ExecutePythonScript(const std::string& scriptName)
{
	Py_Initialize();
	try {
		boost::python::exec_file(scriptName.c_str(), boost::python::import("__main__").attr("__disct"));
	}
	catch (boost::python::error_already_set const&) {
		PyErr_Print();
	}
	Py_Finalize();
	
}

void Object::SetScriptName(const std::string scriptName)
{
	Logger::Get().Log("Script name set to: " + scriptName, __FILE__, __LINE__, Logger::LogLevel::Scripting);
	m_scriptName = scriptName;
}