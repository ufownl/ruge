/*
RUGE GameMaker Copyright (C) 2009 ”Œœ¿UFO

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
#include "RugeLuaCore.h"

int Lua_System_SetState(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	if (args.Count()==2 && args[1].IsInteger())
	{
		int nState=args[1].GetInteger();

		switch (nState/100)
		{
		case 1:
			if (args[2].IsString()) pApp->System_SetState((RUGE::AppStringState)(nState-100), args[2].GetString());
			break;
		case 2:
			if (args[2].IsInteger()) pApp->System_SetState((RUGE::AppIntState)(nState-200), args[2].GetInteger());
			break;
		case 3:
			if (args[2].IsBoolean()) pApp->System_SetState((RUGE::AppBoolState)(nState-300), (BOOL)args[2].GetBoolean());
			break;
		case 4:
			if (args[2].IsInteger()) pApp->System_SetState((RUGE::AppDwordState)(nState-400), args[2].GetInteger());
			break;
		}
	}
	pApp->Release();
	return 0;
}

int Lua_System_GetState(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	if (args.Count()==1 && args[1].IsInteger())
	{
		int nState=args[1].GetInteger();

		switch (nState/100)
		{
		case 1:
			lua->PushString(pApp->System_GetState((RUGE::AppStringState)(nState-100)));
			break;
		case 2:
			lua->PushInteger(pApp->System_GetState((RUGE::AppIntState)(nState-200)));
			break;
		case 3:
			lua->PushBoolean(pApp->System_GetState((RUGE::AppBoolState)(nState-300)) ? true : false);
			break;
		case 4:
			lua->PushInteger((int)pApp->System_GetState((RUGE::AppDwordState)(nState-400)));
			break;
		case 5:
			lua->PushLightUserData(pApp->System_GetState((RUGE::AppHandleState)(nState-500)));
			break;
		}
	}
	pApp->Release();
	return 1;
}

void Ini_SetInt(LPCSTR lpcszSection, LPCSTR lpcszName, int nVal)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	
	pApp->Ini_SetInt(lpcszSection, lpcszName, nVal);
	pApp->Release();
}

void Ini_SetFloat(LPCSTR lpcszSection, LPCSTR lpcszName, float fVal)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	
	pApp->Ini_SetFloat(lpcszSection, lpcszName, fVal);
	pApp->Release();
}

void Ini_SetString(LPCSTR lpcszSection, LPCSTR lpcszName, LPCSTR lpcszVal)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	
	pApp->Ini_SetString(lpcszSection, lpcszName, lpcszVal);
	pApp->Release();
}

int Lua_Ini_GetInt(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	LPCSTR lpcszSection=NULL, lpcszName=NULL;
	int nDef=0;

	switch (args.Count())
	{
	case 3:
		if (args[3].IsInteger()) nDef=args[3].GetInteger();
	case 2:
		if (args[1].IsString()) lpcszSection=args[1].GetString();
		if (args[2].IsString()) lpcszName=args[2].GetString();
		break;
	}

	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	int nRes=pApp->Ini_GetInt(lpcszSection, lpcszName, nDef);

	pApp->Release();
	
	lua->PushInteger(nRes);
	return 1;
}

int Lua_Ini_GetFloat(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	LPCSTR lpcszSection=NULL, lpcszName=NULL;
	float fDef=0;

	switch (args.Count())
	{
	case 3:
		if (args[3].IsNumber()) fDef=args[3].GetFloat();
	case 2:
		if (args[1].IsString()) lpcszSection=args[1].GetString();
		if (args[2].IsString()) lpcszName=args[2].GetString();
		break;
	}

	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	float fRes=pApp->Ini_GetFloat(lpcszSection, lpcszName, fDef);

	pApp->Release();
	
	lua->PushNumber(fRes);
	return 1;
}

int Lua_Ini_GetString(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	LPCSTR lpcszSection=NULL, lpcszName=NULL, lpcszDef=NULL;

	switch (args.Count())
	{
	case 3:
		if (args[3].IsString()) lpcszDef=args[3].GetString();
	case 2:
		if (args[1].IsString()) lpcszSection=args[1].GetString();
		if (args[2].IsString()) lpcszName=args[2].GetString();
		break;
	}

	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	LPCSTR lpcszRes=pApp->Ini_GetString(lpcszSection, lpcszName, lpcszDef);

	pApp->Release();
	
	lua->PushString(lpcszRes);
	return 1;
}

void Gfx_BeginTarget(RUGE::HTARGET hTarg)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Gfx_BeginTarget(hTarg);
	pApp->Release();
}

void Gfx_EndTarget()
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Gfx_EndTarget();
	pApp->Release();
}

int Lua_Gfx_Clear(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	int nColor=0;

	if (args.Count()==1 && args[1].IsInteger()) nColor=args[1].GetInteger();

	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Gfx_Clear(nColor);
	pApp->Release();

	return 0;
}

int Lua_Gfx_RenderLine(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::VERTEX v[2]={0};
	int nBlend=BLEND_DEFAULT;

	switch (args.Count())
	{
	case 3:
		if (args[3].IsInteger()) nBlend=args[3].GetInteger();
	case 2:
		for (int i=0; i<2; i++)
		{
			if (args[i+1].IsTable())
			{
				if (args[i+1]["x"].IsNumber()) v[i].x=args[i+1]["x"].GetFloat();
				if (args[i+1]["y"].IsNumber()) v[i].y=args[i+1]["y"].GetFloat();
				if (args[i+1]["z"].IsNumber()) v[i].z=args[i+1]["z"].GetFloat();
				if (args[i+1]["Color"].IsInteger()) v[i].dwColor=args[i+1]["Color"].GetInteger();
				if (args[i+1]["tu"].IsNumber()) v[i].tu=args[i+1]["tu"].GetFloat();
				if (args[i+1]["tv"].IsNumber()) v[i].tv=args[i+1]["tv"].GetFloat();
			}
		}
		break;
	}
	
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Gfx_RenderLine(v, v+1, nBlend);
	pApp->Release();

	return 0;
}

int Lua_Gfx_RenderTriangle(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::TRIANGLE Triangle={0};

	if (args.Count()==1 && args[1].IsTable())
	{
		if (args[1]["v"].IsTable())
		{
			for (int i=0; i<3; i++)
			{
				if (args[1]["v"][i+1].IsTable())
				{
					if (args[1]["v"][i+1]["x"].IsNumber()) Triangle.v[i].x=args[1]["v"][i+1]["x"].GetFloat();
					if (args[1]["v"][i+1]["y"].IsNumber()) Triangle.v[i].y=args[1]["v"][i+1]["y"].GetFloat();
					if (args[1]["v"][i+1]["z"].IsNumber()) Triangle.v[i].z=args[1]["v"][i+1]["z"].GetFloat();
					if (args[1]["v"][i+1]["Color"].IsInteger()) Triangle.v[i].dwColor=args[1]["v"][i+1]["Color"].GetInteger();
					if (args[1]["v"][i+1]["tu"].IsNumber()) Triangle.v[i].tu=args[1]["v"][i+1]["tu"].GetFloat();
					if (args[1]["v"][i+1]["tv"].IsNumber()) Triangle.v[i].tv=args[1]["v"][i+1]["tv"].GetFloat();
				}
			}
		}
		if (args[1]["Tex"].IsLightUserData()) Triangle.hTex=args[1]["Tex"].GetLightUserData();
		if (args[1]["Blend"].IsInteger()) Triangle.dwBlend=args[1]["Blend"].GetInteger();
	}

	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Gfx_RenderTriangle(&Triangle);
	pApp->Release();

	return 0;
}

int Lua_Gfx_RenderQuad(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::QUAD Quad={0};

	if (args.Count()==1 && args[1].IsTable())
	{
		if (args[1]["v"].IsTable())
		{
			for (int i=0; i<4; i++)
			{
				if (args[1]["v"][i+1].IsTable())
				{
					if (args[1]["v"][i+1]["x"].IsNumber()) Quad.v[i].x=args[1]["v"][i+1]["x"].GetFloat();
					if (args[1]["v"][i+1]["y"].IsNumber()) Quad.v[i].y=args[1]["v"][i+1]["y"].GetFloat();
					if (args[1]["v"][i+1]["z"].IsNumber()) Quad.v[i].z=args[1]["v"][i+1]["z"].GetFloat();
					if (args[1]["v"][i+1]["Color"].IsInteger()) Quad.v[i].dwColor=args[1]["v"][i+1]["Color"].GetInteger();
					if (args[1]["v"][i+1]["tu"].IsNumber()) Quad.v[i].tu=args[1]["v"][i+1]["tu"].GetFloat();
					if (args[1]["v"][i+1]["tv"].IsNumber()) Quad.v[i].tv=args[1]["v"][i+1]["tv"].GetFloat();
				}
			}
		}
		if (args[1]["Tex"].IsLightUserData()) Quad.hTex=args[1]["Tex"].GetLightUserData();
		if (args[1]["Blend"].IsInteger()) Quad.dwBlend=args[1]["Blend"].GetInteger();
	}

	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Gfx_RenderQuad(&Quad);
	pApp->Release();

	return 0;
}

int Lua_Gfx_Shotsnap(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	LPCSTR lpcszPath=NULL;
	int nIFF=IFF_BMP;

	switch (args.Count())
	{
	case 2:
		if (args[2].IsInteger()) nIFF=args[2].GetInteger();
	case 1:
		if (args[1].IsString()) lpcszPath=args[1].GetString();
		break;
	}

	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Gfx_Shotsnap(lpcszPath, nIFF);
	pApp->Release();

	return 0;
}

RUGE::HTEXTURE Texture_Create(int nWidth, int nHeight)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	RUGE::HTEXTURE hTex=pApp->Texture_Create(nWidth, nHeight);
	
	pApp->Release();
	return hTex;
}

RUGE::HTEXTURE Texture_Load(LPCSTR lpcszPath)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	RUGE::HTEXTURE hTex=pApp->Texture_Load(lpcszPath);

	pApp->Release();
	return hTex;
}

void Texture_Free(RUGE::HTEXTURE hTex)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Texture_Free(hTex);
	pApp->Release();
}

int Texture_GetWidth(RUGE::HTEXTURE hTex)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	int nRes=pApp->Texture_GetWidth(hTex);

	pApp->Release();
	return nRes;
}

int Texture_GetHeight(RUGE::HTEXTURE hTex)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	int nRes=pApp->Texture_GetHeight(hTex);

	pApp->Release();
	return nRes;
}

RUGE::HTARGET Target_Create(int nWidth, int nHeight)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	RUGE::HTARGET hTarg=pApp->Target_Create(nWidth, nHeight);

	pApp->Release();
	return hTarg;
}

void Target_Free(RUGE::HTARGET hTarg)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Target_Free(hTarg);
	pApp->Release();
}

RUGE::HTEXTURE Target_GetTexture(RUGE::HTARGET hTarg)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	RUGE::HTEXTURE hTex=pApp->Target_GetTexture(hTarg);

	pApp->Release();
	return hTex;
}

RUGE::HFONT Font_Create(int nHeight, int nWidth, int nWeight, bool bItalic, LPCSTR lpcszFont)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	RUGE::HFONT hFont=pApp->Font_Create(nHeight, nWidth, nWeight, (BOOL)bItalic, lpcszFont);

	pApp->Release();
	return hFont;
}

void Font_Free(RUGE::HFONT hFont)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Font_Free(hFont);
	pApp->Release();
}

int Lua_Font_DrawText(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::HFONT hFont=NULL;
	LPCSTR lpcszText=NULL;
	RECT rect={0};
	float z=0.0f;
	int nFormat=DT_TOP|DT_LEFT, nColor=0xFFFFFFFF;

	switch (args.Count())
	{
	case 6:
		if (args[6].IsInteger()) nColor=args[6].GetInteger();
	case 5:
		if (args[5].IsInteger()) nFormat=args[5].GetInteger();
	case 4:
		if (args[4].IsNumber()) z=args[4].GetFloat();
	case 3:
		if (args[1].IsLightUserData()) hFont=args[1].GetLightUserData();
		if (args[2].IsString()) lpcszText=args[2].GetString();
		if (args[3].IsTable())
		{
			if (args[3]["Left"].IsInteger()) rect.left=args[3]["Left"].GetInteger();
			if (args[3]["Top"].IsInteger()) rect.top=args[3]["Top"].GetInteger();
			if (args[3]["Right"].IsInteger()) rect.right=args[3]["Right"].GetInteger();
			if (args[3]["Bottom"].IsInteger()) rect.bottom=args[3]["Bottom"].GetInteger();
		}
		break;
	}

	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	int nRes=pApp->Font_DrawText(hFont, lpcszText, &rect, z, nFormat, nColor);

	pApp->Release();

	lua->PushInteger(nRes);
	
	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetInteger("Left", rect.left);
	table.SetInteger("Top", rect.top);
	table.SetInteger("Right", rect.right);
	table.SetInteger("Bottom", rect.bottom);
	return 2;
}

bool Input_KeyDown(int nVKey)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	bool bRes=(pApp->Input_KeyDown(nVKey) ? true : false);

	pApp->Release();
	return bRes;
}

bool Input_KeyPressed(int nVKey)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	bool bRes=(pApp->Input_KeyPressed(nVKey) ? true : false);

	pApp->Release();
	return bRes;
}

bool Input_KeyUp(int nVKey)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	bool bRes=(pApp->Input_KeyUp(nVKey) ? true : false);

	pApp->Release();
	return bRes;
}

int Input_GetKey()
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	int nRes=pApp->Input_GetKey();

	pApp->Release();
	return nRes;
}

int Input_GetChar()
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	int nRes=pApp->Input_GetChar();

	pApp->Release();
	return nRes;
}

LPCSTR Input_GetKeyName(int nVKey)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	LPCSTR lpcszRes=pApp->Input_GetKeyName(nVKey);

	pApp->Release();
	return lpcszRes;
}

int Lua_Input_GetMousePos(LuaPlus::LuaState *lua)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	float x, y;

	pApp->Input_GetMousePos(&x, &y);
	pApp->Release();

	lua->PushNumber(x);
	lua->PushNumber(y);
	return 2;
}

void Input_SetMousePos(float x, float y)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Input_SetMousePos(x, y);
	pApp->Release();
}

int Input_GetMouseWheel()
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	int nRes=pApp->Input_GetMouseWheel();

	pApp->Release();
	return nRes;
}

bool Input_IsMouseOver()
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	bool bRes=(pApp->Input_IsMouseOver() ? true : false);

	pApp->Release();
	return bRes;
}

RUGE::HAUDIO Effect_Load(LPCSTR lpcszPath)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	RUGE::HAUDIO hAudio=pApp->Effect_Load(lpcszPath);

	pApp->Release();
	return hAudio;
}

int Lua_Effect_Play(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::HAUDIO hAudio=NULL;
	int nVolume=100, nPan=0;
	float fPitch=1.0f;
	BOOL bLoop=FALSE;

	switch (args.Count())
	{
	case 5:
		if (args[5].IsBoolean()) bLoop=(BOOL)args[5].GetBoolean();
	case 4:
		if (args[4].IsNumber()) fPitch=args[4].GetFloat();
	case 3:
		if (args[3].IsInteger()) nPan=args[3].GetInteger();
	case 2:
		if (args[2].IsInteger()) nVolume=args[2].GetInteger();
	case 1:
		if (args[1].IsLightUserData()) hAudio=args[1].GetLightUserData();
		break;
	}

	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	RUGE::HCHANNEL hChannel=pApp->Effect_Play(hAudio, nVolume, nPan, fPitch, bLoop);

	pApp->Release();

	lua->PushLightUserData(hChannel);
	return 1;
}

RUGE::HAUDIO Music_Load(LPCSTR lpcszPath)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	RUGE::HAUDIO hAudio=pApp->Music_Load(lpcszPath);

	pApp->Release();
	return hAudio;
}

int Lua_Music_Play(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::HAUDIO hAudio;
	int nVolume=100;
	float fStart=0.0f;
	BOOL bLoop=TRUE;

	switch (args.Count())
	{
	case 4:
		if (args[4].IsBoolean()) bLoop=(BOOL)args[4].GetBoolean();
	case 3:
		if (args[3].IsNumber()) fStart=args[3].GetFloat();
	case 2:
		if (args[2].IsInteger()) nVolume=args[2].GetInteger();
	case 1:
		if (args[1].IsLightUserData()) hAudio=args[1].GetLightUserData();
		break;
	}

	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	RUGE::HCHANNEL hChannel=pApp->Music_Play(hAudio, nVolume, fStart, bLoop);

	pApp->Release();

	lua->PushLightUserData(hChannel);
	return 1;
}

float Audio_GetLength(RUGE::HAUDIO hAudio)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	float fRes=pApp->Audio_GetLength(hAudio);

	pApp->Release();
	return fRes;
}

void Audio_Free(RUGE::HAUDIO hAudio)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Audio_Free(hAudio);
	pApp->Release();
}

void Channel_Pause(RUGE::HCHANNEL hChannel)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Channel_Pause(hChannel);
	pApp->Release();
}

void Channel_Resume(RUGE::HCHANNEL hChannel)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Channel_Resume(hChannel);
	pApp->Release();
}

void Channel_Stop(RUGE::HCHANNEL hChannel)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Channel_Stop(hChannel);
	pApp->Release();
}

bool Channel_IsPlaying(RUGE::HCHANNEL hChannel)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	bool bRes=(pApp->Channel_IsPlaying(hChannel) ? true : false);
	
	pApp->Release();
	return bRes;
}

void Channel_SetVolume(RUGE::HCHANNEL hChannel, int nVolume)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Channel_SetVolume(hChannel, nVolume);
	pApp->Release();
}

void Channel_SetPan(RUGE::HCHANNEL hChannel, int nPan)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Channel_SetPan(hChannel, nPan);
	pApp->Release();
}

void Channel_SetPitch(RUGE::HCHANNEL hChannel, float fPitch)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Channel_SetPitch(hChannel, fPitch);
	pApp->Release();
}

void Channel_SetPosition(RUGE::HCHANNEL hChannel, float fPos)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Channel_SetPosition(hChannel, fPos);
	pApp->Release();
}

int Channel_GetVolume(RUGE::HCHANNEL hChannel)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	int nRes=pApp->Channel_GetVolume(hChannel);
	
	pApp->Release();
	return nRes;
}

int Channel_GetPan(RUGE::HCHANNEL hChannel)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	int nRes=pApp->Channel_GetPan(hChannel);
	
	pApp->Release();
	return nRes;
}

float Channel_GetPosition(RUGE::HCHANNEL hChannel)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	float fRes=pApp->Channel_GetPosition(hChannel);
	
	pApp->Release();
	return fRes;
}

void Random_Seed(int nSeed)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();

	pApp->Random_Seed(nSeed);
	pApp->Release();
}

int Random_Int(int nMax, int nMin)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	int nRes=pApp->Random_Int(nMax, nMin);
	
	pApp->Release();
	return nRes;
}

float Random_Float(float fMax, float fMin)
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	float fRes=pApp->Random_Float(fMax, fMin);
	
	pApp->Release();
	return fRes;
}

float Timer_GetTime()
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	float fRes=pApp->Timer_GetTime();
	
	pApp->Release();
	return fRes;
}

float Timer_GetDelta()
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	float fRes=pApp->Timer_GetDelta();
	
	pApp->Release();
	return fRes;
}

int Timer_GetFPS()
{
	RUGE::PAPPLICATION pApp=RUGE::GetRUGE();
	int nRes=pApp->Timer_GetFPS();
	
	pApp->Release();
	return nRes;
}

int HW_ARGB(int a, int r, int g, int b)
{
	return ARGB(a, r, g, b);
}

int HW_XRGB(int r, int g, int b)
{
	return XRGB(r, g, b);
}

int HW_GETA(int nColor)
{
	return GETA(nColor);
}

int HW_GETR(int nColor)
{
	return GETR(nColor);
}

int HW_GETG(int nColor)
{
	return GETG(nColor);
}

int HW_GETB(int nColor)
{
	return GETB(nColor);
}

int HW_SETA(int nColor, int a)
{
	return SETA(nColor, a);
}

int HW_SETR(int nColor, int r)
{
	return SETR(nColor, r);
}

int HW_SETG(int nColor, int g)
{
	return SETG(nColor, g);
}

int HW_SETB(int nColor, int b)
{
	return SETB(nColor, b);
}

int Lua_Bit_and(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	int nRes=0;
	
	if (args.Count()>1)
	{
		if (args[1].IsInteger()) nRes=args[1].GetInteger();
		for (int i=2; i<=args.Count(); i++)
		{
			if (args[i].IsInteger()) nRes&=args[i].GetInteger();
		}
	}

	lua->PushInteger(nRes);
	return 1;
}

int Lua_Bit_or(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	int nRes=0;
	
	if (args.Count()>1)
	{
		if (args[1].IsInteger()) nRes=args[1].GetInteger();
		for (int i=2; i<=args.Count(); i++)
		{
			if (args[i].IsInteger()) nRes|=args[i].GetInteger();
		}
	}

	lua->PushInteger(nRes);
	return 1;
}

int Bit_not(int x)
{
	return ~x;
}

int Lua_Bit_xor(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	int nRes=0;
	
	if (args.Count()>1)
	{
		if (args[1].IsInteger()) nRes=args[1].GetInteger();
		for (int i=2; i<=args.Count(); i++)
		{
			if (args[i].IsInteger()) nRes^=args[i].GetInteger();
		}
	}

	lua->PushInteger(nRes);
	return 1;
}

int Bit_lsh(int x, int n)
{
	return x<<n;
}

int Bit_rsh(int x, int n)
{
	return x>>n;
}
