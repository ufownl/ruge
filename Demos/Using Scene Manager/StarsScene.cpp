#include "StdAfx.h"
#include "StarsScene.h"
#include <time.h>

CStarsScene::CStarsScene(PSCENE pParentScene)
	: m_pApp(GetRUGE())
	, m_nState(0)
	, m_fRes(0)
	, m_hFont(NULL)
	, m_hFontHint(NULL)
	, m_hTex(NULL)
	, m_hTexBg(NULL)
	, m_hAudioBg(NULL)
	, m_hAudioLost(NULL)
	, m_hChannelBg(NULL)
	, m_pSpr(NULL)
	, m_pSpt(NULL)
	, m_pSprStar(NULL)
	, m_pSprBg(NULL)
	, m_pPar(NULL)
	, m_fx(400)
	, m_fy(300)
	, m_fdx(0)
	, m_fdy(0)
	, m_cfSpeed(200)
	, m_pParentScene(pParentScene)
{
}

CStarsScene::~CStarsScene()
{
	m_pApp->Release();
}

BOOL CStarsScene::EnterScene(WPARAM wParam, LPARAM lParam)
{
	m_pApp->Random_Seed((DWORD)time(NULL));

	m_hFont=m_pApp->Font_Create(20, 0, 0, FALSE, "微软雅黑");
	m_hFontHint=m_pApp->Font_Create(100, 0, 0, FALSE, "微软雅黑");
	m_hTex=m_pApp->Texture_Load("particles.png");
	m_hTexBg=m_pApp->Texture_Load("bg2.png");
	m_hAudioBg=m_pApp->Music_Load("Background.mid");
	m_hAudioLost=m_pApp->Effect_Load("Lost.wav");

	m_pSpr=new CSprite(m_hTex, 96, 64, 32, 32);
	m_pSpr->SetBlendMode(BLEND_COLORMUL|BLEND_ALPHABLEND|BLEND_ZWRITE);
	m_pSpr->SetColor(0xFFFFF000);
	m_pSpr->SetHotSpot(16, 16);

	m_pSpt=new CSprite(m_hTex, 96, 64, 32, 32);
	m_pSpt->SetBlendMode(BLEND_COLORMUL|BLEND_ALPHAADD|BLEND_ZWRITE);
	m_pSpt->SetHotSpot(16, 16);

	m_pPar=new CParticleSystem("trail.psi", m_pSpt);
    m_pPar->Fire();

	m_pSprStar=new CSprite(m_hTex, 32, 32, 32, 32);
	m_pSprStar->SetBlendMode(BLEND_COLORMUL|BLEND_ALPHABLEND|BLEND_ZWRITE);
	m_pSprStar->SetColor(0xFFFFA000);
	m_pSprStar->SetHotSpot(16, 16);

	m_pSprBg=new CSprite(m_hTexBg, 50*cosf(0), 50*sinf(0), 800, 600);
	m_pSprBg->SetBlendMode(BLEND_COLORADD|BLEND_ALPHABLEND|BLEND_ZWRITE);
	m_pSprBg->SetColor(0xFF000000, 0);
	m_pSprBg->SetColor(0xFF000000, 1);
	m_pSprBg->SetColor(0xFF000010, 2);
	m_pSprBg->SetColor(0xFF000010, 3);
	m_pSprBg->SetZ(1);

	switch (wParam)
	{
	case MODE_RESUME:
		if (m_nState==1)
		{
			m_hChannelBg=m_pApp->Music_Play(m_hAudioBg);
			break;
		}
	case MODE_START:
		for (int i=0; i<STARCNT-3; i+=4)
		{
			m_StarInfo[i].fx=m_pApp->Random_Float(0, 800);
			m_StarInfo[i].fy=m_pApp->Random_Float(-128, -16);

			m_StarInfo[i+1].fx=m_pApp->Random_Float(0, 800);
			m_StarInfo[i+1].fy=m_pApp->Random_Float(616, 728);

			m_StarInfo[i+2].fx=m_pApp->Random_Float(-128, -16);
			m_StarInfo[i+2].fy=m_pApp->Random_Float(0, 600);

			m_StarInfo[i+3].fx=m_pApp->Random_Float(816, 928);
			m_StarInfo[i+3].fy=m_pApp->Random_Float(0, 600);
		}

		m_fx=400;
		m_fy=300;

		m_fRes=0;
		m_nState=0;
		break;
	}

	return TRUE;
}

void CStarsScene::ExitScene()
{
	delete m_pSprBg;
	delete m_pSprStar;
	delete m_pPar;
	delete m_pSpt;
	delete m_pSpr;

	m_pApp->Audio_Free(m_hAudioLost);
	m_pApp->Audio_Free(m_hAudioBg);
	m_pApp->Texture_Free(m_hTexBg);
	m_pApp->Texture_Free(m_hTex);
	m_pApp->Font_Free(m_hFontHint);
	m_pApp->Font_Free(m_hFont);
}

