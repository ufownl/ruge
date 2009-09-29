#include "StdAfx.h"
#include "MenuScene.h"

CMenuScene::CMenuScene()
	: m_pApp(GetRUGE())
	, m_hFont(NULL)
	, m_hTex(NULL)
	, m_pSpr(NULL)
	, m_fTime(0)
{
	m_pStarsScene=new CStarsScene(this);
}

CMenuScene::~CMenuScene()
{
	delete m_pStarsScene;
	m_pApp->Release();
}

BOOL CMenuScene::EnterScene(WPARAM wParam, LPARAM lParam)
{
	m_hFont=m_pApp->Font_Create(50, 0, 0, FALSE, "微软雅黑");
	m_hTex=m_pApp->Texture_Load("bg.png");

	m_pSpr=new CSprite(m_hTex, 0, 0, 800, 600);
	m_pSpr->SetBlendMode(BLEND_COLORMUL|BLEND_ALPHABLEND|BLEND_ZWRITE);

	m_fTime=0;

	return TRUE;
}

void CMenuScene::ExitScene()
{
	delete m_pSpr;

	m_pApp->Texture_Free(m_hTex);
	m_pApp->Font_Free(m_hFont);
}

BOOL CMenuScene::Update(CSceneManager *pSceneManager, float fDelta)
{
	switch (m_pApp->Input_GetKey())
	{
	case '1':
		pSceneManager->SwitchScene(m_pStarsScene, MODE_START);
		return FALSE;
	case '2':
		pSceneManager->SwitchScene(m_pStarsScene, MODE_RESUME);
		return FALSE;
	case '3':
		return TRUE;
	}

	m_fTime+=fDelta;
	m_pSpr->SetTextureRect(50*cosf(m_fTime), 50*sinf(m_fTime), 800, 600);

	return FALSE;
}

void CMenuScene::Render()
{
	m_pSpr->Render(0, 0);

	RECT Rect={0, 0, 800, 600};

	m_pApp->Font_DrawText(m_hFont, "按对应的数字键选择:\n1.Start\n2.Resume\n3.Exit",
		&Rect, 0, DT_CENTER|DT_VCENTER);
}
