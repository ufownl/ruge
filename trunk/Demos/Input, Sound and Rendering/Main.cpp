#include <RUGE.h>
#ifdef _DEBUG
#pragma comment(lib, "RUGE_Debug.lib")
#else
#pragma comment(lib, "RUGE.lib")
#endif  // _DEBUG

RUGE::PAPPLICATION g_pApp;  // ����RUGE Application�ӿ�ָ��

RUGE::HFONT g_hFont;
RUGE::HAUDIO g_hAudio;
RUGE::QUAD g_Quad;

float g_fx=100.0f, g_fy=100.0f, g_fdx, g_fdy;
const float g_cfAcceleration=90.0f, g_cfFriction=0.98f;

void Boom()
{
	int nPan=(int)(g_fx-400)/4;
	float fPitch=(g_fdx*g_fdx+g_fdy*g_fdy)*0.0005f+0.2f;
	
	g_pApp->Effect_Play(g_hAudio, 100, nPan, fPitch);
}

class CEventHandler : public RUGE::IApplicationEventHandler  // ʵ��RUGE Application�¼�����ӿ�
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
	
	g_Quad.hTex=g_pApp->Texture_Load("particles.png");
	g_Quad.dwBlend=BLEND_DEFAULT;
	for (int i=0; i<4; i++)
	{
		g_Quad.v[i].z=0.5f;
		g_Quad.v[i].dwColor=0xFFFFA000;
	}

	g_Quad.v[0].tu=96.0/128.0;
	g_Quad.v[0].tv=64.0/128.0;
	
	g_Quad.v[1].tu=128.0/128.0;
	g_Quad.v[1].tv=64.0/128.0;
	
	g_Quad.v[2].tu=128.0/128.0;
	g_Quad.v[2].tv=96.0/128.0;
	
	g_Quad.v[3].tu=96.0/128.0;
	g_Quad.v[3].tv=96.0/128.0;

	return S_OK;  // ����S_OK��ʾ��Դ��ʼ���ɹ�
}

void CEventHandler::ReleaseResource()
{
	// �ڴ������Դ�ͷŴ���
	// �����ڲ�����ϵͳ�����Զ��ͷ��������弰������Դ
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

	g_Quad.v[0].x=g_fx-16;
	g_Quad.v[0].y=g_fy-16;

	g_Quad.v[1].x=g_fx+16;
	g_Quad.v[1].y=g_fy-16;

	g_Quad.v[2].x=g_fx+16;
	g_Quad.v[2].y=g_fy+16;

	g_Quad.v[3].x=g_fx-16;
	g_Quad.v[3].y=g_fy+16;

	return FALSE;  // ����FALSE��ʾ��Ϸδ����
}

void CEventHandler::Render()
{
	// �ڴ������Ⱦ����
	g_pApp->Gfx_Clear();
	g_pApp->Gfx_RenderQuad(&g_Quad);

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
	g_pApp=RUGE::GetRUGE();  // ��ȡRUGE Application����
	if (g_pApp==NULL)
	{
		puts("Error: RUGE Application�����ȡʧ��");
		system("Pause");
		return -1;
	}
	g_pApp->System_SetState(RUGE::APP_EVENTHANDLER, &CEventHandler());  // �����¼��������
	g_pApp->System_SetState(RUGE::APP_CAPTION, "Input, Sound and Rendering");  // ���ô��ڱ���
	g_pApp->System_SetState(RUGE::APP_VSYNC, VSYNC_ONE);  // ������ֱͬ��
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