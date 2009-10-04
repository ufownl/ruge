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
	// �ڴ������Դ��ʼ������
	m_hFont=m_pApp->Font_Create(20, 0, 0, FALSE, "Fixedsys");
	m_hTex=m_pApp->Texture_Load("bg.png");
	
	m_pSpr=new CSprite(m_hTex, 0, 0, 800, 600);

	m_pscMenu=new CMenuScene;
	m_pSceneManager=new CSceneManager(m_pscMenu);

	return S_OK;  // ����S_OK��ʾ��Դ��ʼ���ɹ�
}

void CEventHandler::ReleaseResource()
{
	// �ڴ������Դ�ͷŴ���
	// �����ڲ�����ϵͳ�����Զ��ͷ��������弰������Դ
	delete m_pSceneManager;
	delete m_pscMenu;
	delete m_pSpr;
}

// float fDelta: ��һ֡�͵�ǰ֡��ʱ����������Ϊ��λ
BOOL CEventHandler::Frame(float fDelta)
{
	// �ڴ������Ϸ�߼����ƴ���
	m_pSpr->SetTextureRect(50*sinf(m_pApp->Timer_GetTime()), 50*cosf(m_pApp->Timer_GetTime()), 800, 600);
	return m_pSceneManager->Update(fDelta);
}

void CEventHandler::Render()
{
	// �ڴ������Ⱦ����
	m_pApp->Gfx_Clear();
	m_pSpr->Render(0, 0);
	m_pSceneManager->Render();

	char szBuf[256];
	RECT rect={0, 0, 0, 0};

	sprintf(szBuf, "FPS: %d", m_pApp->Timer_GetFPS());
	m_pApp->Font_DrawText(m_hFont, szBuf, &rect, 0, DT_CALCRECT);
	m_pApp->Font_DrawText(m_hFont, szBuf, &rect);
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
