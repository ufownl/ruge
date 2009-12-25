/*
RUGE GameMaker Copyright (C) 2009 ����UFO

This file is part of RUGE GameMaker.

RUGE GameMaker is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RUGE GameMaker is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RUGE GameMaker.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "StdAfx.h"
#include "EventHandler.h"
#include "Register.h"

int main(int argc, char *argv[])
{
	HRESULT hr=0;  // ���򷵻�ֵ
	RUGE::PAPPLICATION pApp=NULL;  // ����RUGE Application�ӿ�ָ��
	LuaPlus::LuaStateOwner lua(true);
	LPCSTR lpcszPath=(argc>1 ? argv[argc-1] : "Main.lua");

	CoInitialize(NULL);  // ��ʼ��COM��
	pApp=RUGE::GetRUGE();  // ��ȡRUGE Application����
	if (pApp==NULL)
	{
		puts("Error: RUGE Application�����ȡʧ��");
		system("Pause");
		return -1;
	}
	RegisterAPI(lua);
	lua->CheckStack(LUA_STACKSIZE);
	if (hr=-lua->DoFile(lpcszPath))
	{
		printf("Error: %s�ű�����\n", lpcszPath);
		system("pause");
	}
	else
	{
		if (lua->GetGlobal("InitEngine").IsFunction())
		{
			LuaPlus::LuaFunction<void> Lua_InitEngine=lua->GetGlobal("InitEngine");

			Lua_InitEngine();
		}
		pApp->System_SetState(RUGE::APP_EVENTHANDLER, &CEventHandler(lua));
		hr=pApp->System_Initialize();  // ��ʼ��RUGE Application����
		if (SUCCEEDED(hr)) hr=pApp->System_Run();  // ������ѭ��
		else
		{
			printf("Error: RUGE Application�����ʼ��ʧ��\nError Code: %d\n", hr);
			system("Pause");
		}
	}
	pApp->Release();  // �ͷ�RUGE Application����
	CoUninitialize();  // �ͷ�COM��
	return hr;
}
