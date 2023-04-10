#include "StdAfx.h"
#include "Vector3D.h"


Vector3D::Vector3D()
{
	x_ = 0.0f; 
	y_ = 0.0f; 
	z_ = 0.0f; 
}


Vector3D::Vector3D(float val)
{
	x_ = val; 
	y_ = val; 
	z_ = val; 
}

Vector3D::Vector3D(float x, float y, float z)
{
	x_ = x; 
	y_ = y; 
	z_ = z; 
}


Vector3D::~Vector3D()
{
}



//void Vector3D::PackInfo(Proud::CMessage& msg)
//{
//	msg << x_ << y_ << z_; 
//}
//void Vector3D::UnpackInfo(Proud::CMessage& msg)
//{
//	msg >> x_ >> y_ >> z_; 
//}


///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : 
// @Description : Access grants
// @Argument : ->
// @author : 
// @date : 
// 
const float& Vector3D::operator [](int i) const
{
	return (&x_)[i]; 
}


float& Vector3D::operator [](int i)
{
	return (&x_)[i]; 
}


///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : 
// @Description : Assignment operators
// @Argument : ->
// @author : 
// @date : 
// 
Vector3D& Vector3D::operator =(const Vector3D& v)
{
	x_ = v.x_;    y_ = v.y_;    z_ = v.z_; 
	return *this; 
}

Vector3D& Vector3D::operator +=(const Vector3D& v)
{
	x_ += v.x_;    y_ += v.y_;    z_ += v.z_; 
	return *this; 
}


Vector3D& Vector3D::operator -=(const Vector3D& v)
{
	x_ -= v.x_;    y_ -= v.y_;    z_ -= v.z_; 
	return *this; 
}


Vector3D& Vector3D::operator *=(const Vector3D& v)
{
	x_ *= v.x_;    y_ *= v.y_;    z_ *= v.z_; 
	return *this; 
}


Vector3D& Vector3D::operator /=(const Vector3D& v)
{
	x_ /= v.x_;    y_ /= v.y_;    z_ /= v.z_; 
	return *this; 
}


Vector3D& Vector3D::operator *=(float val)
{
	x_ *= val;    y_ *= val;    z_ *= val; 
	return *this; 
}


Vector3D& Vector3D::operator /=(float val)
{
	x_ /= val;    y_ /= val;    z_ /= val; 
	return *this; 
}


Vector3D& Vector3D::operator =(float val)
{
	x_ = val;    y_ = val;    z_ = val; 
	return *this; 	
}


inline Vector3D operator + (const Vector3D& v1)
{
	return v1; 
}

inline Vector3D operator - (const Vector3D& v1)
{
	return Vector3D(-v1.x_, -v1.y_, -v1.z_); 
}

// Addition and subtraction
Vector3D operator + (const Vector3D& v1, const Vector3D& v2)
{
	return Vector3D(v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_); 
}


Vector3D operator - (const Vector3D& v1, const Vector3D& v2)
{
	return Vector3D(v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_); 
}


// Scalar multiplication and division
Vector3D operator * (const Vector3D& v, float val)
{
	return Vector3D(v.x_ * val, v.y_ * val, v.z_ * val); 
}


Vector3D operator / (const Vector3D& v, float val)
{
	return Vector3D(v.x_ / val, v.y_ / val, v.z_ / val); 
}


// Memberwise multiplication and division
Vector3D operator * (const Vector3D& v1, const Vector3D& v2)
{
	return Vector3D(v1.x_ * v2.x_, v1.y_ * v2.y_, v1.z_ * v2.z_); 
}


Vector3D operator / (const Vector3D& v1, const Vector3D& v2)
{
	return Vector3D(v1.x_ / v2.x_, v1.y_ / v2.y_, v1.z_ / v2.z_); 
}


// Vector dominance
int operator < (const Vector3D& v1, const Vector3D& v2)
{
	return v1.x_ < v2.x_ && v1.y_ < v2.y_ && v1.z_ < v2.z_; 

}


int operator <= (const Vector3D& v1, const Vector3D& v2)
{
	return v1.x_ <= v2.x_ && v1.y_ <= v2.y_ && v1.z_ <= v2.z_; 
}


// Bitwise equality
int operator == (const Vector3D& v1, const Vector3D& v2)
{
	return v1.x_ == v2.x_ && v1.y_ == v2.y_ && v1.z_ == v2.z_; 
}


///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : SquareLength2D
// @Description : 벡터의 크기
// @Argument : ->
// @author : 
// @date : 
// 
// 
float SquareLength2D (const Vector3D& v)
{
	return v.x_ * v.x_ + v.y_ * v.y_; 
}


