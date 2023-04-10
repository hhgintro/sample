#pragma once

#include <math.h>

#define _PI_ 3.14159265358979323846f


class Vector3D
{
public:
	float x_;
	float y_;
	float z_;

public:
	Vector3D();
	Vector3D(float val);
	Vector3D(float x, float y, float z);
	~Vector3D();


	// Access grants
	const float & operator[](int i ) const;
	float &operator[](int i);

	// Assignment operators
	Vector3D& operator =(const Vector3D& v);
	Vector3D& operator +=(const Vector3D& v);
	Vector3D& operator -=(const Vector3D& v);
	Vector3D& operator *=(const Vector3D& v);
	Vector3D& operator /=(const Vector3D& v);
	Vector3D& operator *=(float val);
	Vector3D& operator /=(float val);
	Vector3D& operator =(float val);

	friend Vector3D operator + (const Vector3D& v);
	friend Vector3D operator - (const Vector3D& v);

	// Addition and subtraction
	friend Vector3D operator + (const Vector3D& v1, const Vector3D& v2);
	friend Vector3D operator - (const Vector3D& v1, const Vector3D& v2);
	// Memberwise multiplication and division
	friend Vector3D operator * (const Vector3D& v1, const Vector3D& v2);
	friend Vector3D operator / (const Vector3D& v1, const Vector3D& v2);
	// Scalar multiplication and division
	friend Vector3D operator * (const Vector3D& v, float val);
	friend Vector3D operator / (const Vector3D& v, float val);

	// Vector dominance
	friend int operator < (const Vector3D& v1, const Vector3D& v2);
	friend int operator <= (const Vector3D& v1, const Vector3D& v2);

	// Bitwise equality
	friend int operator == (const Vector3D& v1, const Vector3D& v2);

	// Length-related functions
	friend float SquareLength2D(const Vector3D& v);
	friend float Length2D(const Vector3D& v);
	friend float SquareLength3D(const Vector3D& v);
	friend float Length3D(const Vector3D& v);

	// Returns vector with same direction and unit length
	friend Vector3D Normalize2D(Vector3D v);
	friend Vector3D Normalize3D(const Vector3D& v);

	friend Vector3D Truncate(const Vector3D& v, float maxlength);

	// Dot and cross product
	friend float DotProduct(const Vector3D& v1, const Vector3D& v2);
	friend Vector3D CrossProduct(const Vector3D& v1, const Vector3D& v2);

	//friend float GetAngleFromUnit(const Vector3D& v);
	//friend Vector3D GetUnitFromAngle(float fDegree);

	// 점이 두 평면 사이에 존재하는 지 체크하는 함수
	friend bool CheckInnerPlane(const Vector3D& TargetPos, const Vector3D& Pos, const Vector3D& Dir, float fDist) ;
};
