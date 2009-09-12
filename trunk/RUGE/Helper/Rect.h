#pragma once

#ifndef _RECT_H_
#define _RECT_H_

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
	BOOL CRect::Intersect(const CRect &rect) const;

public:
	float x1, y1, x2, y2;

protected:
	BOOL m_bClean;
};

#endif  // _RECT_H_