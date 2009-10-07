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
#include "Rect.h"

namespace RUGE
{

	CRect::CRect()
	{
		Clear();
	}

	CRect::CRect(const CRect &rect)
		: x1(rect.x1)
		, y1(rect.y1)
		, x2(rect.x2)
		, y2(rect.y2)
		, m_bClean(rect.m_bClean)
	{
	}

	CRect::CRect(float fLeft, float fTop, float fRight, float fBottom)
	{
		Set(fLeft, fTop, fRight, fBottom);
	}

	CRect& CRect::operator=(const CRect &rect)
	{
		if (this!=&rect)
		{
			x1=rect.x1;
			y1=rect.y1;
			x2=rect.x2;
			y2=rect.y2;
			m_bClean=rect.m_bClean;
		}
		return *this;
	}

	void CRect::Clear()
	{
		x1=0.0f;
		y1=0.0f;
		x2=0.0f;
		y2=0.0f;
		m_bClean=TRUE;
	}

	BOOL CRect::IsClean()
	{
		return m_bClean;
	}

	void CRect::Set(float fLeft, float fTop, float fRight, float fBottom)
	{
		x1=fLeft;
		y1=fTop;
		x2=fRight;
		y2=fBottom;
		m_bClean=FALSE;
	}

	void CRect::SetRadius(float x, float y, float r)
	{
		x1=x-r;
		y1=y-r;
		x2=x+r;
		y2=y+r;
		m_bClean=FALSE;
	}

	void CRect::Encapsulate(float x, float y)
	{
		if(m_bClean)
		{
			x1=x2=x;
			y1=y2=y;
			m_bClean=FALSE;
		}
		else
		{
			if(x<x1) x1=x;
			if(x>x2) x2=x;
			if(y<y1) y1=y;
			if(y>y2) y2=y;
		}
	}

	BOOL CRect::TestPoint(float x, float y) const
	{
		return x1<=x && x<=x2 && y1<=y && y<=y2;
	}

	BOOL CRect::Intersect(const CRect *pRect) const
	{
		return fabs(x1+x2-pRect->x1-pRect->x2)<(x2-x1+pRect->x2-pRect->x1) && fabs(y1+y2-pRect->y1-pRect->y2)<(y2-y1+pRect->y2-pRect->y1);
	}

}