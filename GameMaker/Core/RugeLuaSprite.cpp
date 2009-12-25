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
#include "RugeLuaSprite.h"
#include <Sprite.h>

int Lua_Sprite_Create(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::HTEXTURE hTex=NULL;
	float x=0, y=0, w=0, h=0;
	RUGE::CSprite *pSrc=NULL, *pRes=NULL;

	switch (args.Count())
	{
	case 1:
		if (args[1].IsLightUserData()) pSrc=(RUGE::CSprite*)args[1].GetLightUserData();
		pRes=new RUGE::CSprite(*pSrc);
		break;
	case 5:
		if (args[1].IsLightUserData()) hTex=args[1].GetLightUserData();
		if (args[2].IsNumber()) x=args[2].GetFloat();
		if (args[3].IsNumber()) y=args[3].GetFloat();
		if (args[4].IsNumber()) w=args[4].GetFloat();
		if (args[5].IsNumber()) h=args[5].GetFloat();
		pRes=new RUGE::CSprite(hTex, x, y, w, h);
		break;
	}

	lua->PushLightUserData(pRes);
	return 1;
}

void Sprite_Free(HSPRITE hSpr)
{
	delete (RUGE::CSprite*)hSpr;
}

HSPRITE Sprite_Assign(HSPRITE hDst, HSPRITE hSrc)
{
	*(RUGE::CSprite*)hDst=*(RUGE::CSprite*)hSrc;
	return hDst;
}

int Lua_Sprite_Flip(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CSprite *pSpr=NULL;
	bool bx=false, by=false, bHotSpot=false;

	switch (args.Count())
	{
	case 4:
		if (args[4].IsBoolean()) bHotSpot=args[4].GetBoolean();
	case 3:
		if (args[1].IsLightUserData()) pSpr=(RUGE::CSprite*)args[1].GetLightUserData();
		if (args[2].IsBoolean()) bx=args[2].GetBoolean();
		if (args[3].IsBoolean()) by=args[3].GetBoolean();
		break;
	}
	pSpr->Flip((BOOL)bx, (BOOL)by, (BOOL)bHotSpot);
	return 0;
}

void Sprite_Render(HSPRITE hSpr, float x, float y)
{
	((RUGE::CSprite*)hSpr)->Render(x, y);
}

int Lua_Sprite_RenderEx(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CSprite *pSpr=NULL;
	float x=0.0f, y=0.0f, fRot=0.0f, fHScale=1.0f, fVScale=0.0f;

	switch (args.Count())
	{
	case 6:
		if (args[6].IsNumber()) fVScale=args[6].GetFloat();
	case 5:
		if (args[5].IsNumber()) fHScale=args[5].GetFloat();
	case 4:
		if (args[4].IsNumber()) fRot=args[4].GetFloat();
	case 3:
		if (args[1].IsLightUserData()) pSpr=(RUGE::CSprite*)args[1].GetLightUserData();
		if (args[2].IsNumber()) x=args[2].GetFloat();
		if (args[3].IsNumber()) y=args[3].GetFloat();
		break;
	}
	pSpr->RenderEx(x, y, fRot, fHScale, fVScale);
	return 0;
}

void Sprite_RenderStretch(HSPRITE hSpr, float x1, float y1, float x2, float y2)
{
	((RUGE::CSprite*)hSpr)->RenderStretch(x1, y1, x2, y2);
}

int Lua_Sprite_Render4V(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CSprite *pSpr=NULL;
	float x0=0, y0=0, x1=0, y1=0, x2=0, y2=0, x3=0, y3=0;

	if (args.Count()==9)
	{
		if (args[1].IsLightUserData()) pSpr=(RUGE::CSprite*)args[1].GetLightUserData();
		if (args[2].IsNumber()) x0=args[2].GetFloat();
		if (args[3].IsNumber()) y0=args[3].GetFloat();
		if (args[4].IsNumber()) x1=args[4].GetFloat();
		if (args[5].IsNumber()) y1=args[5].GetFloat();
		if (args[6].IsNumber()) x2=args[6].GetFloat();
		if (args[7].IsNumber()) y2=args[7].GetFloat();
		if (args[8].IsNumber()) x3=args[8].GetFloat();
		if (args[9].IsNumber()) y3=args[9].GetFloat();
	}
	pSpr->Render4V(x0, y0, x1, y1, x2, y2, x3, y3);
	return 0;
}

void Sprite_SetTexture(HSPRITE hSpr, RUGE::HTEXTURE hTex)
{
	((RUGE::CSprite*)hSpr)->SetTexture(hTex);
}

void Sprite_SetTextureRect(HSPRITE hSpr, float x, float y, float w, float h)
{
	((RUGE::CSprite*)hSpr)->SetTextureRect(x, y, w, h);
}

