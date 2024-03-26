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