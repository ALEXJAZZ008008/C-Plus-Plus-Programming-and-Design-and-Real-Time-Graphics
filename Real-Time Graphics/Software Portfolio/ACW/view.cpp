#include "view.h"

View::View() : m_ViewMatrix(), m_OutsidePosition(), m_InsidePosition(), m_InitialPosition(), m_Position(), m_OutsideRotation(), m_InsideRotation(), m_InitialRotation(), m_Rotation()
{

}

View::View(const XMFLOAT3 &outsidePosition, const XMFLOAT3 &insidePosition, const XMFLOAT3 &outsideRotation, const XMFLOAT3 &insideRotation) : m_ViewMatrix(), m_OutsidePosition(outsidePosition), m_InsidePosition(insidePosition), m_InitialPosition(), m_Position(), m_OutsideRotation(outsideRotation), m_InsideRotation(insideRotation), m_InitialRotation(), m_Rotation()
{

}

View::View(const View &view) : m_ViewMatrix(view.GetViewMatrix()), m_OutsidePosition(XMFLOAT3(view.GetOutsidePositionX(), view.GetOutsidePositionY(), view.GetOutsidePositionZ())), m_InsidePosition(XMFLOAT3(view.GetInsidePositionX(), view.GetInsidePositionY(), view.GetInsidePositionZ())), m_InitialPosition(XMFLOAT3(view.GetInitialPositionX(), view.GetInitialPositionY(), view.GetInitialPositionZ())), m_Position(XMFLOAT3(view.GetPositionX(), view.GetPositionY(), view.GetPositionZ())), m_OutsideRotation(XMFLOAT3(view.GetOutsideRotationX(), view.GetOutsideRotationY(), view.GetOutsideRotationZ())), m_InsideRotation(XMFLOAT3(view.GetInsideRotationX(), view.GetInsideRotationY(), view.GetInsideRotationZ())), m_InitialRotation(XMFLOAT3(view.GetInitialRotationX(), view.GetInitialRotationY(), view.GetInitialRotationZ())), m_Rotation(XMFLOAT3(view.GetRotationX(), view.GetRotationY(), view.GetRotationZ()))
{

}

View & View::operator = (const View &view)
{
	if (this != &view)
	{
		m_ViewMatrix = view.GetViewMatrix();

		m_OutsidePosition = XMFLOAT3(view.GetOutsidePositionX(), view.GetOutsidePositionY(), view.GetOutsidePositionZ());
		m_InsidePosition = XMFLOAT3(view.GetInsidePositionX(), view.GetInsidePositionY(), view.GetInsidePositionZ());
		m_InitialPosition = XMFLOAT3(view.GetInitialPositionX(), view.GetInitialPositionY(), view.GetInitialPositionZ());
		m_Position = XMFLOAT3(view.GetPositionX(), view.GetPositionY(), view.GetPositionZ());
		m_OutsideRotation = XMFLOAT3(view.GetOutsideRotationX(), view.GetOutsideRotationY(), view.GetOutsideRotationZ());
		m_InsideRotation = XMFLOAT3(view.GetInsideRotationX(), view.GetInsideRotationY(), view.GetInsideRotationZ());
		m_InitialRotation = XMFLOAT3(view.GetInitialRotationX(), view.GetInitialRotationY(), view.GetInitialRotationZ());
		m_Rotation = XMFLOAT3(view.GetRotationX(), view.GetRotationY(), view.GetRotationZ());
	}
	
	return *this;
}

View::View(const View &&view) : m_ViewMatrix(view.GetViewMatrix()), m_OutsidePosition(XMFLOAT3(view.GetOutsidePositionX(), view.GetOutsidePositionY(), view.GetOutsidePositionZ())), m_InsidePosition(XMFLOAT3(view.GetInsidePositionX(), view.GetInsidePositionY(), view.GetInsidePositionZ())), m_InitialPosition(XMFLOAT3(view.GetInitialPositionX(), view.GetInitialPositionY(), view.GetInitialPositionZ())), m_Position(XMFLOAT3(view.GetPositionX(), view.GetPositionY(), view.GetPositionZ())), m_OutsideRotation(XMFLOAT3(view.GetOutsideRotationX(), view.GetOutsideRotationY(), view.GetOutsideRotationZ())), m_InsideRotation(XMFLOAT3(view.GetInsideRotationX(), view.GetInsideRotationY(), view.GetInsideRotationZ())), m_InitialRotation(XMFLOAT3(view.GetInitialRotationX(), view.GetInitialRotationY(), view.GetInitialRotationZ())), m_Rotation(XMFLOAT3(view.GetRotationX(), view.GetRotationY(), view.GetRotationZ()))
{

}

