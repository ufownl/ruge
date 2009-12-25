/*
RUGE GameMaker Copyright (C) 2009 游侠UFO

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
	HRESULT hr=0;  // 程序返回值
	RUGE::PAPPLICATION pApp=NULL;  // 定义RUGE Application接口指针
	LuaPlus::LuaStateOwner lua(true);
	LPCSTR lpcszPath=(argc>1 ? argv[argc-1] : "Main.lua");

	CoInitialize(NULL);  // 初始化COM库
	pApp=RUGE::GetRUGE();  // 获取RUGE Application对象
	if (pApp==NULL)
	{
		puts("Error: RUGE Application对象获取失败");
		system("Pause");
		return -1;
	}
	RegisterAPI(lua);
	lua->CheckStack(LUA_STACKSIZE);
	if (hr=-lua->DoFile(lpcszPath))
	{
		printf("Error: %s脚本错误\n", lpcszPath);
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
		hr=pApp->System_Initialize();  // 初始化RUGE Application对象
		if (SUCCEEDED(hr)) hr=pApp->System_Run();  // 进入主循环
		else
		{
			printf("Error: RUGE Application对象初始化失败\nError Code: %d\n", hr);
			system("Pause");
		}
	}
	pApp->Release();  // 释放RUGE Application对象
	CoUninitialize();  // 释放COM库
	return hr;
}
