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
#include "Color.h"

CColor::CColor(float a/* =0 */, float r/* =0 */, float g/* =0 */, float b/* =0 */)
	: a(a)
	, r(r)
	, g(g)
	, b(b)
{
}

CColor::CColor(const CColor &color)
	: a(color.a)
	, r(color.r)
	, g(color.g)
	, b(color.b)
{
}

CColor::CColor(DWORD dwColor)
{
	SetColor(dwColor);
}

CColor& CColor::operator = (const CColor &color)
{
	a=color.a;
	a=color.r;
	a=color.g;
	a=color.b;
	return *this;
}

CColor& CColor::operator = (DWORD dwColor)
{
	SetColor(dwColor);
	return *this;
}

CColor CColor::operator - (const CColor &color) const
{
	return CColor(a-color.a, r-color.r, g-color.g, b-color.b);
}

CColor CColor::operator + (const CColor &color) const
{
	return CColor(a+color.a, r+color.r, g+color.g, b+color.b);
}

CColor CColor::operator * (const CColor &color) const
{
	return CColor(a*color.a, r*color.r, g*color.g, b*color.b);
}

CColor& CColor::operator -= (const CColor &color)
{
	a-=color.a;
	r-=color.r;
	g-=color.g;
	b-=color.b;
	return *this;
}

CColor& CColor::operator += (const CColor &color)
{
	a+=color.a;
	r+=color.r;
	g+=color.g;
	b+=color.b;
	return *this;
}

CColor& CColor::operator *= (const CColor &color)
{
	a*=color.a;
	r*=color.r;
	g*=color.g;
	b*=color.b;
	return *this;
}

CColor CColor::operator / (float fScale) const
{
	return CColor(a/fScale, r/fScale, g/fScale, b/fScale);
}

CColor CColor::operator * (float fScale) const
{
	return CColor(a*fScale, r*fScale, g*fScale, b*fScale);
}

CColor& CColor::operator /= (float fScale)
{
	a/=fScale;
	r/=fScale;
	g/=fScale;
	b/=fScale;
	return *this;
}

CColor& CColor::operator *= (float fScale)
{
	a*=fScale;
	r*=fScale;
	g*=fScale;
	b*=fScale;
	return *this;
}

bool CColor::operator == (const CColor &color) const
{
	return a==color.a && r==color.r && g==color.g && b==color.b;
}

bool CColor::operator != (const CColor &color) const
{
	return a!=color.a || r!=color.r || g!=color.g || b!=color.b;
}

void CColor::SetColor(DWORD dwColor)
{
	a=(dwColor>>24)/255.0f;
	r=((dwColor>>16)&0xFF)/255.0f;
	g=((dwColor>>8)&0xFF)/255.0f;
	b=(dwColor&0xFF)/255.0f;
}

DWORD CColor::GetColor() const
{
	return (DWORD(a*255.0f)<<24)+(DWORD(r*255.0f)<<16)+(DWORD(g*255.0f)<<8)+DWORD(b*255.0f);
}

void CColor::Clamp()
{
	if(a<0.0f) a=0.0f;
	if(a>1.0f) a=1.0f;

	if(r<0.0f) r=0.0f;
	if(r>1.0f) r=1.0f;

	if(g<0.0f) g=0.0f;
	if(g>1.0f) g=1.0f;

	if(b<0.0f) b=0.0f;
	if(b>1.0f) b=1.0f;
}

CColor operator * (float fScale, const CColor &color)
{
	return color*fScale;
}