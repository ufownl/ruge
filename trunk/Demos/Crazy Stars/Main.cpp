#include <RUGE.h>
#ifdef _DEBUG
#pragma comment(lib, "RUGE_Debug.lib")
#else
#pragma comment(lib, "RUGE.lib")
#endif

#include <Sprite.h>
#include <ParticleSystem.h>
#ifdef _DEBUG
#pragma comment(lib, "Helper_Debug.lib")
#else
#pragma comment(lib, "Helper.lib")
#endif  // _DEBUG

#include <time.h>
#include <math.h>

PAPPLICATION g_pApp;  // ����RUGE Application�ӿ�ָ��

int g_nState;
float g_fRes;

HFONTX g_hFont, g_hFontHint;
HTEXTURE g_hTex, g_hTexBg;
HAUDIO g_hAudioBg, g_hAudioLost;
HCHANNEL g_hChannelBg;

CSprite *g_pSpr, *g_pSpt, *g_pSprStar, *g_pSprBg;
CParticleSystem *g_pPar;

float g_fx=400.0f, g_fy=300.0f, g_fdx, g_fdy;
const float g_cfSpeed=200.0f;

#define STARCNT	40

struct STARINFO
{
	float fx, fy, fdx, fdy, fRot;
} g_StarInfo[STARCNT];

