#include "StdAfx.h"
#include "MenuItem.h"

PAPPLICATION g_pApp;  // 定义RUGE Application接口指针

QUAD g_Quad;
HTEXTURE g_hTex;
HAUDIO g_hSound;
HFONTX g_hFont;

CGUI *g_pGUI;
CSprite *g_pSpr;

class CEventHandler : public IApplicationEventHandler  // 实现RUGE Application事件处理接口
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
	// 在此添加资源初始化代码
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
	g_hFont=g_pApp->Font_Create(40, 0, 0, FALSE, "微软雅黑");

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

	return S_OK;  // 返回S_OK表示资源初始化成功
}

void CEventHandler::ReleaseResource()
{
	// 在此添加资源释放代码
	// 引擎内部管理系统可以自动释放纹理、字体及声音资源
	delete g_pGUI;
	delete g_pSpr;
}

// float fDelta: 上一帧和当前帧的时间间隔，以秒为单位
BOOL CEventHandler::Frame(float fDelta)
{
	// 在此添加游戏逻辑控制代码
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

	return FALSE;  // 返回FALSE表示游戏未结束
}

void CEventHandler::Render()
{
	// 在此添加渲染代码
	char szBuf[256];
	RECT rect={0, 0, 0, 0};

	sprintf(szBuf, "FPS: %d", g_pApp->Timer_GetFPS());

	g_pApp->Gfx_Clear();
	g_pApp->Gfx_RenderQuad(&g_Quad);
	g_pGUI->Render();
	g_pApp->Font_DrawText(g_hFont, szBuf, &rect, 0, DT_CALCRECT);
	g_pApp->Font_DrawText(g_hFont, szBuf, &rect);
}

// int nPitch: 图像中一行像素点在缓冲区中所占空间的字节数
// void *pBits: 即将渲染到屏幕的图像数据缓冲区指针，一个像素点占4个字节，格
//              如下：0xAARRGGBB
void CEventHandler::Pretreat(int nPitch, void *pBits)
{
	// 在此添加图像预处理代码
}

// UINT uMsg: WINDOWS消息代码
// WPARAM wParam: WINDOWS消息WPARAM参数
// LPARAM lParam: WINDOWS消息LPARAM参数
void CEventHandler::WndEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 在此添加窗口消息处理代码
}

int main(int argc, char *argv[])
{
	HRESULT hr=0;  // 程序返回值

	CoInitialize(NULL);  // 初始化COM库
	g_pApp=GetRUGE();  // 获取RUGE Application对象
	if (g_pApp==NULL)
	{
		puts("Error: RUGE Application对象获取失败");
		system("Pause");
		return -1;
	}
	g_pApp->System_SetState(RUGE_EVENTHANDLER, &CEventHandler());  // 设置事件处理对象
	g_pApp->System_SetState(RUGE_CAPTION, "Creating Menus");  // 设置窗口标题
	g_pApp->System_SetState(RUGE_HIDECURSOR, TRUE);  // 隐藏系统鼠标指针
	g_pApp->System_SetState(RUGE_VSYNC, VSYNC_ONE);  // 开启垂直同步
	hr=g_pApp->System_Initialize();  // 初始化RUGE Application对象
	if (SUCCEEDED(hr)) hr=g_pApp->System_Run();  // 进入主循环
	else
	{
		printf("Error: RUGE Application对象初始化失败\nError Code: %d\n", hr);
		system("Pause");
	}
	g_pApp->Release();  // 释放RUGE Application对象
	CoUninitialize();  // 释放COM库
	return hr;
}