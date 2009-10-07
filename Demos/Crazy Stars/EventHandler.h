#pragma once

#include "MenuScene.h"

class CEventHandler : public RUGE::IApplicationEventHandler  // 实现RUGE Application事件处理接口
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
	RUGE::PAPPLICATION m_pApp;
	RUGE::CSceneManager *m_pSceneManager;

	RUGE::HFONT m_hFont;
	RUGE::HTEXTURE m_hTex;

	RUGE::CSprite *m_pSpr;
};
