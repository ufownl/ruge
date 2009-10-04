#pragma once

#include "StarsScene.h"

class CMenuScene : public IScene
{
public:
	CMenuScene();
	virtual ~CMenuScene();

	virtual BOOL EnterScene(WPARAM wParam, LPARAM lParam);
	virtual void ExitScene();
	virtual BOOL Update(CSceneManager *pSceneManager, float fDelta);
	virtual void Render();

protected:
	PAPPLICATION m_pApp;
	CStarsScene *m_pscStars;

	int m_nLastID;

	HTEXTURE m_hTex;
	HAUDIO m_hSound;
	HFONTX m_hFont;

	CGUI *m_pGUI;
	CSprite *m_pSpr;
};
