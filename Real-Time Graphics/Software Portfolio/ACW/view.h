#pragma once

#include <directxmath.h>
#include <iostream>

using namespace std;
using namespace DirectX;

class View
{
public:
	View();
	View(const XMFLOAT3 &, const XMFLOAT3 &, const XMFLOAT3 &, const XMFLOAT3 &);
	View(const View &);
	View & operator = (const View &);
	View(const View &&);
	View & operator = (const View &&);
	~View();

	const XMMATRIX & GetViewMatrix() const
	{
		return m_ViewMatrix;
	}

	const float GetOutsidePositionX() const
	{
		return m_OutsidePosition.x;
	}

	const float GetOutsidePositionY() const
	{
		return m_OutsidePosition.y;
	}

	const float GetOutsidePositionZ() const
	{
		return m_OutsidePosition.z;
	}

	const float GetInsidePositionX() const
	{
		return m_InsidePosition.x;
	}

	const float GetInsidePositionY() const
	{
		return m_InsidePosition.y;
	}

	const float GetInsidePositionZ() const
	{
		return m_InsidePosition.z;
	}

	const float GetInitialPositionX() const
	{
		return m_InitialPosition.x;
	}

	const float GetInitialPositionY() const
	{
		return m_InitialPosition.y;
	}

	const float GetInitialPositionZ() const
	{
		return m_InitialPosition.z;
	}

	const float GetPositionX() const
	{
		return m_Position.x;
	}

	const float GetPositionY() const
	{
		return m_Position.y;
	}

	const float GetPositionZ() const
	{
		return m_Position.z;
	}

	const float GetOutsideRotationX() const
	{
		return m_OutsideRotation.x;
	}

	const float GetOutsideRotationY() const
	{
		return m_OutsideRotation.y;
	}

	const float GetOutsideRotationZ() const
	{
		return m_OutsideRotation.z;
	}

	const float GetInsideRotationX() const
	{
		return m_InsideRotation.x;
	}

	const float GetInsideRotationY() const
	{
		return m_InsideRotation.y;
	}

	const float GetInsideRotationZ() const
	{
		return m_InsideRotation.z;
	}

	const float GetInitialRotationX() const
	{
		return m_InitialRotation.x;
	}

	const float GetInitialRotationY() const
	{
		return m_InitialRotation.y;
	}

	const float GetInitialRotationZ() const
	{
		return m_InitialRotation.z;
	}

	const float GetRotationX() const
	{
		return m_Rotation.x;
	}

	const float GetRotationY() const
	{
		return m_Rotation.y;
	}

	const float GetRotationZ() const
	{
		return m_Rotation.z;
	}

	const XMFLOAT3 GetOutsidePosition() const
	{
		return XMFLOAT3(m_OutsidePosition.x, m_OutsidePosition.y, m_OutsidePosition.z);
	}

	const XMFLOAT3 GetInsidePosition() const
	{
		return XMFLOAT3(m_InsidePosition.x, m_InsidePosition.y, m_InsidePosition.z);
	}

	const XMFLOAT3 GetInitialPosition() const
	{
		return XMFLOAT3(m_InitialPosition.x, m_InitialPosition.y, m_InitialPosition.z);
	}

	const XMFLOAT3 GetPosition() const
	{
		return XMFLOAT3(m_Position.x, m_Position.y, m_Position.z);
	}

	const XMFLOAT3 GetOutsideRotation() const
	{
		return XMFLOAT3(m_OutsideRotation.x, m_OutsideRotation.y, m_OutsideRotation.z);
	}

	const XMFLOAT3 GetInsideRotation() const
	{
		return XMFLOAT3(m_InsideRotation.x, m_InsideRotation.y, m_InsideRotation.z);
	}

	const XMFLOAT3 GetInitialRotation() const
	{
		return XMFLOAT3(m_InitialRotation.x, m_InitialRotation.y, m_InitialRotation.z);
	}

