#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Rect.h"

class CSprite
{
public:
	CSprite(HTEXTURE hTex, float x, float y, float w, float h);
	CSprite(const CSprite &Spr);
	virtual ~CSprite();

	CSprite& operator = (const CSprite &Spr);

	void Flip(BOOL bx, BOOL by, BOOL bHotSpot=FALSE);
	void Render(float x, float y, float fRot=0.0f, float fHScale=1.0f, float fVScale=0.0f);

	void SetTexture(HTEXTURE hTex);
	void SetTextureRect(float x, float y, float w, float h);
	void SetColor(DWORD dwColor, int nIndex=-1);
	void SetZ(float z, int nIndex=-1);
	void SetBlendMode(DWORD dwBlend);
	void SetHotSpot(float x, float y);

	HTEXTURE GetTexture() const;
	void GetTextureRect(float &x, float &y, float &w, float &h) const;
	DWORD GetColor(int nIndex=0) const;
	float GetZ(int nIndex=0) const;
	DWORD GetBlendMode() const;
	void GetHotSpot(float &x, float &y) const;
	float GetWidth() const;
	float GetHeight() const;
	void GetBoundingBox(float x, float y, CRect &rect) const;
	void GetBoundingBox(float x, float y, float fRot, float fHScale, float fVScale, CRect &rect) const;

protected:
	PAPPLICATION m_pApp;
	QUAD m_quadTex;
	float m_fLeft, m_fTop, m_fWidth, m_fHeight, m_fHotx, m_fHoty;
};

#endif  // _SPRITE_H_
