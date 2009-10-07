#include "StdAfx.h"
#include "EventHandler.h"

int main(int argc, char *argv[])
{
	HRESULT hr=0;  // 程序返回值
	RUGE::PAPPLICATION pApp=NULL;  // 定义RUGE Application接口指针

	CoInitialize(NULL);  // 初始化COM库
	pApp=RUGE::GetRUGE();  // 获取RUGE Application对象
	if (pApp==NULL)
	{
		puts("Error: RUGE Application对象获取失败");
		system("Pause");
		return -1;
	}
	pApp->System_SetState(RUGE::APP_EVENTHANDLER, &CEventHandler());  // 设置事件处理对象
	pApp->System_SetState(RUGE::APP_CAPTION, "Crazy Stars");  // 设置窗口标题
	pApp->System_SetState(RUGE::APP_HIDECURSOR, TRUE);  // 隐藏系统鼠标指针
	pApp->System_SetState(RUGE::APP_VSYNC, VSYNC_ONE);  // 开启垂直同步
	hr=pApp->System_Initialize();  // 初始化RUGE Application对象
	if (SUCCEEDED(hr)) hr=pApp->System_Run();  // 进入主循环
	else
	{
		printf("Error: RUGE Application对象初始化失败\nError Code: %d\n", hr);
		system("Pause");
	}
	pApp->Release();  // 释放RUGE Application对象
	CoUninitialize();  // 释放COM库
	return hr;
}