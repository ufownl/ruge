#pragma once

#ifndef _COLOR_H_
#define _COLOR_H_

class CColor
{
public:
	CColor(float a=0, float r=0, float g=0, float b=0);
	CColor(const CColor &color);
	CColor(DWORD dwColor);

	CColor& operator = (const CColor &color);
	CColor& operator = (DWORD dwColor);

	CColor operator - (const CColor &color) const;
	CColor operator + (const CColor &color) const;
	CColor operator * (const CColor &color) const;
	CColor& operator -= (const CColor &color);
	CColor& operator += (const CColor &color);
	CColor& operator *= (const CColor &color);

	CColor operator / (float fScale) const;
	CColor operator * (float fScale) const;
	CColor& operator /= (float fScale);
	CColor& operator *= (float fScale);

	bool operator == (const CColor &color) const;
	bool operator != (const CColor &color) const;

	void SetColor(DWORD dwColor);
	DWORD GetColor() const;
	void Clamp();

public:
	float r, g, b, a;
};

CColor operator * (float fScale, const CColor &color);

#endif  // _COLOR_H_
