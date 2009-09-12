#include "StdAfx.h"
#include "Vector.h"

CVector::CVector(float fx/* =0 */, float fy/* =0 */)
	: x(fx)
	, y(fy)
{
}

CVector& CVector::operator = (const CVector &v)
{
	x=v.x;
	y=v.y;
	return *this;
}

CVector CVector::operator - () const
{
	return CVector(-x, -y);
}

CVector CVector::operator - (const CVector &v) const
{
	return CVector(x-v.x, y-v.y);
}

CVector CVector::operator + (const CVector &v) const
{
	return CVector(x+v.x, y+v.y);
}

CVector& CVector::operator -= (const CVector &v)
{
	x-=v.x;
	y-=v.y;
	return *this;
}

CVector& CVector::operator += (const CVector &v)
{
	x+=v.x;
	y+=v.y;
	return *this;
}

CVector CVector::operator / (float fScale) const
{
	return CVector(x/fScale, y/fScale);
}

CVector CVector::operator * (float fScale) const
{
	return CVector(x*fScale, y*fScale);
}

CVector& CVector::operator /= (float fScale)
{
	x/=fScale;
	y/=fScale;
	return *this;
}

CVector& CVector::operator *= (float fScale)
{
	x*=fScale;
	y*=fScale;
	return *this;
}

float CVector::operator ^ (const CVector &v) const
{
	return Angle(&v);
}

float CVector::operator % (const CVector &v) const
{
	return Dot(&v);
}

bool CVector::operator == (const CVector &v) const
{
	return x==v.x && y==v.y;
}

bool CVector::operator != (const CVector &v) const
{
	return x!=v.x || y!=v.y;
}

float CVector::Dot(const CVector *v) const
{
	return x*v->x+y*v->y;
}

float CVector::Length() const
{
	return sqrtf(Dot(this));
}

float CVector::Angle(const CVector *v/* =NULL */) const
{
	if(v==NULL) return atan2f(y, x);

	CVector s=*this, t=*v;

	s.Normalize();
	t.Normalize();
	return acosf(s.Dot(&t));
}

void CVector::Clamp(float fMax)
{
	if (Length()>fMax)
	{
		Normalize();
		x*=fMax;
		y*=fMax;
	}
}

CVector& CVector::Normalize()
{
	float rc=1.0f/sqrtf(Dot(this));

	x*=rc;
	y*=rc;
	return *this;
}

CVector& CVector::Rotate(float a)
{
	x=x*cosf(a) - y*sinf(a);
	y=x*sinf(a) + y*cosf(a);
	return *this;
}

CVector operator * (float fScale, const CVector &v)
{
	return v*fScale;
}