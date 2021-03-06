#include "StdAfx.h"
#include "MenuScene.h"
#include "MenuItem.h"

CMenuScene::CMenuScene(int nID)
	: RUGE::CScene(nID)
	, m_nLastID(0)
	, m_hTex(NULL)
	, m_hSound(NULL)
	, m_hFont(NULL)
	, m_pGUI(NULL)
	, m_pSpr(NULL)
{
}

CMenuScene::~CMenuScene()
{
}

void CMenuScene::Render()
{
	m_pGUI->Render();
}

BOOL CMenuScene::Update(float fDelta)
{
	if (m_pApp->Input_GetKey()==VK_ESCAPE)
	{
		m_nLastID=3;
		m_pGUI->Exit();
	}

	int nID=m_pGUI->Update(fDelta);

	if (nID==-1)
	{
		switch (m_nLastID)
		{
		case 1:
			m_pSceneManager->Switch(SCENE_STARS, ENTER_START);
			return FALSE;
		case 2:
			m_pSceneManager->Switch(SCENE_STARS, ENTER_RESUME);
			return FALSE;
		case 3:
			return TRUE;
		}
	}
	else if (nID>0)
	{
		m_nLastID=nID;
		m_pGUI->Exit();
	}

	return FALSE;
}

BOOL CMenuScene::Enter(WPARAM wParam, LPARAM lParam)
{
	m_hTex=m_pApp->Texture_Load("cursor.png");
	m_hSound=m_pApp->Effect_Load("menu.wav");
	m_hFont=m_pApp->Font_Create(40, 0, 0, FALSE, "΢���ź�");

	m_pSpr=new RUGE::CSprite(m_hTex, 0, 0, 32, 32);

	m_pGUI=new RUGE::CGUI;
	m_pGUI->AddCtrl(new CMenuItem(1, m_hFont, m_hSound, 400, 240, 0.1f, "Start"));
	m_pGUI->AddCtrl(new CMenuItem(2, m_hFont, m_hSound, 400, 280, 0.2f, "Resume"));
	m_pGUI->AddCtrl(new CMenuItem(3, m_hFont, m_hSound, 400, 320, 0.3f, "Exit"));
	m_pGUI->SetNavMode(NAV_UPDOWN|NAV_CYCLED);
	m_pGUI->SetCursor(m_pSpr);
	m_pGUI->SetFocus(1);
	m_pGUI->Enter();

	m_nLastID=0;

	return TRUE;
}

void CMenuScene::Exit()
{
	delete m_pGUI;
	delete m_pSpr;
	m_pApp->Font_Free(m_hFont);
	m_pApp->Audio_Free(m_hSound);
	m_pApp->Texture_Free(m_hTex);
}
