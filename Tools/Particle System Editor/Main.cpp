/*
RUGE Copyright (C) 2009 ����UFO

This file is part of RUGE.

RUGE is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RUGE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RUGE.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "StdAfx.h"
#include "EventHandler.h"

int main(int argc, char *argv[])
{
	HRESULT hr=0;  // ���򷵻�ֵ
	RUGE::PAPPLICATION pApp=NULL;  // ����RUGE Application�ӿ�ָ��

	CoInitialize(NULL);  // ��ʼ��COM��
	pApp=RUGE::GetRUGE();  // ��ȡRUGE Application����
	if (pApp==NULL)
	{
		puts("Error: RUGE Application�����ȡʧ��");
		system("Pause");
		return -1;
	}
	pApp->System_SetState(RUGE::APP_EVENTHANDLER, &CEventHandler());  // �����¼��������
	pApp->System_SetState(RUGE::APP_CAPTION, "RUGE Particle System Editor");  // ���ô��ڱ���
	pApp->System_SetState(RUGE::APP_HIDECURSOR, TRUE);  // ����ϵͳ���ָ��
	pApp->System_SetState(RUGE::APP_VSYNC, VSYNC_ONE);  // ������ֱͬ��
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