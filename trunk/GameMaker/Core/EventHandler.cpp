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

CEventHandler::CEventHandler(LuaPlus::LuaState *lua)
	: m_pApp(RUGE::GetRUGE())
	, m_pLua(lua)
{
}

CEventHandler::~CEventHandler()
{
	m_pApp->Release();
}

HRESULT CEventHandler::InitResource()
{
	// 在此添加资源初始化代码
	if (!m_pLua->GetGlobal("InitResource").IsFunction()) return S_OK;
	
	LuaPlus::LuaFunction<bool> Lua_InitResource=m_pLua->GetGlobal("InitResource");

	return Lua_InitResource() ? S_OK : -1;  // 返回S_OK表示资源初始化成功
}

void CEventHandler::ReleaseResource()
{
	// 在此添加资源释放代码
	// 引擎内部管理系统可以自动释放纹理、字体及声音资源
	if (!m_pLua->GetGlobal("ReleaseResource").IsFunction()) return;

	LuaPlus::LuaFunction<void> Lua_ReleaseResource=m_pLua->GetGlobal("ReleaseResource");

	Lua_ReleaseResource();
}

// float fDelta: 上一帧和当前帧的时间间隔，以秒为单位
BOOL CEventHandler::Frame(float fDelta)
{
	// 在此添加游戏逻辑控制代码
	if (!m_pLua->GetGlobal("Frame").IsFunction()) return FALSE;

	LuaPlus::LuaFunction<bool> Lua_Frame=m_pLua->GetGlobal("Frame");

	return Lua_Frame(fDelta) ? TRUE : FALSE;  // 返回FALSE表示游戏未结束
}

void CEventHandler::Render()
{
	// 在此添加渲染代码
	if (!m_pLua->GetGlobal("Render").IsFunction()) return;

	LuaPlus::LuaFunction<void> Lua_Render=m_pLua->GetGlobal("Render");

	Lua_Render();
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
	switch (uMsg)
	{
	case WM_SYSKEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			m_pApp->System_SetState(RUGE::APP_WINDOWED, !m_pApp->System_GetState(RUGE::APP_WINDOWED));
			break;
		}
		break;
	}
}
