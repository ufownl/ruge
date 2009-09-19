#include <RUGE.h>
#pragma comment(lib, "RUGE.lib")

#include <DistortionMesh.h>
#ifdef _DEBUG
#pragma comment(lib, "Helper_Debug.lib")
#else
#pragma comment(lib, "Helper.lib")
#endif  // _DEBUG

#include <math.h>

PAPPLICATION g_pApp;  // 定义RUGE Application接口指针

HFONTX g_hFont;
HTEXTURE g_hTex;

CDistortionMesh *g_pDis;

const int g_cnRows=16, g_cnCols=16;
const float g_cfCellW=512.0f/(g_cnCols-1), g_cfCellH=512.0f/(g_cnRows-1), g_cfDisX=144, g_cfDisY=44;

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
	g_hFont=g_pApp->Font_Create(20, 0, 0, FALSE, "微软雅黑");
	g_hTex=g_pApp->Texture_Load("texture.jpg");

	g_pDis=new CDistortionMesh(g_cnRows, g_cnCols);
	g_pDis->SetTexture(g_hTex);
	g_pDis->SetTextureRect(0, 0, 512, 512);
	g_pDis->SetBlendMode(BLEND_COLORADD|BLEND_ALPHABLEND|BLEND_ZWRITE);
	g_pDis->Clear(0xFF000000);

	return S_OK;  // 返回S_OK表示资源初始化成功
}

void CEventHandler::ReleaseResource()
{
	// 在此添加资源释放代码
	// 引擎内部管理系统可以自动释放纹理、字体及声音资源
	delete g_pDis;
}

// float fDelta: 上一帧和当前帧的时间间隔，以秒为单位
BOOL CEventHandler::Frame(float fDelta)
{
	// 在此添加游戏逻辑控制代码
	static float fTime=0;
	static int nTrans=0;
	
	fTime+=fDelta;

	switch (g_pApp->Input_GetKey())
	{
	case VK_ESCAPE:
		return TRUE;
	case VK_SPACE:
		nTrans=(nTrans+1)%3;
		g_pDis->Clear(0xFF000000);
		break;
	default:
		break;
	}

	switch (nTrans)
	{
	case 0:
		for (int i=1; i<g_cnRows-1; i++)
		{
			for (int j=1; j<g_cnCols-1; j++)
			{
				g_pDis->SetDisplacement(i, j, cosf(fTime*10+(i+j)/2)*5, sinf(fTime*10+(i+j)/2)*5, DISP_NODE);
			}
		}
		break;
	case 1:
		for (int i=0; i<g_cnRows; i++)
		{
			for (int j=1; j<g_cnCols-1; j++)
			{
				DWORD dwColor=(DWORD)((cosf(fTime*5+(i+j)/2)+1)*35);

				g_pDis->SetDisplacement(i, j, cosf(fTime*5+j/2)*15, 0, DISP_NODE);
				g_pDis->SetColor(i, j, 0xFF<<24|dwColor<<16|dwColor<<8|dwColor);
			}
		}
		break;
	case 2:
		for(int i=0; i<g_cnRows; i++)
		{
			for(int j=0; j<g_cnCols; j++)
			{
				float fr=sqrtf(powf(j-(float)g_cnCols/2, 2)+powf(i-(float)g_cnRows/2, 2)), fa=fr*cosf(fTime*2)*0.1f,
					fdx=sinf(fa)*(i*g_cfCellH-256)+cosf(fa)*(j*g_cfCellW-256), fdy=cosf(fa)*(i*g_cfCellH-256)-sinf(fa)*(j*g_cfCellW-256);
				DWORD dwColor=(DWORD)((cosf(fr+fTime*4)+1)*40);

				g_pDis->SetDisplacement(i, j, fdx, fdy, DISP_CENTER);
				g_pDis->SetColor(i, j, 0xFF<<24|dwColor<<16|(dwColor/2)<<8);
			}
		}
		break;
	}
	return FALSE;  // 返回FALSE表示游戏未结束
}

void CEventHandler::Render()
{
	// 在此添加渲染代码
	g_pApp->Gfx_Clear();
	g_pDis->Render(g_cfDisX, g_cfDisY);

	static RECT Rect={0, 0, 100, 20};
	char szBuf[256];

	sprintf(szBuf, "FPS: %d", g_pApp->System_GetState(RUGE_FPS));
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
	g_pApp=GetRUGE(RUGE_VERSION);  // 获取RUGE Application对象
	if (g_pApp==NULL)
	{
		puts("Error: RUGE Application对象获取失败");
		system("Pause");
		return -1;
	}
	g_pApp->System_SetState(RUGE_EVENTHANDLER, &CEventHandler());  // 设置事件处理对象
	g_pApp->System_SetState(RUGE_CAPTION, "Using Distortion Mesh");  // 设置窗口标题
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