///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : Length2D
// @Description : 벡터의 길이
// @Argument : ->
// @author : 
// @date : 
// 
float Length2D (const Vector3D& v)
{
	return (float)sqrt(SquareLength2D(v)); 
}


///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : SquareLength3D
// @Description : 벡터의 크기
// @Argument : ->
// @author : 
// @date : 
// 
// 
float SquareLength3D(const Vector3D& v)
{
	return v.x_ * v.x_ + v.y_ * v.y_ + v.z_ * v.z_; 
}


///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : Length3D
// @Description : 벡터의 길이
// @Argument : ->
// @author : 
// @date : 
// 
float Length3D (const Vector3D& v)
{
	return (float)sqrt(SquareLength3D(v)); 
}


///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : Normalize2D
// @Description : 벡터의 단위벡터
// @Argument : ->
// @author : 
// @date : 
// 
Vector3D Normalize2D (Vector3D v)
{
	v.z_ = 0.0f; 
	float fLength = Length2D(v); 
	if(0.0f == fLength)
	{
		fLength = 1.0f; 
	}
	return v / fLength; 
}


///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : Normalize3D
// @Description : 벡터의 단위벡터
// @Argument : ->
// @author : 
// @date : 
// 
Vector3D Normalize3D(const Vector3D& v)
{
	float fLength = Length3D(v); 
	if(0.0f == fLength)
	{
		fLength = 1.0f; 
	}
	return v / fLength; 
}


///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : Truncate
// @Description : 벡터의 최대 크기
// @Argument : ->
// @author : 
// @date : 
// 
Vector3D Truncate(const Vector3D& v, float maxlength)
{
	//sqrt() 함수 사용을 줄이기 위해
	if(SquareLength3D(v) <= (maxlength*maxlength))
		return v; 

	return Normalize3D(v) * maxlength; 
}

///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : DotProduct
// @Description : 두백터간의 내적 계산
// @Argument : ->
// @author : 
// @date : 
// 
float DotProduct(const Vector3D& v1, const Vector3D& v2)
{
	return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_; 
}


///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : CrossProduct
// @Description : 두백터간의 외적 계산
// @Argument : ->
// @author : 
// @date : 
// 
Vector3D CrossProduct(const Vector3D& v1, const Vector3D& v2)
{
	Vector3D v; 
	v.x_ = v1.y_ * v2.z_ - v1.z_ * v2.y_; 
	v.y_ = v1.z_ * v2.x_ - v1.x_ * v2.z_; 
	v.z_ = v1.x_ * v2.y_ - v1.y_ * v2.x_; 
	return v; 
}


///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : GetAngleFromUnit
// @Description : 단위벡터로부터 회전각을 구하는 함수
// @Argument : ->
// @author : 
// @date : 
// 
float GetAngleFromUnit(const Vector3D& v)
{
	float temp	= 0.0f; 
	float theta	= 0.0f; 
	//if(v.z_ <= 1 && v.z_ >= -1)
	if(v.y_ <= 1 && v.y_ >= -1)
	{
		temp = (float)acos((double)v.y_); 
	}

	if(v.x_>=0)
	{
		theta= ((temp*180.0f)/_PI_); 
	}
	else if(v.x_<0)
	{
		theta = -((temp*180.0f)/_PI_); 
	}

	if(theta<0.0f)
	{
		theta+=360.0f; 
	}

	return theta; 
}


///////////////////////////////////////////////////////////////////////////////
// @Class : 
// @Name : GetUnitFromAngle
// @Description : 각도(degree)로부터 단위벡터를 구하는 함수
// @Argument : ->
// @author : 
// @date : 
// 
Vector3D GetUnitFromAngle(float fDegree)
{
	Vector3D Unit; 
	Unit.x_ = (float)sin(fDegree * _PI_/180.0f); 
	//Unit.z_ = (float)cos(fDegree * _PI_/180.0f); 
	Unit.y_ = (float)cos(fDegree * _PI_/180.0f); 
	return Unit; 
}


// 점이 두 평면 사이에 존재하는 지 체크하는 함수
bool CheckInnerPlane(const Vector3D& TargetPos, const Vector3D& Pos, const Vector3D& Dir, float fDist)
{
	Vector3D UpVec(0,1,0); 
	Vector3D vRight = CrossProduct(Dir, UpVec); 

	Vector3D vLeft = -vRight; 

	Vector3D Vec1 = Pos + (fDist * vRight); 
	Vector3D Vec2 = Pos + (fDist * vLeft); 

	Vector3D ResVec1 = (TargetPos - Vec1); 
	Vector3D ResVec2 = (TargetPos - Vec2); 

	if(DotProduct(vRight, ResVec1) > 0)
	{
		return false; 
	}

	if(DotProduct(vLeft, ResVec2) > 0)
	{
		return false; 
	}

	return true; 
}

