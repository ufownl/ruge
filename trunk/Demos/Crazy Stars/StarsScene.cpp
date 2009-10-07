#include "StdAfx.h"
#include "StarsScene.h"

CStarsScene::CStarsScene(int nID)
	: RUGE::CScene(nID)
	, m_bGameOver(TRUE)
	, m_fRes(0)
	, m_hFont(NULL)
	, m_hTex(NULL)
	, m_hMusic(NULL)
	, m_hSound(NULL)
	, m_hChannel(NULL)
	, m_pSpr(NULL)
	, m_pSpt(NULL)
	, m_psprStar(NULL)
	, m_pPar(NULL)
	, m_fx(400)
	, m_fy(300)
	, m_fdx(0)
	, m_fdy(0)
	, m_cfSpeed(200)
{
	memset(m_StarInfo, 0, sizeof(m_StarInfo));
}

CStarsScene::~CStarsScene()
{
}

void CStarsScene::Render()
{
	m_pSpr->Render(m_fx, m_fy);
	m_pPar->Render();
	for (int i=0; i<STARCNT; i++) m_psprStar->RenderEx(m_StarInfo[i].fx, m_StarInfo[i].fy, m_StarInfo[i].fRot);

	if (m_bGameOver)
	{
		RECT rect={0, 0, 800, 600};
		char szBuf[256];

		sprintf(szBuf, "ÓÎÏ·½áÊø\nÄúµÄ³É¼¨: %f", m_fRes);
		m_pApp->Font_DrawText(m_hFont, szBuf, &rect, 0, DT_CENTER|DT_VCENTER);
	}
}

BOOL CStarsScene::Update(float fDelta)
{
	if (m_pApp->Input_KeyPressed(VK_ESCAPE))
	{
		m_pSceneManager->Switch(SCENE_MENU);
		return FALSE;
	}

	if (m_bGameOver)
	{
		if (m_pApp->Input_KeyPressed(VK_RETURN))
		{
			m_pSceneManager->Switch(SCENE_MENU);
			return FALSE;
		}
	}
	else
	{
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
				m_bGameOver=TRUE;
				m_pApp->Effect_Play(m_hSound);
				m_pApp->Channel_Stop(m_hChannel);
				break;
			}
		}
	}

	return FALSE;
}

BOOL CStarsScene::Enter(WPARAM wParam, LPARAM lParam)
{
	m_pApp->Random_Seed((DWORD)time(NULL));

	m_hFont=m_pApp->Font_Create(100, 0, 0, FALSE, "Î¢ÈíÑÅºÚ");
	m_hTex=m_pApp->Texture_Load("particles.png");
	m_hMusic=m_pApp->Music_Load("Background.mid");
	m_hSound=m_pApp->Effect_Load("Lost.wav");

	m_pSpr=new RUGE::CSprite(m_hTex, 96, 64, 32, 32);
	m_pSpr->SetColor(0xFFFFF000);
	m_pSpr->SetHotSpot(16, 16);

	m_pSpt=new RUGE::CSprite(m_hTex, 96, 64, 32, 32);
	m_pSpt->SetBlendMode(BLEND_COLORMUL|BLEND_ALPHAADD|BLEND_NOZWRITE);
	m_pSpt->SetHotSpot(16, 16);

	m_pPar=new RUGE::CParticleSystem("trail.psi", m_pSpt);
    m_pPar->Fire();

	m_psprStar=new RUGE::CSprite(m_hTex, 32, 32, 32, 32);
	m_psprStar->SetColor(0xFFFFA000);
	m_psprStar->SetHotSpot(16, 16);

	switch (wParam)
	{
	case ENTER_RESUME:
		if (!m_bGameOver) break;
	case ENTER_START:
		m_bGameOver=FALSE;
		m_fRes=0;
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
		break;
	}

	m_hChannel=m_pApp->Music_Play(m_hMusic);

	return TRUE;
}

void CStarsScene::Exit()
{
	delete m_psprStar;
	delete m_pPar;
	delete m_pSpt;
	delete m_pSpr;
	m_pApp->Audio_Free(m_hSound);
	m_pApp->Audio_Free(m_hMusic);
	m_pApp->Texture_Free(m_hTex);
	m_pApp->Font_Free(m_hFont);
}