int Lua_Sprite_SetColor(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CSprite *pSpr=NULL;
	int nColor=-1, nIndex=-1;

	switch (args.Count())
	{
	case 3:
		if (args[3].IsInteger()) nIndex=args[3].GetInteger();
	case 2:
		if (args[1].IsLightUserData()) pSpr=(RUGE::CSprite*)args[1].GetLightUserData();
		if (args[2].IsInteger()) nColor=args[2].GetInteger();
		break;
	}
	pSpr->SetColor(nColor, nIndex);
	return 0;
}

int Lua_Sprite_SetZ(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CSprite *pSpr=NULL;
	float z=0.5f;
	int nIndex=-1;

	switch (args.Count())
	{
	case 3:
		if (args[3].IsInteger()) nIndex=args[3].GetInteger();
	case 2:
		if (args[1].IsLightUserData()) pSpr=(RUGE::CSprite*)args[1].GetLightUserData();
		if (args[2].IsNumber()) z=args[2].GetFloat();
		break;
	}
	pSpr->SetZ(z, nIndex);
	return 0;
}

void Sprite_SetBlendMode(HSPRITE hSpr, int nBlend)
{
	((RUGE::CSprite*)hSpr)->SetBlendMode(nBlend);
}

void Sprite_SetHotSpot(HSPRITE hSpr, float x, float y)
{
	((RUGE::CSprite*)hSpr)->SetHotSpot(x, y);
}

RUGE::HTEXTURE Sprite_GetTexture(HSPRITE hSpr)
{
	return ((RUGE::CSprite*)hSpr)->GetTexture();
}

int Lua_Sprite_GetTextureRect(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CSprite *pSpr=NULL;
	float x=0, y=0, w=0, h=0;

	if (args.Count()==1 && args[1].IsLightUserData()) pSpr=(RUGE::CSprite*)args[1].GetLightUserData();
	pSpr->GetTextureRect(&x, &y, &w, &h);

	lua->PushNumber(x);
	lua->PushNumber(y);
	lua->PushNumber(w);
	lua->PushNumber(h);
	return 4;
}

int Lua_Sprite_GetColor(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CSprite *pSpr=NULL;
	int nIndex=0;

	switch (args.Count())
	{
	case 2:
		if (args[2].IsInteger()) nIndex=args[2].GetInteger();
	case 1:
		if (args[1].IsLightUserData()) pSpr=(RUGE::CSprite*)args[1].GetLightUserData();
		break;
	}

	lua->PushInteger(pSpr->GetColor(nIndex));
	return 1;
}

int Lua_Sprite_GetZ(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CSprite *pSpr=NULL;
	int nIndex=0;

	switch (args.Count())
	{
	case 2:
		if (args[2].IsInteger()) nIndex=args[2].GetInteger();
	case 1:
		if (args[1].IsLightUserData()) pSpr=(RUGE::CSprite*)args[1].GetLightUserData();
		break;
	}

	lua->PushNumber(pSpr->GetZ(nIndex));
	return 1;
}

int Sprite_GetBlendMode(HSPRITE hSpr)
{
	return ((RUGE::CSprite*)hSpr)->GetBlendMode();
}

int Lua_Sprite_GetHotSpot(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CSprite *pSpr=NULL;
	float x=0, y=0;

	if (args.Count()==1 && args[1].IsLightUserData()) pSpr=(RUGE::CSprite*)args[1].GetLightUserData();
	pSpr->GetHotSpot(&x, &y);

	lua->PushNumber(x);
	lua->PushNumber(y);
	return 2;
}

float Sprite_GetWidth(HSPRITE hSpr)
{
	return ((RUGE::CSprite*)hSpr)->GetWidth();
}

float Sprite_GetHeight(HSPRITE hSpr)
{
	return ((RUGE::CSprite*)hSpr)->GetHeight();
}

int Lua_Sprite_GetBoundingBox(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CSprite *pSpr=NULL;
	float x=0, y=0, fRot=0, fHScale=0, fVScale=0;
	RUGE::CRect rect;

	switch (args.Count())
	{
	case 3:
		if (args[1].IsLightUserData()) pSpr=(RUGE::CSprite*)args[1].GetLightUserData();
		if (args[2].IsNumber()) x=args[2].GetFloat();
		if (args[3].IsNumber()) y=args[3].GetFloat();
		pSpr->GetBoundingBox(x, y, &rect);
		break;
	case 6:
		if (args[1].IsLightUserData()) pSpr=(RUGE::CSprite*)args[1].GetLightUserData();
		if (args[2].IsNumber()) x=args[2].GetFloat();
		if (args[3].IsNumber()) y=args[3].GetFloat();
		if (args[4].IsNumber()) fRot=args[4].GetFloat();
		if (args[5].IsNumber()) fHScale=args[5].GetFloat();
		if (args[6].IsNumber()) fVScale=args[6].GetFloat();
		pSpr->GetBoundingBox(x, y, fRot, fHScale, fVScale, &rect);
		break;
	}

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("Left", rect.x1);
	table.SetNumber("Top", rect.y1);
	table.SetNumber("Right", rect.x2);
	table.SetNumber("Bottom", rect.y2);
	return 1;
}