BOOL CStarsScene::Update(CSceneManager *pSceneManager, float fDelta)
{
	if (m_pApp->Input_KeyPressed(VK_ESCAPE))
	{
		pSceneManager->SwitchScene(m_pParentScene);
		return FALSE;
	}

	switch (m_nState)
	{
	case 0:
		if (m_pApp->Input_KeyPressed(VK_RETURN))
		{
			m_hChannelBg=m_pApp->Music_Play(m_hAudioBg);
			m_nState=1;
		}
		break;
	case 1:
		m_fRes+=fDelta;

		m_fdx=0;
		m_fdy=0;

		if (m_pApp->Input_KeyPressed(VK_LEFT)) m_fdx=-m_cfSpeed*fDelta;
		if (m_pApp->Input_KeyPressed(VK_RIGHT)) m_fdx=m_cfSpeed*fDelta;
		if (m_pApp->Input_KeyPressed(VK_UP)) m_fdy=-m_cfSpeed*fDelta;
		if (m_pApp->Input_KeyPressed(VK_DOWN)) m_fdy=m_cfSpeed*fDelta;

		m_fx+=m_fdx;
		if (m_fx<16) m_fx=16;
		if (m_fx>784) m_fx=784;

		m_fy+=m_fdy;
		if (m_fy<16) m_fy=16;
		if (m_fy>584) m_fy=584;

		if (m_fdx!=0 || m_fdy!=0) m_pPar->m_Info.nEmission=50;
		else m_pPar->m_Info.nEmission=0;
		m_pPar->MoveTo(m_fx, m_fy);
		m_pPar->Update(fDelta);

		for (int i=0; i<STARCNT; i++)
		{
			if (m_StarInfo[i].fx<=-16 || m_StarInfo[i].fx>=816 || m_StarInfo[i].fy<=-16 || m_StarInfo[i].fy>=616)
			{
				float fRate=m_pApp->Random_Float(m_cfSpeed*0.5f, m_cfSpeed*1.5f)/sqrtf((m_fx-m_StarInfo[i].fx)*(m_fx-m_StarInfo[i].fx)+(m_fy-m_StarInfo[i].fy)*(m_fy-m_StarInfo[i].fy));

				m_StarInfo[i].fdx=(m_fx-m_StarInfo[i].fx)*fRate;
				m_StarInfo[i].fdy=(m_fy-m_StarInfo[i].fy)*fRate;
			}

			m_StarInfo[i].fx+=m_StarInfo[i].fdx*fDelta;
			m_StarInfo[i].fy+=m_StarInfo[i].fdy*fDelta;

			m_StarInfo[i].fRot+=fDelta*5;

			if ((m_fx-m_StarInfo[i].fx)*(m_fx-m_StarInfo[i].fx)+(m_fy-m_StarInfo[i].fy)*(m_fy-m_StarInfo[i].fy)<=16*16)
			{
				m_nState=2;
				m_pApp->Effect_Play(m_hAudioLost);
				m_pApp->Channel_Stop(m_hChannelBg);
				break;
			}

			m_pSprBg->SetTextureRect(50*cosf(m_fRes), 50*sinf(m_fRes), 800, 600);
		}
		break;
	case 2:
		if (m_pApp->Input_KeyPressed(VK_RETURN))
		{
			m_fx=400;
			m_fy=300;

			for (int i=0; i<STARCNT-3; i+=4)
			{
				m_StarInfo[i].fx=m_pApp->Random_Float(0, 800);
				m_StarInfo[i].fy=m_pApp->Random_Float(-128, -16);

				m_StarInfo[i+1].fx=m_pApp->Random_Float(0, 800);
				m_StarInfo[i+1].fy=m_pApp->Random_Float(616, 728);

				m_StarInfo[i+2].fx=m_pApp->Random_Float(-128, -16);
				m_StarInfo[i+2].fy=m_pApp->Random_Float(0, 600);

				m_StarInfo[i+3].fx=m_pApp->Random_Float(816, 928);
				m_StarInfo[i+3].fy=m_pApp->Random_Float(0, 600);
			}

			m_hChannelBg=m_pApp->Music_Play(m_hAudioBg);

			m_fRes=0;
			m_nState=1;
		}
	default:
		break;
	}

	return FALSE;
}

void CStarsScene::Render()
{
	char szBuf[256];

	m_pSprBg->Render(0, 0);
	switch (m_nState)
	{
	case 0:
		{
			RECT Rect={0, 0, 800, 600};

			m_pApp->Font_DrawText(m_hFontHint, "按回车键开始游戏", &Rect, 0, DT_CENTER|DT_VCENTER);
		}
		break;
	case 2:
		{
			RECT Rect={0, 0, 800, 600};

			sprintf(szBuf, "游戏结束\n您的成绩: %f", m_fRes);
			m_pApp->Font_DrawText(m_hFontHint, szBuf, &Rect, 0, DT_CENTER|DT_VCENTER);
		}
	case 1:
		{
			m_pSpr->Render(m_fx, m_fy);
			m_pPar->Render();
			for (int i=0; i<STARCNT; i++) m_pSprStar->Render(m_StarInfo[i].fx, m_StarInfo[i].fy, m_StarInfo[i].fRot);
		}
		break;
	default:
		break;
	}

	RECT Rect={0, 0, 200, 40};

	sprintf(szBuf, "FPS: %d\nTime: %f", m_pApp->Timer_GetFPS(), m_fRes);
	m_pApp->Font_DrawText(m_hFont, szBuf, &Rect);
}
