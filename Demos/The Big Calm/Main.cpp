#include <RUGE.h>
#ifdef _DEBUG
#pragma comment(lib, "RUGE_Debug.lib")
#else
#pragma comment(lib, "RUGE.lib")
#endif  // _DEBUG

#include <Sprite.h>
#include <DistortionMesh.h>
#include <Color.h>
#ifdef _DEBUG
#pragma comment(lib, "Helper_Debug.lib")
#else
#pragma comment(lib, "Helper.lib")
#endif  // _DEBUG

#include <math.h>

PAPPLICATION g_pApp;  // 定义RUGE Application接口指针

HFONTX g_hFont;

int g_nSpeed=-1;

#define M_PI	3.14159265358979323846f
#define M_PI_2	1.57079632679489661923f

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define NUM_STARS		100
#define SEA_SUBDIVISION 16

#define SKY_HEIGHT		(SCREEN_HEIGHT*0.6f)
#define STARS_HEIGHT	(SKY_HEIGHT*0.9f)
#define ORBITS_RADIUS	(SCREEN_WIDTH*0.43f)

DWORD g_dwSkyTopColors[]={0xFF15092A, 0xFF6C6480, 0xFF89B9D0};
DWORD g_dwSkyBtmColors[]={0xFF303E57, 0xFFAC7963, 0xFFCAD7DB};
DWORD g_dwSeaTopColors[]={0xFF3D546B, 0xFF927E76, 0xFF86A2AD};
DWORD g_dwSeaBtmColors[]={0xFF1E394C, 0xFF2F4E64, 0xFF2F4E64};

int g_nSeq[]={0, 0, 1, 2, 2, 2, 1, 0, 0};

HTEXTURE g_hTex;

CSprite	*g_psprSky, *g_psprSun, *g_psprMoon, *g_psprGlow, *g_psprSeaGlow, *g_psprStar;
CDistortionMesh *g_pdisSea;
CColor	g_colWhite;

float g_fTime, g_fSpeed;

int	  g_nSeqID;
float g_fSeqResidue;
float g_fStarX[NUM_STARS], g_fStarY[NUM_STARS], g_fStarS[NUM_STARS], g_fStarA[NUM_STARS];
float g_fSeaP[SEA_SUBDIVISION];

CColor g_colSkyTop, g_colSkyBtm, g_colSeaTop, g_colSeaBtm;
CColor g_colSun, g_colSunGlow, g_colMoon, g_colMoonGlow, g_colSeaGlow;

float g_fSunX, g_fSunY, g_fSunS, g_SunGlowS;
float g_fMoonX, g_fMoonY, g_fMoonS, g_fMoonGlowS;
float g_fSeaGlowX, g_fSeaGlowSX, g_fSeaGlowSY;

void InitSimulation();
void DoneSimulation();
void UpdateSimulation(float fDelta);
void RenderSimulation();

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
	g_hFont=g_pApp->Font_Create(20, 0, 0, FALSE, "Fixedsys");
	InitSimulation();
	return S_OK;  // 返回S_OK表示资源初始化成功
}

void CEventHandler::ReleaseResource()
{
	// 在此添加资源释放代码
	// 引擎内部管理系统可以自动释放纹理、字体及声音资源
	DoneSimulation();
}

// float fDelta: 上一帧和当前帧的时间间隔，以秒为单位
BOOL CEventHandler::Frame(float fDelta)
{
	// 在此添加游戏逻辑控制代码
	int nVKey=g_pApp->Input_GetKey();

	if (nVKey>0)
	{
		switch (nVKey)
		{
		case VK_ESCAPE:
			return TRUE;
		case VK_UP:
			if (g_nSpeed<8) g_nSpeed++;
			break;
		case VK_DOWN:
			if (g_nSpeed>-1) g_nSpeed--;
			break;
		case VK_RETURN:
			g_nSpeed=-1;
			break;
		}
		if (g_nSpeed==-1) g_fSpeed=0;
		else g_fSpeed=powf(2, (float)g_nSpeed)/10;
	}
	UpdateSimulation(fDelta);
	return FALSE;  // 返回FALSE表示游戏未结束
}