class CEventHandler : public IApplicationEventHandler  // ʵ��RUGE Application�¼������ӿ�
{
public:
	virtual HRESULT InitResource();
	virtual void ReleaseResource();
	virtual BOOL Frame(float fDelta);
	virtual void Render();
	virtual void Pretreat(int nPitch, void *pBits);
	virtual void WndEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

HRESULT CEventHandler::InitResource()
{
	// �ڴ�������Դ��ʼ������
	g_pApp->Random_Seed((DWORD)time(NULL));

	g_hFont=g_pApp->Font_Create(20, 0, 0, FALSE, "΢���ź�");
	g_hFontHint=g_pApp->Font_Create(100, 0, 0, FALSE, "΢���ź�");
	g_hTex=g_pApp->Texture_Load("particles.png");
	g_hTexBg=g_pApp->Texture_Load("bg.png");
	g_hAudioBg=g_pApp->Music_Load("Background.mid");
	g_hAudioLost=g_pApp->Effect_Load("Lost.wav");

	g_pSpr=new CSprite(g_hTex, 96, 64, 32, 32);
	g_pSpr->SetColor(0xFFFFF000);
	g_pSpr->SetHotSpot(16, 16);

	g_pSpt=new CSprite(g_hTex, 96, 64, 32, 32);
	g_pSpt->SetBlendMode(BLEND_COLORMUL|BLEND_ALPHAADD|BLEND_NOZWRITE);
	g_pSpt->SetHotSpot(16, 16);

	g_pPar=new CParticleSystem("trail.psi", g_pSpt);
    g_pPar->Fire();

	g_pSprStar=new CSprite(g_hTex, 32, 32, 32, 32);
	g_pSprStar->SetColor(0xFFFFA000);
	g_pSprStar->SetHotSpot(16, 16);

	g_pSprBg=new CSprite(g_hTexBg, 50*cosf(0), 50*sinf(0), 800, 600);
	g_pSprBg->SetBlendMode(BLEND_COLORADD|BLEND_ALPHABLEND|BLEND_NOZWRITE);
	g_pSprBg->SetColor(0xFF000000, 0);
	g_pSprBg->SetColor(0xFF000000, 1);
	g_pSprBg->SetColor(0xFF000010, 2);
	g_pSprBg->SetColor(0xFF000010, 3);

	for (int i=0; i<STARCNT-3; i+=4)
	{
		g_StarInfo[i].fx=g_pApp->Random_Float(0, 800);
		g_StarInfo[i].fy=g_pApp->Random_Float(-128, -16);

		g_StarInfo[i+1].fx=g_pApp->Random_Float(0, 800);
		g_StarInfo[i+1].fy=g_pApp->Random_Float(616, 728);

		g_StarInfo[i+2].fx=g_pApp->Random_Float(-128, -16);
		g_StarInfo[i+2].fy=g_pApp->Random_Float(0, 600);

		g_StarInfo[i+3].fx=g_pApp->Random_Float(816, 928);
		g_StarInfo[i+3].fy=g_pApp->Random_Float(0, 600);
	}

	return S_OK;  // ����S_OK��ʾ��Դ��ʼ���ɹ�
}

void CEventHandler::ReleaseResource()
{
	// �ڴ�������Դ�ͷŴ���
	// �����ڲ�����ϵͳ�����Զ��ͷ����������弰������Դ
	delete g_pSprBg;
	delete g_pSprStar;
	delete g_pPar;
	delete g_pSpt;
	delete g_pSpr;
}

// float fDelta: ��һ֡�͵�ǰ֡��ʱ����������Ϊ��λ
BOOL CEventHandler::Frame(float fDelta)
{
	// �ڴ�������Ϸ�߼����ƴ���
	if (g_pApp->Input_KeyPressed(VK_ESCAPE)) return TRUE;

	switch (g_nState)
	{
	case 0:
		if (g_pApp->Input_KeyPressed(VK_RETURN))
		{
			g_hChannelBg=g_pApp->Music_Play(g_hAudioBg);
			g_nState=1;
		}
		break;
	case 1:
		g_fRes+=fDelta;

		g_fdx=0;
		g_fdy=0;

		if (g_pApp->Input_KeyPressed(VK_LEFT)) g_fdx=-g_cfSpeed*fDelta;
		if (g_pApp->Input_KeyPressed(VK_RIGHT)) g_fdx=g_cfSpeed*fDelta;
		if (g_pApp->Input_KeyPressed(VK_UP)) g_fdy=-g_cfSpeed*fDelta;
		if (g_pApp->Input_KeyPressed(VK_DOWN)) g_fdy=g_cfSpeed*fDelta;

		g_fx+=g_fdx;
		if (g_fx<16) g_fx=16;
		if (g_fx>784) g_fx=784;

		g_fy+=g_fdy;
		if (g_fy<16) g_fy=16;
		if (g_fy>584) g_fy=584;

		if (g_fdx!=0 || g_fdy!=0) g_pPar->m_Info.nEmission=50;
		else g_pPar->m_Info.nEmission=0;
		g_pPar->MoveTo(g_fx, g_fy);
		g_pPar->Update(fDelta);

		for (int i=0; i<STARCNT; i++)
		{
			if (g_StarInfo[i].fx<=-16 || g_StarInfo[i].fx>=816 || g_StarInfo[i].fy<=-16 || g_StarInfo[i].fy>=616)
			{
				float fRate=g_pApp->Random_Float(g_cfSpeed*0.5f, g_cfSpeed*1.5f)/sqrtf((g_fx-g_StarInfo[i].fx)*(g_fx-g_StarInfo[i].fx)+(g_fy-g_StarInfo[i].fy)*(g_fy-g_StarInfo[i].fy));

				g_StarInfo[i].fdx=(g_fx-g_StarInfo[i].fx)*fRate;
				g_StarInfo[i].fdy=(g_fy-g_StarInfo[i].fy)*fRate;
			}

			g_StarInfo[i].fx+=g_StarInfo[i].fdx*fDelta;
			g_StarInfo[i].fy+=g_StarInfo[i].fdy*fDelta;

			g_StarInfo[i].fRot+=fDelta*5;

			if ((g_fx-g_StarInfo[i].fx)*(g_fx-g_StarInfo[i].fx)+(g_fy-g_StarInfo[i].fy)*(g_fy-g_StarInfo[i].fy)<=16*16)
			{
				g_nState=2;
				g_pApp->Effect_Play(g_hAudioLost);
				g_pApp->Channel_Stop(g_hChannelBg);
				break;
			}

			g_pSprBg->SetTextureRect(50*cosf(g_fRes), 50*sinf(g_fRes), 800, 600);
		}
		break;
	case 2:
		if (g_pApp->Input_KeyPressed(VK_RETURN))
		{
			g_fx=400;
			g_fy=300;

			for (int i=0; i<STARCNT-3; i+=4)
			{
				g_StarInfo[i].fx=g_pApp->Random_Float(0, 800);
				g_StarInfo[i].fy=g_pApp->Random_Float(-128, -16);

				g_StarInfo[i+1].fx=g_pApp->Random_Float(0, 800);
				g_StarInfo[i+1].fy=g_pApp->Random_Float(616, 728);

				g_StarInfo[i+2].fx=g_pApp->Random_Float(-128, -16);
				g_StarInfo[i+2].fy=g_pApp->Random_Float(0, 600);

				g_StarInfo[i+3].fx=g_pApp->Random_Float(816, 928);
				g_StarInfo[i+3].fy=g_pApp->Random_Float(0, 600);
			}

			g_hChannelBg=g_pApp->Music_Play(g_hAudioBg);

			g_fRes=0;
			g_nState=1;
		}
	}

	return FALSE;  // ����FALSE��ʾ��Ϸδ����
}

void CEventHandler::Render()
{
	// �ڴ�������Ⱦ����
	char szBuf[256];

	g_pApp->Gfx_Clear();
	g_pSprBg->Render(0, 0);
	switch (g_nState)
	{
	case 0:
		{
			RECT Rect={0, 0, 800, 600};

			g_pApp->Font_DrawText(g_hFontHint, "���س�����ʼ��Ϸ", &Rect, 0, DT_CENTER|DT_VCENTER);
		}
		break;
	case 2:
		{
			RECT Rect={0, 0, 800, 600};

			sprintf(szBuf, "��Ϸ����\n���ĳɼ�: %f", g_fRes);
			g_pApp->Font_DrawText(g_hFontHint, szBuf, &Rect, 0, DT_CENTER|DT_VCENTER);
		}
	case 1:
		{
			g_pSpr->Render(g_fx, g_fy);
			g_pPar->Render();
			for (int i=0; i<STARCNT; i++) g_pSprStar->Render(g_StarInfo[i].fx, g_StarInfo[i].fy, g_StarInfo[i].fRot);
		}
		break;
	default:
		break;
	}

	RECT Rect={0, 0, 200, 40};

	sprintf(szBuf, "FPS: %d\nTime: %f", g_pApp->Timer_GetFPS(), g_fRes);
	g_pApp->Font_DrawText(g_hFont, szBuf, &Rect);
}

// int nPitch: ͼ����һ�����ص��ڻ���������ռ�ռ���ֽ���
// void *pBits: ������Ⱦ����Ļ��ͼ�����ݻ�����ָ�룬һ�����ص�ռ4���ֽڣ���
//              ���£�0xAARRGGBB
void CEventHandler::Pretreat(int nPitch, void *pBits)
{
	// �ڴ�����ͼ��Ԥ��������
}

// UINT uMsg: WINDOWS��Ϣ����
// WPARAM wParam: WINDOWS��ϢWPARAM����
// LPARAM lParam: WINDOWS��ϢLPARAM����
void CEventHandler::WndEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �ڴ����Ӵ�����Ϣ��������
}

int main(int argc, char *argv[])
{
	HRESULT hr=0;  // ���򷵻�ֵ

	CoInitialize(NULL);  // ��ʼ��COM��
	g_pApp=GetRUGE();  // ��ȡRUGE Application����
	if (g_pApp==NULL)
	{
		puts("Error: RUGE Application�����ȡʧ��");
		system("Pause");
		return -1;
	}
	g_pApp->System_SetState(RUGE_EVENTHANDLER, &CEventHandler());  // �����¼���������
	g_pApp->System_SetState(RUGE_CAPTION, "Crazy Stars");  // ���ô��ڱ���
	g_pApp->System_SetState(RUGE_VSYNC, VSYNC_ONE);  // ������ֱͬ��
	hr=g_pApp->System_Initialize();  // ��ʼ��RUGE Application����
	if (SUCCEEDED(hr)) hr=g_pApp->System_Run();  // ������ѭ��
	else
	{
		printf("Error: RUGE Application�����ʼ��ʧ��\nError Code: %d\n", hr);
		system("Pause");
	}
	g_pApp->Release();  // �ͷ�RUGE Application����
	CoUninitialize();  // �ͷ�COM��
	return hr;
}