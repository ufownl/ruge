#include "StdAfx.h"
#include "MenuItem.h"

PAPPLICATION g_pApp;  // ����RUGE Application�ӿ�ָ��

QUAD g_Quad;
HTEXTURE g_hTex;
HAUDIO g_hSound;
HFONTX g_hFont;

CGUI *g_pGUI;
CSprite *g_pSpr;

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
	g_Quad.hTex=g_pApp->Texture_Load("bg.png");
	g_Quad.dwBlend=BLEND_DEFAULT;
	for (int i=0; i<4; i++)
	{
		g_Quad.v[i].z=0.5f;
		g_Quad.v[i].dwColor=0xFFFFFFFF;
	}
	g_Quad.v[0].x=0;
	g_Quad.v[0].y=0;
	g_Quad.v[1].x=800;
	g_Quad.v[1].y=0;
	g_Quad.v[2].x=800;
	g_Quad.v[2].y=600;
	g_Quad.v[3].x=0;
	g_Quad.v[3].y=600;

	g_hTex=g_pApp->Texture_Load("cursor.png");
	g_hSound=g_pApp->Effect_Load("menu.wav");
	g_hFont=g_pApp->Font_Create(40, 0, 0, FALSE, "΢���ź�");

	g_pSpr=new CSprite(g_hTex, 0, 0, 32, 32);

	g_pGUI=new CGUI;
	g_pGUI->AddCtrl(new CMenuItem(1, g_hFont, g_hSound, 400, 200, 0.0f, "Play"));
	g_pGUI->AddCtrl(new CMenuItem(2, g_hFont, g_hSound, 400, 240, 0.1f, "Options"));
	g_pGUI->AddCtrl(new CMenuItem(3, g_hFont, g_hSound, 400, 280, 0.2f, "Instructions"));
	g_pGUI->AddCtrl(new CMenuItem(4, g_hFont, g_hSound, 400, 320, 0.3f, "Credits"));
	g_pGUI->AddCtrl(new CMenuItem(5, g_hFont, g_hSound, 400, 360, 0.4f, "Exit"));
	g_pGUI->SetNavMode(NAV_UPDOWN|NAV_CYCLED);
	g_pGUI->SetCursor(g_pSpr);
	g_pGUI->SetFocus(1);
	g_pGUI->Enter();

	return S_OK;  // ����S_OK��ʾ��Դ��ʼ���ɹ�
}

void CEventHandler::ReleaseResource()
{
	// �ڴ������Դ�ͷŴ���
	// �����ڲ�����ϵͳ�����Զ��ͷ��������弰������Դ
	delete g_pGUI;
	delete g_pSpr;
}

// float fDelta: ��һ֡�͵�ǰ֡��ʱ����������Ϊ��λ
BOOL CEventHandler::Frame(float fDelta)
{
	// �ڴ������Ϸ�߼����ƴ���
	static int nLastID=0;

	if (g_pApp->Input_KeyPressed(VK_ESCAPE))
	{
		nLastID=5;
		g_pGUI->Exit();
	}

	int nID=g_pGUI->Update(fDelta);

	if (nID==-1)
	{
		switch (nLastID)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			g_pGUI->SetFocus(1);
			g_pGUI->Enter();
			break;
		case 5:
			return TRUE;
		}
	}
	else if (nID>0)
	{
		nLastID=nID;
		g_pGUI->Exit();
	}

	float t=g_pApp->Timer_GetTime(), tu=50*cosf(t/60), tv=50*sinf(t/60);

	g_Quad.v[0].tu=tu;
	g_Quad.v[0].tv=tv;
	g_Quad.v[1].tu=tu+800/64;
	g_Quad.v[1].tv=tv;
	g_Quad.v[2].tu=tu+800/64;
	g_Quad.v[2].tv=tv+600/64;
	g_Quad.v[3].tu=tu;
	g_Quad.v[3].tv=tv+600/64;

	return FALSE;  // ����FALSE��ʾ��Ϸδ����
}

void CEventHandler::Render()
{
	// �ڴ������Ⱦ����
	char szBuf[256];
	RECT rect={0, 0, 0, 0};

	sprintf(szBuf, "FPS: %d", g_pApp->Timer_GetFPS());

	g_pApp->Gfx_Clear();
	g_pApp->Gfx_RenderQuad(&g_Quad);
	g_pGUI->Render();
	g_pApp->Font_DrawText(g_hFont, szBuf, &rect, 0, DT_CALCRECT);
	g_pApp->Font_DrawText(g_hFont, szBuf, &rect);
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
	g_pApp->System_SetState(RUGE_CAPTION, "Creating Menus");  // ���ô��ڱ���
	g_pApp->System_SetState(RUGE_HIDECURSOR, TRUE);  // ����ϵͳ���ָ��
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