View & View::operator = (const View &&view)
{
	if (this != &view)
	{
		m_ViewMatrix = view.GetViewMatrix();

		m_OutsidePosition = XMFLOAT3(view.GetOutsidePositionX(), view.GetOutsidePositionY(), view.GetOutsidePositionZ());
		m_InsidePosition = XMFLOAT3(view.GetInsidePositionX(), view.GetInsidePositionY(), view.GetInsidePositionZ());
		m_InitialPosition = XMFLOAT3(view.GetInitialPositionX(), view.GetInitialPositionY(), view.GetInitialPositionZ());
		m_Position = XMFLOAT3(view.GetPositionX(), view.GetPositionY(), view.GetPositionZ());
		m_OutsideRotation = XMFLOAT3(view.GetOutsideRotationX(), view.GetOutsideRotationY(), view.GetOutsideRotationZ());
		m_InsideRotation = XMFLOAT3(view.GetInsideRotationX(), view.GetInsideRotationY(), view.GetInsideRotationZ());
		m_InitialRotation = XMFLOAT3(view.GetInitialRotationX(), view.GetInitialRotationY(), view.GetInitialRotationZ());
		m_Rotation = XMFLOAT3(view.GetRotationX(), view.GetRotationY(), view.GetRotationZ());
	}

	return *this;
}

View::~View()
{
	try
	{

	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

void View::Update(const bool positionBool, const bool eyePositionBool, const XMFLOAT3 &position, const XMFLOAT3 &rotation)
{
	if (positionBool)
	{
		if (eyePositionBool)
		{
			const float eyeOffset = 0.18f;
			const XMFLOAT3 eyePosition = XMFLOAT3(sinf(rotation.y * (3.141592653589793238462643383279502884f / 180.0f)) * eyeOffset, 0.0f, cosf(rotation.y * (3.141592653589793238462643383279502884f / 180.0f)) * eyeOffset);

			m_Position = XMFLOAT3(position.x - eyePosition.x, position.y + 0.3f, (position.z - 0.75f) - eyePosition.z);
		}
		else
		{
			m_Position = XMFLOAT3(position.x, position.y + 0.25f, position.z - 1.75f);
		}
	}
	else
	{
		float heightOffset = 0.75f;
		XMFLOAT3 objectOffset = XMFLOAT3(75.0f, -90.0f, 0.0f);

		if (m_Position.z > position.z)
		{
			heightOffset = -0.75f;
			objectOffset.z = (180.0f);
		}

		const XMFLOAT3 viewPosition = XMFLOAT3(m_Position.x - position.x, m_Position.y - (position.y - heightOffset), m_Position.z - position.z);

		const float magnitude = sqrt(pow(viewPosition.x, 2) + pow(viewPosition.y, 2) + pow(viewPosition.z, 2));
		const XMFLOAT3 unitViewPosition = XMFLOAT3(viewPosition.x / magnitude, viewPosition.y / magnitude, viewPosition.z / magnitude);

		m_Rotation = XMFLOAT3(atan2f(unitViewPosition.z, unitViewPosition.y) * (180.f / 3.141592653589793238462643383279502884f) + objectOffset.x, acosf(unitViewPosition.x) * (180.f / 3.141592653589793238462643383279502884f) + objectOffset.y, objectOffset.z);
	}
}

void View::Render()
{
	// Setup the vector that points upwards.
	XMFLOAT3 const up = XMFLOAT3(0.0f, 1.0f, 0.0f);

	// Load it into a XMVECTOR structure.
	XMVECTOR upVector = XMLoadFloat3(&up);

	// Setup the position of the camera in the world.
	XMFLOAT3 const position = XMFLOAT3(m_Position.x, m_Position.y, m_Position.z);

	// Load it into a XMVECTOR structure.
	XMVECTOR const positionVector = XMLoadFloat3(&position);

	// Setup where the camera is looking by default.
	XMFLOAT3 const lookAt = XMFLOAT3(0.0f, 0.0f, 1.0f);

	// Load it into a XMVECTOR structure.
	XMVECTOR lookAtVector = XMLoadFloat3(&lookAt);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	float const pitch = static_cast<float>(m_Rotation.x) * (3.141592653589793238462643383279502884f / 180.0f);
	float const yaw = static_cast<float>(m_Rotation.y) * (3.141592653589793238462643383279502884f / 180.0f);
	float const roll = static_cast<float>(m_Rotation.z) * (3.141592653589793238462643383279502884f / 180.0f);

	// Create the rotation matrix from the yaw, pitch, and roll values.
	XMMATRIX const rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// Finally create the view matrix from the three updated vectors.
	m_ViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
}