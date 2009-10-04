#include "StdAfx.h"
#include "EventHandler.h"

CEventHandler::CEventHandler()
	: m_pApp(GetRUGE())
	, m_pSpr(NULL)
	, m_pscMenu(NULL)
	, m_pSceneManager(NULL)
	, m_hFont(NULL)
{
}

CEventHandler::~CEventHandler()
{
	m_pApp->Release();
}

HRESULT CEventHandler::InitResource()
{
	// 在此添加资源初始化代码
	m_hFont=m_pApp->Font_Create(20, 0, 0, FALSE, "Fixedsys");
	m_hTex=m_pApp->Texture_Load("bg.png");
	
	m_pSpr=new CSprite(m_hTex, 0, 0, 800, 600);

	m_pscMenu=new CMenuScene;
	m_pSceneManager=new CSceneManager(m_pscMenu);

	return S_OK;  // 返回S_OK表示资源初始化成功
}

void CEventHandler::ReleaseResource()
{
	// 在此添加资源释放代码
	// 引擎内部管理系统可以自动释放纹理、字体及声音资源
	delete m_pSceneManager;
	delete m_pscMenu;
	delete m_pSpr;
}

// float fDelta: 上一帧和当前帧的时间间隔，以秒为单位
BOOL CEventHandler::Frame(float fDelta)
{
	// 在此添加游戏逻辑控制代码
	m_pSpr->SetTextureRect(50*sinf(m_pApp->Timer_GetTime()), 50*cosf(m_pApp->Timer_GetTime()), 800, 600);
	return m_pSceneManager->Update(fDelta);
}

void CEventHandler::Render()
{
	// 在此添加渲染代码
	m_pApp->Gfx_Clear();
	m_pSpr->Render(0, 0);
	m_pSceneManager->Render();

	char szBuf[256];
	RECT rect={0, 0, 0, 0};

	sprintf(szBuf, "FPS: %d", m_pApp->Timer_GetFPS());
	m_pApp->Font_DrawText(m_hFont, szBuf, &rect, 0, DT_CALCRECT);
	m_pApp->Font_DrawText(m_hFont, szBuf, &rect);
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
