#include <RUGE.h>
#ifdef _DEBUG
#pragma comment(lib, "RUGE_Debug.lib")
#else
#pragma comment(lib, "RUGE.lib")
#endif  // _DEBUG

#include <Sprite.h>
#ifdef _DEBUG
#pragma comment(lib, "Helper_Debug.lib")
#else
#pragma comment(lib, "Helper.lib")
#endif  // _DEBUG

#include <math.h>

PAPPLICATION g_pApp;  // ����RUGE Application�ӿ�ָ��
IRandomPtr g_pRand;

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

#define MIN_OBJS	100
#define MAX_OBJS	2000

typedef struct SPROBJ
{
	float fx, fy, fdx, fdy, fScale, fRot, fdScale, fdRot;
	DWORD dwColor;
} *PSPROBJ;

PSPROBJ g_pObjs;
int g_nObjs, g_nBlend;

HFONTX g_hFont;
HTEXTURE g_hTex, g_hTexBg;
CSprite *g_pSpr, *g_pSprBg;

DWORD g_dwFntColor[5]={0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF};

void SetBlend(int nBlend)
{
	static DWORD dwBlend[5]=
	{
		BLEND_COLORMUL|BLEND_ALPHABLEND|BLEND_ZWRITE,
		BLEND_COLORADD|BLEND_ALPHABLEND|BLEND_ZWRITE,
		BLEND_COLORMUL|BLEND_ALPHABLEND|BLEND_ZWRITE,
		BLEND_COLORMUL|BLEND_ALPHAADD|BLEND_ZWRITE,
		BLEND_COLORMUL|BLEND_ALPHABLEND|BLEND_ZWRITE
	};
	
	static DWORD dwColor[5][5]=
	{
		{0xFFFFFFFF, 0xFFFFE080, 0xFF80A0FF, 0xFFA0FF80, 0xFFFF80A0},
		{0xFF000000, 0xFF303000, 0xFF000060, 0xFF006000, 0xFF600000},
		{0x80FFFFFF, 0x80FFE080, 0x8080A0FF, 0x80A0FF80, 0x80FF80A0},
		{0x80FFFFFF, 0x80FFE080, 0x8080A0FF, 0x80A0FF80, 0x80FF80A0},
		{0x40202020, 0x40302010, 0x40102030, 0x40203010, 0x40102030}
	};

	nBlend%=5;
	g_nBlend=nBlend;
	g_pSpr->SetBlendMode(dwBlend[nBlend]);
	for (int i=0; i<MAX_OBJS; i++) g_pObjs[i].dwColor=dwColor[nBlend][g_pRand->Integer(0, 4)];
}

class CEventHandler : public IApplicationEventHandler  // ʵ��RUGE Application�¼�����ӿ�
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
	// �ڴ������Դ��ʼ������
	g_pRand.CreateInstance(__uuidof(CRandomImpl));

	g_hFont=g_pApp->Font_Create(20, 0, 0, FALSE, "Fixedsys");
	g_hTex=g_pApp->Texture_Load("zazaka.png");
	g_hTexBg=g_pApp->Texture_Load("bg2.png");

	g_pSpr=new CSprite(g_hTex, 0, 0, 64, 64);
	g_pSpr->SetHotSpot(32, 32);

	g_pSprBg=new CSprite(g_hTexBg, 0, 0, 800, 600);
	g_pSprBg->SetBlendMode(BLEND_COLORADD|BLEND_ALPHABLEND|BLEND_NOZWRITE);
	g_pSprBg->SetColor(0xFF000000, 0);
	g_pSprBg->SetColor(0xFF000000, 1);
	g_pSprBg->SetColor(0xFF000040, 2);
	g_pSprBg->SetColor(0xFF000040, 3);

	g_pObjs=new SPROBJ[MAX_OBJS];
	g_nObjs=1000;

	for (int i=0; i<MAX_OBJS; i++)
	{
		static const float fPi=acosf(-1);

		g_pObjs[i].fx=g_pRand->Float(0, SCREEN_WIDTH);
		g_pObjs[i].fy=g_pRand->Float(0, SCREEN_HEIGHT);
		g_pObjs[i].fdx=g_pRand->Float(-200, 200);
		g_pObjs[i].fdy=g_pRand->Float(-200, 200);
		g_pObjs[i].fScale=g_pRand->Float(0.5f, 2.0f);
		g_pObjs[i].fdScale=g_pRand->Float(-1.0f, 1.0f);
		g_pObjs[i].fRot=g_pRand->Float(0, fPi*2);
		g_pObjs[i].fdRot=g_pRand->Float(-1.0f, 1.0f);
	}

	SetBlend(0);

	return S_OK;  // ����S_OK��ʾ��Դ��ʼ���ɹ�
}

