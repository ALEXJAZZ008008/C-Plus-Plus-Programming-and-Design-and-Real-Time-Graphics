#pragma once

class Vector3d
{
public:
	Vector3d(double x = 0, double y = 0, double z = 0);
	~Vector3d(void);

	double GetX() const;
	void SetX(double x);

	double GetY() const;
	void SetY(double y);

	double GetZ() const;
	void SetZ(double z);

private:
	double m_x, m_y, m_z;
};
