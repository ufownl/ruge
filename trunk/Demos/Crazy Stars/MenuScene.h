#pragma once

#include "StarsScene.h"

class CMenuScene : public CScene
{
public:
	CMenuScene();
	virtual ~CMenuScene();

	virtual void Render();
	virtual BOOL Update(float fDelta);

	virtual BOOL Enter(WPARAM wParam, LPARAM lParam);
	virtual void Exit();

protected:
	int m_nLastID;

	HTEXTURE m_hTex;
	HAUDIO m_hSound;
	HFONTX m_hFont;

	CGUI *m_pGUI;
	CSprite *m_pSpr;
};
