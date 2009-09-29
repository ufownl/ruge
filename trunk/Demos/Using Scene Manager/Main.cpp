#include "StdAfx.h"
#include "MenuScene.h"

PAPPLICATION g_pApp;  // ����RUGE Application�ӿ�ָ��

CMenuScene *g_pMenuScene;
CSceneManager *g_pSceneManager;

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
	g_pMenuScene=new CMenuScene();
	g_pSceneManager=new CSceneManager(g_pMenuScene);
	return S_OK;  // ����S_OK��ʾ��Դ��ʼ���ɹ�
}

void CEventHandler::ReleaseResource()
{
	// �ڴ������Դ�ͷŴ���
	// �����ڲ�����ϵͳ�����Զ��ͷ��������弰������Դ
	delete g_pSceneManager;
	delete g_pMenuScene;
}

// float fDelta: ��һ֡�͵�ǰ֡��ʱ����������Ϊ��λ
BOOL CEventHandler::Frame(float fDelta)
{
	// �ڴ������Ϸ�߼����ƴ���
	return g_pSceneManager->Update(fDelta);
}

void CEventHandler::Render()
{
	// �ڴ������Ⱦ����
	g_pApp->Gfx_Clear();
	g_pSceneManager->Render();
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
	g_pApp->System_SetState(RUGE_CAPTION, "Using Scene Manager");  // ���ô��ڱ���
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