	const XMFLOAT3 GetRotation() const
	{
		return XMFLOAT3(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	}

	void SetViewMatrix(const XMMATRIX &viewMatrix)
	{
		m_ViewMatrix = viewMatrix;
	}

	void SetOutsidePositionX(const float x)
	{
		m_OutsidePosition.x = x;
	}

	void SetOutsidePositionY(const float y)
	{
		m_OutsidePosition.y = y;
	}

	void SetOutsidePositionZ(const float z)
	{
		m_OutsidePosition.z = z;
	}

	void SetInsidePositionX(const float x)
	{
		m_InsidePosition.x = x;
	}

	void SetInsidePositionY(const float y)
	{
		m_InsidePosition.y = y;
	}

	void SetInsidePositionZ(const float z)
	{
		m_InsidePosition.z = z;
	}

	void SetInitialPositionX(const float x)
	{
		m_InitialPosition.x = x;
	}

	void SetInitialPositionY(const float y)
	{
		m_InitialPosition.y = y;
	}

	void SetInitialPositionZ(const float z)
	{
		m_InitialPosition.z = z;
	}

	void SetPositionX(const float x)
	{
		m_Position.x = x;
	}

	void SetPositionY(const float y)
	{
		m_Position.y = y;
	}

	void SetPositionZ(const float z)
	{
		m_Position.z = z;
	}

	void SetOutsideRotationX(const float x)
	{
		m_OutsideRotation.x = x;
	}

	void SetOutsideRotationY(const float y)
	{
		m_OutsideRotation.y = y;
	}

	void SetOutsideRotationZ(const float z)
	{
		m_OutsideRotation.z = z;
	}

	void SetInsideRotationX(const float x)
	{
		m_InsideRotation.x = x;
	}

	void SetInsideRotationY(const float y)
	{
		m_InsideRotation.y = y;
	}

	void SetInsideRotationZ(const float z)
	{
		m_InsideRotation.z = z;
	}

	void SetInitialRotationX(const float x)
	{
		m_InitialRotation.x = x;
	}

	void SetInitialRotationY(const float y)
	{
		m_InitialRotation.y = y;
	}

	void SetInitialRotationZ(const float z)
	{
		m_InitialRotation.z = z;
	}

	void SetRotationX(const float x)
	{
		m_Rotation.x = x;
	}

	void SetRotationY(const float y)
	{
		m_Rotation.y = y;
	}

	void SetRotationZ(const float z)
	{
		m_Rotation.z = z;
	}

	void SetOutsidePosition(const float x, const float y, const float z)
	{
		m_OutsidePosition = XMFLOAT3(x, y, z);
	}

	void SetInsidePosition(const float x, const float y, const float z)
	{
		m_InsidePosition = XMFLOAT3(x, y, z);
	}

	void SetInitialPosition(const float x, const float y, const float z)
	{
		m_InitialPosition = XMFLOAT3(x, y, z);
	}

	void SetPosition(const float x, const float y, const float z)
	{
		m_Position = XMFLOAT3(x, y, z);
	}

	void SetOutsideRotation(const float x, const float y, const float z)
	{
		m_OutsideRotation = XMFLOAT3(x, y, z);
	}

	void SetInsideRotation(const float x, const float y, const float z)
	{
		m_InsideRotation = XMFLOAT3(x, y, z);
	}

	void SetInitialRotation(const float x, const float y, const float z)
	{
		m_InitialRotation = XMFLOAT3(x, y, z);
	}

	void SetRotation(const float x, const float y, const float z)
	{
		m_Rotation = XMFLOAT3(x, y, z);
	}

	void SetViewToOutside()
	{
		m_InitialPosition = m_OutsidePosition;
		m_Position = m_OutsidePosition;

		m_InitialRotation = m_OutsideRotation;
		m_Rotation = m_OutsideRotation;
	}

	void SetViewToInside()
	{
		m_InitialPosition = m_InsidePosition;
		m_Position = m_InsidePosition;

		m_InitialRotation = m_InsideRotation;
		m_Rotation = m_InsideRotation;
	}

	void Update(const bool, const bool, const XMFLOAT3 &, const XMFLOAT3 &);
	void Render();

private:
	XMMATRIX m_ViewMatrix;
	XMFLOAT3 m_OutsidePosition, m_InsidePosition, m_InitialPosition, m_Position, m_OutsideRotation, m_InsideRotation, m_InitialRotation, m_Rotation;
};