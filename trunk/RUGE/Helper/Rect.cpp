#include "StdAfx.h"
#include "Rect.h"

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
	if(x1<=x && x<=x2 && y1<=y && y<=y2) return TRUE;
	return FALSE;
}

BOOL CRect::Intersect(const CRect &rect) const
{
	if(fabs(x1+x2-rect.x1-rect.x2)<(x2-x1+rect.x2-rect.x1)
		&& fabs(y1+y2-rect.y1-rect.y2)<(y2-y1+rect.y2-rect.y1)) return TRUE;
	return FALSE;
}