void CEventHandler::ReleaseResource()
{
	// �ڴ������Դ�ͷŴ���
	// �����ڲ�����ϵͳ�����Զ��ͷ��������弰������Դ
	delete[] g_pObjs;
	delete g_pSprBg;
	delete g_pSpr;
	g_pRand.Release();
	
}

// float fDelta: ��һ֡�͵�ǰ֡��ʱ����������Ϊ��λ
BOOL CEventHandler::Frame(float fDelta)
{
	// �ڴ������Ϸ�߼����ƴ���
	switch (g_pApp->Input_GetKey())
	{
	case VK_ESCAPE:
		return TRUE;
	case VK_UP:
		if (g_nObjs<MAX_OBJS) g_nObjs+=100;
		break;
	case VK_DOWN:
		if (g_nObjs>MIN_OBJS) g_nObjs-=100;
		break;
	case VK_SPACE:
		SetBlend(++g_nBlend);
		break;
	}

	for (int i=0; i<g_nObjs; i++)
	{
		g_pObjs[i].fx+=g_pObjs[i].fdx*fDelta;
		if (g_pObjs[i].fx<0 || g_pObjs[i].fx>SCREEN_WIDTH) g_pObjs[i].fdx=-g_pObjs[i].fdx;
		g_pObjs[i].fy+=g_pObjs[i].fdy*fDelta;
		if (g_pObjs[i].fy<0 || g_pObjs[i].fy>SCREEN_HEIGHT) g_pObjs[i].fdy=-g_pObjs[i].fdy;
		g_pObjs[i].fScale+=g_pObjs[i].fdScale*fDelta;
		if(g_pObjs[i].fScale<0.5 || g_pObjs[i].fScale>2) g_pObjs[i].fdScale=-g_pObjs[i].fdScale;
		g_pObjs[i].fRot+=g_pObjs[i].fdRot*fDelta;
	}

	return FALSE;  // ����FALSE��ʾ��Ϸδ����
}

void CEventHandler::Render()
{
	// �ڴ������Ⱦ����
	static RECT Rect={0, 0, 800, 600};
	char szBuf[256];

	sprintf(szBuf, "UP and DOWN to adjust number of hares: %d\nSPACE to change blending mode: %d\nFPS: %d",
		g_nObjs, g_nBlend, g_pApp->Timer_GetFPS());

	g_pApp->Gfx_Clear();
	g_pSprBg->Render(0, 0);
	for(int i=0; i<g_nObjs; i++)
	{
		g_pSpr->SetColor(g_pObjs[i].dwColor); 
		g_pSpr->Render(g_pObjs[i].fx, g_pObjs[i].fy, g_pObjs[i].fRot, g_pObjs[i].fScale);
	}
	g_pApp->Font_DrawText(g_hFont, szBuf, &Rect, 0, DT_TOP|DT_LEFT, g_dwFntColor[g_nBlend]);
}

// int nPitch: ͼ����һ�����ص��ڻ���������ռ�ռ���ֽ���
// void *pBits: ������Ⱦ����Ļ��ͼ�����ݻ�����ָ�룬һ�����ص�ռ4���ֽڣ���
//              ���£�0xAARRGGBB
void CEventHandler::Pretreat(int nPitch, void *pBits)
{
	// �ڴ����ͼ��Ԥ�������
}

// UINT uMsg: WINDOWS��Ϣ����
// WPARAM wParam: WINDOWS��ϢWPARAM����
// LPARAM lParam: WINDOWS��ϢLPARAM����
void CEventHandler::WndEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �ڴ���Ӵ�����Ϣ�������
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
	g_pApp->System_SetState(RUGE_EVENTHANDLER, &CEventHandler());  // �����¼��������
	g_pApp->System_SetState(RUGE_CAPTION, "Thousand of Hares");  // ���ô��ڱ���
	g_pApp->System_SetState(RUGE_VSYNC, VSYNC_IMMEDIATE);  // �رմ�ֱͬ��
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