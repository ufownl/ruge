/*
RUGE Copyright (C) 2009 ”Œœ¿UFO

This file is part of RUGE.

RUGE is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RUGE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RUGE.  If not, see <http://www.gnu.org/licenses/>.
*/

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