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

PAPPLICATION g_pApp;  // 定义RUGE Application接口指针
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

	return S_OK;  // 返回S_OK表示资源初始化成功
}

void CEventHandler::ReleaseResource()
{
	// 在此添加资源释放代码
	// 引擎内部管理系统可以自动释放纹理、字体及声音资源
	delete[] g_pObjs;
	delete g_pSprBg;
	delete g_pSpr;
	g_pRand.Release();
	
}

// float fDelta: 上一帧和当前帧的时间间隔，以秒为单位
BOOL CEventHandler::Frame(float fDelta)
{
	// 在此添加游戏逻辑控制代码
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

	return FALSE;  // 返回FALSE表示游戏未结束
}

void CEventHandler::Render()
{
	// 在此添加渲染代码
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
	g_pApp->System_SetState(RUGE_CAPTION, "Thousand of Hares");  // 设置窗口标题
	g_pApp->System_SetState(RUGE_VSYNC, VSYNC_IMMEDIATE);  // 关闭垂直同步
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