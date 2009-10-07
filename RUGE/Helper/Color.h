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

#ifndef _RUGE_COLOR_H_
#define _RUGE_COLOR_H_

namespace RUGE
{

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

		BOOL operator == (const CColor &color) const;
		BOOL operator != (const CColor &color) const;

		void SetColor(DWORD dwColor);
		DWORD GetColor() const;
		void Clamp();

	public:
		float r, g, b, a;
	};

	CColor operator * (float fScale, const CColor &color);

}

#endif  // _RUGE_COLOR_H_
