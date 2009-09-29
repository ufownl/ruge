#include "StdAfx.h"
#include "MenuScene.h"

PAPPLICATION g_pApp;  // 定义RUGE Application接口指针

CMenuScene *g_pMenuScene;
CSceneManager *g_pSceneManager;

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
	g_pMenuScene=new CMenuScene();
	g_pSceneManager=new CSceneManager(g_pMenuScene);
	return S_OK;  // 返回S_OK表示资源初始化成功
}

void CEventHandler::ReleaseResource()
{
	// 在此添加资源释放代码
	// 引擎内部管理系统可以自动释放纹理、字体及声音资源
	delete g_pSceneManager;
	delete g_pMenuScene;
}

// float fDelta: 上一帧和当前帧的时间间隔，以秒为单位
BOOL CEventHandler::Frame(float fDelta)
{
	// 在此添加游戏逻辑控制代码
	return g_pSceneManager->Update(fDelta);
}

void CEventHandler::Render()
{
	// 在此添加渲染代码
	g_pApp->Gfx_Clear();
	g_pSceneManager->Render();
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
	g_pApp->System_SetState(RUGE_CAPTION, "Using Scene Manager");  // 设置窗口标题
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