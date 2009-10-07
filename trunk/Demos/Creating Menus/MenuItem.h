#pragma once

class CMenuItem : public RUGE::CControl
{
public:
	CMenuItem(int nID, RUGE::HFONT hFont, RUGE::HAUDIO hSound, float x, float y, float fDelay, LPSTR lpcszTitle);
	virtual ~CMenuItem();

protected:
	virtual void Render();
	virtual void Update(float fDelta);

	virtual void Enter();
	virtual void Exit();
	virtual BOOL IsDone();
	virtual void Focus(BOOL bFocused);
	virtual void MouseOver(BOOL bOver);

	virtual BOOL MouseLBtn(BOOL bDown, float x, float y);
	virtual BOOL KeyClick(int nVKey, char chChar);

protected:
	RUGE::HFONT m_hFont;
	RUGE::HAUDIO m_hSound;
	float m_fDelay;
	LPCSTR m_lpcszTitle;

	RUGE::CColor m_colSrc, m_colDelta, m_colSrc2, m_colDelta2, m_colShadowSrc, m_colShadowDelta;
	RUGE::CColor m_colColor, m_colShadow;
	float m_fOffsetSrc, m_fOffsetDelta, m_fOffset;
	float m_fTime, m_fTime2;
};
