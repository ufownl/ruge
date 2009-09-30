#include <RUGE.h>
#ifdef _DEBUG
#pragma comment(lib, "RUGE_Debug.lib")
#else
#pragma comment(lib, "RUGE.lib")
#endif  // _DEBUG

#include <Sprite.h>
#include <ParticleSystem.h>
#ifdef _DEBUG
#pragma comment(lib, "Helper_Debug.lib")
#else
#pragma comment(lib, "Helper.lib")
#endif  // _DEBUG

PAPPLICATION g_pApp;  // ����RUGE Application�ӿ�ָ��

HFONTX g_hFont;
HAUDIO g_hAudio;
HTEXTURE g_hTex;

CSprite *g_pSpr, *g_pSpt;
CParticleSystem *g_pPar;

float g_fx=100.0f, g_fy=100.0f, g_fdx, g_fdy;
const float g_cfAcceleration=90.0f, g_cfFriction=0.98f;

void Boom()
{
	int nPan=(int)(g_fx-400)/4;
	float fPitch=(g_fdx*g_fdx+g_fdy*g_fdy)*0.0005f+0.2f;

	g_pApp->Effect_Play(g_hAudio, 100, nPan, fPitch);
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
	g_hFont=g_pApp->Font_Create(20, 0, 0, FALSE, "΢���ź�");
	g_hAudio=g_pApp->Effect_Load("menu.wav");
	g_hTex=g_pApp->Texture_Load("particles.png");
	
	g_pSpr=new CSprite(g_hTex, 96, 64, 32, 32);
	g_pSpr->SetColor(0xFFFFA000);
	g_pSpr->SetHotSpot(16, 16);

	g_pSpt=new CSprite(g_hTex, 96, 64, 32, 32);
	g_pSpt->SetBlendMode(BLEND_COLORMUL|BLEND_ALPHAADD|BLEND_NOZWRITE);
	g_pSpt->SetHotSpot(16, 16);

	g_pPar=new CParticleSystem("trail.psi", g_pSpt);
    g_pPar->Fire();

	return S_OK;  // ����S_OK��ʾ��Դ��ʼ���ɹ�
}

void CEventHandler::ReleaseResource()
{
	// �ڴ������Դ�ͷŴ���
	// �����ڲ�����ϵͳ�����Զ��ͷ��������弰������Դ
	delete g_pPar;
	delete g_pSpt;
	delete g_pSpr;
}

// float fDelta: ��һ֡�͵�ǰ֡��ʱ����������Ϊ��λ
BOOL CEventHandler::Frame(float fDelta)
{
	// �ڴ������Ϸ�߼����ƴ���
	if (g_pApp->Input_KeyPressed(VK_ESCAPE)) return TRUE;
	if (g_pApp->Input_KeyPressed(VK_LEFT)) g_fdx-=g_cfAcceleration*fDelta;
	if (g_pApp->Input_KeyPressed(VK_RIGHT)) g_fdx+=g_cfAcceleration*fDelta;
	if (g_pApp->Input_KeyPressed(VK_UP)) g_fdy-=g_cfAcceleration*fDelta;
	if (g_pApp->Input_KeyPressed(VK_DOWN)) g_fdy+=g_cfAcceleration*fDelta;

	g_fdx*=g_cfFriction;
	g_fdy*=g_cfFriction;
	g_fx+=g_fdx;
	g_fy+=g_fdy;

	if(g_fx>784)
	{
		g_fx=784-(g_fx-784);
		g_fdx=-g_fdx;
		Boom();
	}
	if(g_fx<16)
	{
		g_fx=16+16-g_fx;
		g_fdx=-g_fdx;
		Boom();
	}
	if(g_fy>584)
	{
		g_fy=584-(g_fy-584);
		g_fdy=-g_fdy;
		Boom();
	}
	if(g_fy<16)
	{
		g_fy=16+16-g_fy;
		g_fdy=-g_fdy;
		Boom();
	}

	g_pPar->m_Info.nEmission=(int)(g_fdx*g_fdx+g_fdy*g_fdy)*2;
	g_pPar->MoveTo(g_fx, g_fy);
	g_pPar->Update(fDelta);

	return FALSE;  // ����FALSE��ʾ��Ϸδ����
}

void CEventHandler::Render()
{
	// �ڴ������Ⱦ����
	g_pApp->Gfx_Clear();
	g_pSpr->Render(g_fx, g_fy);
	g_pPar->Render();

	static RECT Rect={0, 0, 100, 20};
	char szBuf[256];

	sprintf(szBuf, "FPS: %d", g_pApp->Timer_GetFPS());
	g_pApp->Font_DrawText(g_hFont, szBuf, &Rect);
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
	g_pApp->System_SetState(RUGE_CAPTION, "Using Helper Classes");  // ���ô��ڱ���
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