void CEventHandler::Render()
{
	// 在此添加渲染代码
	g_pApp->Gfx_Clear();
	RenderSimulation();

	static RECT Rect={0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	int nHrs, nMins, nSecs;
	float fTemp;
	char szBuf[256];

	// Calculate display time

	nHrs=(int)floorf(g_fTime);
	fTemp=(g_fTime-nHrs)*60.0f;
	nMins=(int)floorf(fTemp);
	nSecs=(int)floorf((fTemp-nMins)*60.0f);
	sprintf(szBuf, "%02d:%02d:%02d\nSpeed: %d\nFPS: %d", nHrs, nMins, nSecs, g_nSpeed+1, g_pApp->Timer_GetFPS());
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
	g_pApp=GetRUGE();  // 获取RUGE Application对象
	if (g_pApp==NULL)
	{
		puts("Error: RUGE Application对象获取失败");
		system("Pause");
		return -1;
	}
	g_pApp->System_SetState(RUGE_EVENTHANDLER, &CEventHandler());  // 设置事件处理对象
	g_pApp->System_SetState(RUGE_CAPTION, "The Big Calm");  // 设置窗口标题
	g_pApp->System_SetState(RUGE_VSYNC, VSYNC_ONE);  // 开启垂直同步
	g_pApp->System_SetState(RUGE_MAGFILTER, TEXF_LINEAR);
	g_pApp->System_SetState(RUGE_MINFILTER, TEXF_LINEAR);
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

float GetTime()
{
	SYSTEMTIME SysTime;
	float fTemp;

	GetLocalTime(&SysTime);
	fTemp=SysTime.wSecond;
	fTemp=SysTime.wMinute+fTemp/60.0f;
	fTemp=SysTime.wHour+fTemp/60.0f;

	return fTemp;
}

void InitSimulation()
{
	g_hTex=g_pApp->Texture_Load("objects.png");

	g_psprSky=new CSprite(NULL, 0, 0, SCREEN_WIDTH, SKY_HEIGHT);
	g_pdisSea=new CDistortionMesh(SEA_SUBDIVISION, SEA_SUBDIVISION);
	g_pdisSea->SetTextureRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT-SKY_HEIGHT);

	g_psprSun=new CSprite(g_hTex, 81, 0, 114, 114);
	g_psprSun->SetHotSpot(57, 57);
	g_psprMoon=new CSprite(g_hTex, 0, 0, 81, 81);
	g_psprMoon->SetHotSpot(40, 40);
	g_psprStar=new CSprite(g_hTex, 72, 81, 9, 9);
	g_psprStar->SetHotSpot(5, 5);

	g_psprGlow=new CSprite(g_hTex, 128, 128, 128, 128);
	g_psprGlow->SetHotSpot(64, 64);
	g_psprGlow->SetBlendMode(BLEND_COLORADD|BLEND_ALPHABLEND|BLEND_NOZWRITE);
	g_psprSeaGlow=new CSprite(g_hTex, 128, 224, 128, 32);
	g_psprSeaGlow->SetHotSpot(64, 0);
	g_psprSeaGlow->SetBlendMode(BLEND_COLORADD|BLEND_ALPHAADD|BLEND_NOZWRITE);

	g_colWhite.SetColor(0xFFFFFFFF);
	g_fTime=GetTime();
	g_fSpeed=0.0f;

	for(int i=0; i<NUM_STARS; i++)
	{
		g_fStarX[i]=g_pApp->Random_Float(0, SCREEN_WIDTH);
		g_fStarY[i]=g_pApp->Random_Float(0, STARS_HEIGHT);
		g_fStarS[i]=g_pApp->Random_Float(0.1f, 0.7f);
	}

	for(int i=0; i<SEA_SUBDIVISION; i++) g_fSeaP[i]=i+g_pApp->Random_Float(-15.0f, 15.0f);
}

void DoneSimulation()
{
	delete g_psprSeaGlow;
	delete g_psprGlow;
	delete g_psprStar;
	delete g_psprMoon;
	delete g_psprSun;
	delete g_psprSky;
	delete g_pdisSea;
}

void UpdateSimulation(float fDelta)
{
	if(g_fSpeed==0.0f) g_fTime=GetTime();
	else
	{
		g_fTime+=fDelta*g_fSpeed;
		if(g_fTime>=24.0f) g_fTime-=24.0f;
	}

	g_nSeqID=(int)(g_fTime/3);
	g_fSeqResidue=g_fTime/3-g_nSeqID;

	CColor col1, col2;

	col1.SetColor(g_dwSkyTopColors[g_nSeq[g_nSeqID]]);
	col2.SetColor(g_dwSkyTopColors[g_nSeq[g_nSeqID+1]]);
	g_colSkyTop=col2*g_fSeqResidue+col1*(1.0f-g_fSeqResidue);

	col1.SetColor(g_dwSkyBtmColors[g_nSeq[g_nSeqID]]);
	col2.SetColor(g_dwSkyBtmColors[g_nSeq[g_nSeqID+1]]);
	g_colSkyBtm=col2*g_fSeqResidue+col1*(1.0f-g_fSeqResidue);
	
	col1.SetColor(g_dwSeaTopColors[g_nSeq[g_nSeqID]]);
	col2.SetColor(g_dwSeaTopColors[g_nSeq[g_nSeqID+1]]);
	g_colSeaTop=col2*g_fSeqResidue+col1*(1.0f-g_fSeqResidue);

	col1.SetColor(g_dwSeaBtmColors[g_nSeq[g_nSeqID]]);
	col2.SetColor(g_dwSeaBtmColors[g_nSeq[g_nSeqID+1]]);
	g_colSeaBtm=col2*g_fSeqResidue+col1*(1.0f-g_fSeqResidue);

	float a;

	if (g_nSeqID>=6 || g_nSeqID<2)
	{
		for(int i=0; i<NUM_STARS; i++)
		{
			a=1.0f-g_fStarY[i]/STARS_HEIGHT;
			a*=g_pApp->Random_Float(0.6f, 1.0f);
			if(g_nSeqID>=6) a*=sinf((g_fTime-18.0f)/6.0f*M_PI_2);
			else a*=sinf((1.0f-g_fTime/6.0f)*M_PI_2);
			g_fStarA[i]=a;
		}
	}

	if(g_nSeqID==2) a=sinf(g_fSeqResidue*M_PI_2);
	else if(g_nSeqID==5) a=cosf(g_fSeqResidue*M_PI_2);
	else if(g_nSeqID>2 && g_nSeqID<5) a=1.0f;
	else a=0.0f;
	
	g_colSun.SetColor(0xFFEAE1BE);
	g_colSun=g_colSun*(1-a)+g_colWhite*a;

	a=(cosf(g_fTime/6.0f*M_PI)+1.0f)/2.0f;
	if(g_nSeqID>=2 && g_nSeqID<=6)
	{
		g_colSunGlow=g_colWhite*a;
		g_colSunGlow.a=1.0f;
	}
	else g_colSunGlow.SetColor(0xFF000000);

	float fZenith=-(g_fTime/12.0f*M_PI-M_PI_2);

	g_fSunX=SCREEN_WIDTH*0.5f+cosf(fZenith)*ORBITS_RADIUS;
	g_fSunY=SKY_HEIGHT*1.2f+sinf(fZenith)*ORBITS_RADIUS;
	g_fSunS=1.0f-0.3f*sinf((g_fTime-6.0f)/12.0f*M_PI);
	g_SunGlowS=3.0f*(1.0f-a)+3.0f;

	if(g_nSeqID>=6) a=sinf((g_fTime-18.0f)/6.0f*M_PI_2);
	else a=sinf((1.0f-g_fTime/6.0f)*M_PI_2);
	g_colMoon.SetColor(0x20FFFFFF);
	g_colMoon=g_colMoon*(1-a)+g_colWhite*a;

	g_colMoonGlow=g_colWhite;
	g_colMoonGlow.a=0.5f*a;

	g_fMoonX=SCREEN_WIDTH*0.5f+cosf(fZenith-M_PI)*ORBITS_RADIUS;
	g_fMoonY=SKY_HEIGHT*1.2f+sinf(fZenith-M_PI)*ORBITS_RADIUS;
	g_fMoonS=1.0f-0.3f*sinf((g_fTime+6.0f)/12.0f*M_PI);
	g_fMoonGlowS=a*0.4f+0.5f;

	if(g_fTime>19.0f || g_fTime<4.5f)
	{
		a=0.2f;
		if(g_fTime>19.0f && g_fTime<20.0f) a*=(g_fTime-19.0f);
		else if(g_fTime>3.5f && g_fTime<4.5f) a*=1.0f-(g_fTime-3.5f);

		g_colSeaGlow=g_colMoonGlow;
		g_colSeaGlow.a=a;
		g_fSeaGlowX=g_fMoonX;
		g_fSeaGlowSX=g_fMoonGlowS*3.0f;
		g_fSeaGlowSY=g_fMoonGlowS*2.0f;
	}
	else if(g_fTime>6.5f && g_fTime<19.0f)
	{
		a=0.3f;
		if(g_fTime<7.5f) a*=(g_fTime-6.5f);
		else if(g_fTime>18.0f) a*=1.0f-(g_fTime-18.0f);

		g_colSeaGlow=g_colSunGlow;
		g_colSeaGlow.a=a;
		g_fSeaGlowX=g_fSunX;
		g_fSeaGlowSX=g_SunGlowS;
		g_fSeaGlowSY=g_SunGlowS*0.6f;
	}
	else g_colSeaGlow.a=0.0f;

	DWORD dwCol1, dwCol2;

	for(int i=1; i<SEA_SUBDIVISION-1; i++)
	{
		a=float(i)/(SEA_SUBDIVISION-1);
		col1=g_colSeaTop*(1-a)+g_colSeaBtm*a;
		dwCol1=col1.GetColor();
		a*=20;

		float fTime=2.0f*g_pApp->Timer_GetTime();

		for(int j=0; j<SEA_SUBDIVISION; j++)
		{
			float fdy=a*sinf(g_fSeaP[i]+(float(j)/(SEA_SUBDIVISION-1)-0.5f)*M_PI*16.0f-fTime);

			g_pdisSea->SetColor(i, j, dwCol1);
			g_pdisSea->SetDisplacement(i, j, 0, fdy, DISP_NODE);
		}
	}

	dwCol1=g_colSeaTop.GetColor();
	dwCol2=g_colSeaBtm.GetColor();

	for(int j=0; j<SEA_SUBDIVISION; j++)
	{
		g_pdisSea->SetColor(0, j, dwCol1);
		g_pdisSea->SetColor(SEA_SUBDIVISION-1, j, dwCol2);
	}

	float fPosX;

	if(g_fTime>19.0f || g_fTime<5.0f)
	{
		a=0.12f;
		if(g_fTime>19.0f && g_fTime<20.0f) a*=(g_fTime-19.0f);
		else if(g_fTime>4.0f && g_fTime<5.0f) a*=1.0f-(g_fTime-4.0f);
		fPosX=g_fMoonX;
	}
	else if(g_fTime>7.0f && g_fTime<17.0f)
	{
		a=0.14f;
		if(g_fTime<8.0f) a*=(g_fTime-7.0f);
		else if(g_fTime>16.0f) a*=1.0f-(g_fTime-16.0f);
		fPosX=g_fSunX;
	}
	else a=0.0f;

	const float cfCellW=SCREEN_WIDTH/(SEA_SUBDIVISION-1);

	if(a!=0.0f)
	{
		int k=(int)floorf(fPosX/cfCellW);
		float s1=(1.0f-(fPosX-k*cfCellW)/cfCellW), s2=(1.0f-((k+1)*cfCellW-fPosX)/cfCellW);

		if(s1>0.7f) s1=0.7f;
		if(s2>0.7f) s2=0.7f;

		s1*=a;
		s2*=a;

		for(int i=0; i<SEA_SUBDIVISION; i+=2)
		{
			a=sinf(float(i)/(SEA_SUBDIVISION-1)*M_PI_2);

			col1.SetColor(g_pdisSea->GetColor(i, k));
			col1+=g_colSun*s1*(1-a);
			col1.Clamp();
			g_pdisSea->SetColor(i, k, col1.GetColor());

			col1.SetColor(g_pdisSea->GetColor(i, k+1));
			col1+=g_colSun*s2*(1-a);
			col1.Clamp();
			g_pdisSea->SetColor(i, k+1, col1.GetColor());
		}
	}
}

void RenderSimulation()
{
	g_psprSky->SetColor(g_colSkyTop.GetColor(), 0);
	g_psprSky->SetColor(g_colSkyTop.GetColor(), 1);
	g_psprSky->SetColor(g_colSkyBtm.GetColor(), 2);
	g_psprSky->SetColor(g_colSkyBtm.GetColor(), 3);
	g_psprSky->Render(0, 0);

	if(g_nSeqID>=6 || g_nSeqID<2)
	{
		for(int i=0; i<NUM_STARS; i++)
		{
			g_psprStar->SetColor((DWORD(g_fStarA[i]*255.0f)<<24)|0xFFFFFF);
			g_psprStar->Render(g_fStarX[i], g_fStarY[i], 0.0f, g_fStarS[i]);
		}
	}

	g_psprGlow->SetColor(g_colSunGlow.GetColor());
	g_psprGlow->Render(g_fSunX, g_fSunY, 0.0f, g_SunGlowS);
	g_psprSun->SetColor(g_colSun.GetColor());
	g_psprSun->Render(g_fSunX, g_fSunY, 0.0f, g_fSunS);

	g_psprGlow->SetColor(g_colMoonGlow.GetColor());
	g_psprGlow->Render(g_fMoonX, g_fMoonY, 0.0f, g_fMoonGlowS);
	g_psprMoon->SetColor(g_colMoon.GetColor());
	g_psprMoon->Render(g_fMoonX, g_fMoonY, 0.0f, g_fMoonS);

	g_pdisSea->Render(0, SKY_HEIGHT);
	g_psprSeaGlow->SetColor(g_colSeaGlow.GetColor());
	g_psprSeaGlow->Render(g_fSeaGlowX, SKY_HEIGHT, 0.0f, g_fSeaGlowSX, g_fSeaGlowSY);
}