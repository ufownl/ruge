#pragma once

#include "MenuScene.h"

class CEventHandler : public IApplicationEventHandler  // 实现RUGE Application事件处理接口
{
public:
	CEventHandler();
	virtual ~CEventHandler();

	virtual HRESULT InitResource();
	virtual void ReleaseResource();
	virtual BOOL Frame(float fDelta);
	virtual void Render();
	virtual void Pretreat(int nPitch, void *pBits);
	virtual void WndEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	PAPPLICATION m_pApp;
	CMenuScene *m_pscMenu;
	CSceneManager *m_pSceneManager;

	HFONTX m_hFont;
	HTEXTURE m_hTex;

	CSprite *m_pSpr;
};
