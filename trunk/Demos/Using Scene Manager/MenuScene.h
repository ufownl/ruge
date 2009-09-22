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

	HFONTX m_hFont;
	HTEXTURE m_hTex;

	CSprite *m_pSpr;

	float m_fTime;

	CStarsScene *m_pStarsScene;
};
