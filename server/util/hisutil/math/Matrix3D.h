#pragma once

#include <math.h>

class Vector3D;

class Matrix3D
{
public:
	float n11_, n12_, n13_;
	float n21_, n22_, n23_;
	float n31_, n32_, n33_;

public:
	Matrix3D();
	~Matrix3D();



	//// Assignment operators
	Matrix3D& operator =(const Matrix3D& m);
	//Matrix3D& operator +=(const Matrix3D& v);
	//Matrix3D& operator -=(const Matrix3D& v);
	//Matrix3D& operator *=(const Matrix3D& v);
	//Matrix3D& operator /=(const Matrix3D& v);
	//Vector3D& operator *=(Vector3D& v);
	//Matrix3D& operator *=(float val);
	//Matrix3D& operator /=(float val);
	//Matrix3D& operator =(float val);

	//friend Matrix3D operator + (const Matrix3D& v);
	//friend Matrix3D operator - (const Matrix3D& v);

	//// Addition and subtraction
	//friend Vector3D operator + (const Vector3D& v1, const Vector3D& v2);
	//friend Vector3D operator - (const Vector3D& v1, const Vector3D& v2);
	//// Memberwise multiplication and division
	friend Matrix3D operator * (const Matrix3D& m1, const Matrix3D& m2);
	friend Vector3D operator * (const Vector3D& v, const Matrix3D& m);


	Matrix3D& Zero()
	{
		n11_ = 0.f; n12_ = 0.f; n13_ = 0.f;
		n21_ = 0.f; n22_ = 0.f; n23_ = 0.f;
		n31_ = 0.f; n32_ = 0.f; n33_ = 0.f;
		return *this;
	}
	Matrix3D& Identify()
	{
		n11_ = 1.f; n12_ = 0.f; n13_ = 0.f;
		n21_ = 0.f; n22_ = 1.f; n23_ = 0.f;
		n31_ = 0.f; n32_ = 0.f; n33_ = 1.f;
		return *this;
	}

	Vector3D Scale(Vector3D& v, float xscale, float yscale, float zscale)
	{
		n11_ = xscale;	n12_ = 0.f;		n13_ = 0.f;
		n21_ = 0.f;		n22_ = yscale;	n23_ = 0.f;
		n31_ = 0.f;		n32_ = 0.f;		n33_ = zscale;
		return v * (*this);
	}
	//radius : 30 * PI / 180( 각이 30도 인경우)
	Vector3D RotationX(Vector3D& v, float radius)
	{
		n11_ = 1.f; n12_ = 0.f;			n13_ = 0.f;
		n21_ = 0.f; n22_ = cos(radius); n23_ = -sin(radius);
		n31_ = 0.f; n32_ = sin(radius); n33_ = cos(radius);
		return v * (*this);
	}

	//radius : 30 * PI / 180( 각이 30도 인경우)
	Vector3D RotationY(Vector3D& v, float radius)
	{
		n11_ = cos(radius); n12_ = 0.f; n13_ = -sin(radius);
		n21_ = 0.f;			n22_ = 1.f; n23_ = 0.f;
		n31_ = sin(radius); n32_ = 0;	n33_ = cos(radius);
		return v * (*this);
	}

	//radius : 30 * PI / 180( 각이 30도 인경우)
	Vector3D RotationZ(Vector3D& v, float radius)
	{
		n11_ = cos(radius); n12_ = -sin(radius);	n13_ = 0.f;
		n21_ = sin(radius); n22_ = cos(radius);		n23_ = 0.f;
		n31_ = 0.f;			n32_ = 0;				n33_ = 1;
		return v * (*this);
	}

	Vector3D Translate(Vector3D& v, float x, float y)
	{
		n11_ = 1.f;	n12_ = 0.f;	n13_ = 0.f;
		n21_ = 0.f;	n22_ = 1.f;	n23_ = 0.f;
		n31_ = x;	n32_ = y;	n33_ = 1.f;
		return v * (*this);
	}
};
