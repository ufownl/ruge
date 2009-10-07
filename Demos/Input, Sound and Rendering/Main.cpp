#include <RUGE.h>
#ifdef _DEBUG
#pragma comment(lib, "RUGE_Debug.lib")
#else
#pragma comment(lib, "RUGE.lib")
#endif  // _DEBUG

RUGE::PAPPLICATION g_pApp;  // 定义RUGE Application接口指针

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

class CEventHandler : public RUGE::IApplicationEventHandler  // 实现RUGE Application事件处理接口
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
	g_hFont=g_pApp->Font_Create(20, 0, 0, FALSE, "微软雅黑");
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

	return S_OK;  // 返回S_OK表示资源初始化成功
}

void CEventHandler::ReleaseResource()
{
	// 在此添加资源释放代码
	// 引擎内部管理系统可以自动释放纹理、字体及声音资源
}

// float fDelta: 上一帧和当前帧的时间间隔，以秒为单位
BOOL CEventHandler::Frame(float fDelta)
{
	// 在此添加游戏逻辑控制代码
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

	return FALSE;  // 返回FALSE表示游戏未结束
}

void CEventHandler::Render()
{
	// 在此添加渲染代码
	g_pApp->Gfx_Clear();
	g_pApp->Gfx_RenderQuad(&g_Quad);

	static RECT Rect={0, 0, 100, 20};
	char szBuf[256];

	sprintf(szBuf, "FPS: %d", g_pApp->Timer_GetFPS());
	g_pApp->Font_DrawText(g_hFont, szBuf, &Rect);
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
	g_pApp=RUGE::GetRUGE();  // 获取RUGE Application对象
	if (g_pApp==NULL)
	{
		puts("Error: RUGE Application对象获取失败");
		system("Pause");
		return -1;
	}
	g_pApp->System_SetState(RUGE::APP_EVENTHANDLER, &CEventHandler());  // 设置事件处理对象
	g_pApp->System_SetState(RUGE::APP_CAPTION, "Input, Sound and Rendering");  // 设置窗口标题
	g_pApp->System_SetState(RUGE::APP_VSYNC, VSYNC_ONE);  // 开启垂直同步
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