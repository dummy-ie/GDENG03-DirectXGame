#pragma once
#include <cmath>
#include <ostream>

class Vector3D
{
public:
	Vector3D() : x(0), y(0), z(0) {}
	Vector3D(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	Vector3D(const Vector3D& vector) : x(vector.x), y(vector.y), z(vector.z) {}
	~Vector3D() = default;

	float magnitude() const
	{
		return sqrt((x * x + y * y + z * z));
	}

	Vector3D normalize() const
	{
		const float mag = this->magnitude();
		return *this / mag;
		// return this->scaleVector3D((1 / this->magnitude()));
	}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, const float delta)
	{
		Vector3D v;
		v.x = start.x * (1.0f - delta) + end.x * (delta);
		v.y = start.y * (1.0f - delta) + end.y * (delta);
		v.z = start.z * (1.0f - delta) + end.z * (delta);
		return v;
	}

	Vector3D operator+(const Vector3D& addend) const
	{
		return { this->x + addend.x, this->y + addend.y, this->z + addend.z };
	}

	Vector3D operator-(const Vector3D& subtrahend) const
	{
		return { this->x - subtrahend.x, this->y - subtrahend.y, this->z - subtrahend.z };
	}

	Vector3D operator*(const Vector3D& v) const
		// cross product w/ vector3d
	{
		return { (this->y * v.z) - (this->z * v.y), (this->z * v.x) - (this->x * v.z), (this->x * v.y) - (this->y * v.x) };
	}

	// Vector3D operator*(const Matrix& m) // cross product w/ matrix
	// {
	// 	float mult[4] = { this->x, this->y, this->z, 1 };
	// 	float result[4] = { 0, 0, 0, 1 };
	//
	// 	if (m.getSize().at(1) != 4)
	// 		return Vector3D();
	//
	// 	for (size_t i = 0; i < (size_t)m.getSize().at(0); i++)
	// 	{
	// 		for (size_t j = 0; j < 4; j++)
	// 		{
	// 			result[i] += (m.getData(i, j) * mult[j]);
	// 			// std::cout << result[i] << " += " << m.getData(i, j) << " * " << mult[j];
	// 			// std::cout << ", ";
	// 		}
	// 		// std::cout << "\n";
	// 	}
	//
	// 	return Vector3D(result[0], result[1], result[2]);
	// }

	Vector3D operator*(const float scalar) const
		// scalar multiplication
	{
		return { this->x * scalar, this->y * scalar, this->z * scalar };
	}

	Vector3D operator/(const float denominator) const
	// scalar division
	{
		return { this->x / denominator, this->y / denominator, this->z / denominator };
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector3D& vec)
	{
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return os;
	}
public:
	float x, y, z;
};

