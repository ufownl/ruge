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

#ifndef _RUGE_RECT_H_
#define _RUGE_RECT_H_

namespace RUGE
{

	class CRect
	{
	public:
		CRect();
		CRect(const CRect &rect);
		CRect(float fLeft, float fTop, float fRight, float fBottom);

		CRect& operator=(const CRect &rect);

		void Clear();
		BOOL IsClean();
		void Set(float fLeft, float fTop, float fRight, float fBottom);
		void SetRadius(float x, float y, float r);
		void Encapsulate(float x, float y);
		BOOL TestPoint(float x, float y) const;
		BOOL Intersect(const CRect *pRect) const;

	public:
		float x1, y1, x2, y2;

	protected:
		BOOL m_bClean;
	};

}

#endif  // _RUGE_RECT_H_