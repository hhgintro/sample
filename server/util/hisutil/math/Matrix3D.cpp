#include "StdAfx.h"
#include "Matrix3D.h"


Matrix3D::Matrix3D()
: n11_(0.f), n12_(0.f), n13_(0.f)
, n21_(0.f), n22_(0.f), n23_(0.f)
, n31_(0.f), n32_(0.f), n33_(0.f)
{
}

Matrix3D::~Matrix3D()
{
}


Matrix3D& Matrix3D::operator =(const Matrix3D& m)
{
	n11_ = m.n11_; n12_ = m.n12_; n13_ = m.n13_;
	n21_ = m.n21_; n22_ = m.n22_; n23_ = m.n23_;
	n31_ = m.n31_; n32_ = m.n32_; n33_ = m.n33_;
	return *this;
}





Matrix3D operator * (const Matrix3D& m1, const Matrix3D& m2)
{
	Matrix3D mat;
	
	mat.n11_ = m1.n11_*m2.n11_ + m1.n12_*m2.n21_ + m1.n13_*m2.n31_;
	mat.n12_ = m1.n11_*m2.n12_ + m1.n12_*m2.n22_ + m1.n13_*m2.n32_;
	mat.n13_ = m1.n11_*m2.n13_ + m1.n12_*m2.n23_ + m1.n13_*m2.n33_;

	mat.n21_ = m1.n21_*m2.n11_ + m1.n22_*m2.n21_ + m1.n23_*m2.n31_;
	mat.n22_ = m1.n21_*m2.n12_ + m1.n22_*m2.n22_ + m1.n23_*m2.n32_;
	mat.n23_ = m1.n21_*m2.n13_ + m1.n22_*m2.n23_ + m1.n23_*m2.n33_;

	mat.n31_ = m1.n31_*m2.n11_ + m1.n32_*m2.n21_ + m1.n33_*m2.n31_;
	mat.n32_ = m1.n31_*m2.n12_ + m1.n32_*m2.n22_ + m1.n33_*m2.n32_;
	mat.n33_ = m1.n31_*m2.n13_ + m1.n32_*m2.n23_ + m1.n33_*m2.n33_;

	return mat;
}

Vector3D operator * (const Vector3D& v, const Matrix3D& m)
{
	return Vector3D(v.x_*m.n11_ + v.y_*m.n21_ + v.z_*m.n31_
					, v.x_*m.n12_ + v.y_*m.n22_ + v.z_*m.n32_
					, v.x_*m.n13_ + v.y_*m.n23_ + v.z_*m.n33_);
}
