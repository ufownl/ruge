#pragma once

#include "StarsScene.h"

class CMenuScene : public RUGE::CScene
{
public:
	CMenuScene(int nID);
	virtual ~CMenuScene();

protected:
	virtual void Render();
	virtual BOOL Update(float fDelta);

	virtual BOOL Enter(WPARAM wParam, LPARAM lParam);
	virtual void Exit();

protected:
	int m_nLastID;

	RUGE::HTEXTURE m_hTex;
	RUGE::HAUDIO m_hSound;
	RUGE::HFONT m_hFont;

	RUGE::CGUI *m_pGUI;
	RUGE::CSprite *m_pSpr;
};
