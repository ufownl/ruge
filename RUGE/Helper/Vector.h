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

#pragma once

#ifndef _VECTOR_H_
#define _VECTOR_H_

class CVector
{
public:
	CVector(float fx=0, float fy=0);

	CVector& operator = (const CVector &v);

	CVector operator - () const;
	CVector operator - (const CVector &v) const;
	CVector operator + (const CVector &v) const;
	CVector& operator -= (const CVector &v);
	CVector& operator += (const CVector &v);

	CVector operator / (float fScale) const;
	CVector operator * (float fScale) const;
	CVector& operator /= (float fScale);
	CVector& operator *= (float fScale);

	float operator ^ (const CVector &v) const;
	float operator % (const CVector &v) const;

	bool operator == (const CVector &v) const;
	bool operator != (const CVector &v) const;

	float Dot(const CVector *v) const;
	float Length() const;
	float Angle(const CVector *v=NULL) const;
	void Clamp(float fMax);
	CVector& Normalize();
	CVector& Rotate(float a);

public:
	float x, y;
};

CVector operator * (float fScale, const CVector &v);

#endif  // _VECTOR_H_