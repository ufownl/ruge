#include "StdAfx.h"
#include "EventHandler.h"

int main(int argc, char *argv[])
{
	HRESULT hr=0;  // ���򷵻�ֵ
	PAPPLICATION pApp=NULL;  // ����RUGE Application�ӿ�ָ��

	CoInitialize(NULL);  // ��ʼ��COM��
	pApp=GetRUGE();  // ��ȡRUGE Application����
	if (pApp==NULL)
	{
		puts("Error: RUGE Application�����ȡʧ��");
		system("Pause");
		return -1;
	}
	pApp->System_SetState(RUGE_EVENTHANDLER, &CEventHandler());  // �����¼��������
	pApp->System_SetState(RUGE_CAPTION, "Crazy Stars");  // ���ô��ڱ���
	pApp->System_SetState(RUGE_HIDECURSOR, TRUE);  // ����ϵͳ���ָ��
	pApp->System_SetState(RUGE_VSYNC, VSYNC_ONE);  // ������ֱͬ��
	hr=pApp->System_Initialize();  // ��ʼ��RUGE Application����
	if (SUCCEEDED(hr)) hr=pApp->System_Run();  // ������ѭ��
	else
	{
		printf("Error: RUGE Application�����ʼ��ʧ��\nError Code: %d\n", hr);
		system("Pause");
	}
	pApp->Release();  // �ͷ�RUGE Application����
	CoUninitialize();  // �ͷ�COM��
	return hr;
}