#pragma once

struct Vector3
{
	float X, Y, Z;

	inline Vector3(void) {}
	inline Vector3(const float x, const float y, const float z)
	{
		X = x; Y = y; Z = z;
	}
	inline Vector3(Vector3& v) {
		X = v.X; Y = v.Y; Z = v.Z;
	}

	inline Vector3 operator + (const Vector3& A) const
	{
		return Vector3(X + A.X, Y + A.Y, Z + A.Z);
	}

	inline Vector3 operator + (const float A) const
	{
		return Vector3(X + A, Y + A, Z + A);
	}

	inline float Dot(const Vector3& A) const
	{
		return A.X*X + A.Y*Y + A.Z*Z;
	}

	static Vector3 zero()
	{
		return Vector3(0, 0, 0);
	}

	static Vector3 one()
	{
		return Vector3(1, 1, 1);
	}

	static Vector3 x()
	{
		return Vector3(1, 0, 0);
	}

	static Vector3 y()
	{
		return Vector3(0, 1, 0);
	}

	static Vector3 z()
	{
		return Vector3(0, 0, 1);
	}
};