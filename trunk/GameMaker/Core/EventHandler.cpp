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
	// �ڴ������Դ��ʼ������
	if (!m_pLua->GetGlobal("InitResource").IsFunction()) return S_OK;
	
	LuaPlus::LuaFunction<bool> Lua_InitResource=m_pLua->GetGlobal("InitResource");

	return Lua_InitResource() ? S_OK : -1;  // ����S_OK��ʾ��Դ��ʼ���ɹ�
}

void CEventHandler::ReleaseResource()
{
	// �ڴ������Դ�ͷŴ���
	// �����ڲ�����ϵͳ�����Զ��ͷ��������弰������Դ
	if (!m_pLua->GetGlobal("ReleaseResource").IsFunction()) return;

	LuaPlus::LuaFunction<void> Lua_ReleaseResource=m_pLua->GetGlobal("ReleaseResource");

	Lua_ReleaseResource();
}

// float fDelta: ��һ֡�͵�ǰ֡��ʱ����������Ϊ��λ
BOOL CEventHandler::Frame(float fDelta)
{
	// �ڴ������Ϸ�߼����ƴ���
	if (!m_pLua->GetGlobal("Frame").IsFunction()) return FALSE;

	LuaPlus::LuaFunction<bool> Lua_Frame=m_pLua->GetGlobal("Frame");

	return Lua_Frame(fDelta) ? TRUE : FALSE;  // ����FALSE��ʾ��Ϸδ����
}

void CEventHandler::Render()
{
	// �ڴ������Ⱦ����
	if (!m_pLua->GetGlobal("Render").IsFunction()) return;

	LuaPlus::LuaFunction<void> Lua_Render=m_pLua->GetGlobal("Render");

	Lua_Render();
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
