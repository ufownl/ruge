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