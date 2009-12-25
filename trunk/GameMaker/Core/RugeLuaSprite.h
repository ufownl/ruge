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

#pragma once

#include "RugeLuaRect.h"

typedef HANDLE HSPRITE;

int Lua_Sprite_Create(LuaPlus::LuaState *lua);
void Sprite_Free(HSPRITE hSpr);

HSPRITE Sprite_Assign(HSPRITE hDst, HSPRITE hSrc);

int Lua_Sprite_Flip(LuaPlus::LuaState *lua);
void Sprite_Render(HSPRITE hSpr, float x, float y);
int Lua_Sprite_RenderEx(LuaPlus::LuaState *lua);
void Sprite_RenderStretch(HSPRITE hSpr, float x1, float y1, float x2, float y2);
int Lua_Sprite_Render4V(LuaPlus::LuaState *lua);

void Sprite_SetTexture(HSPRITE hSpr, RUGE::HTEXTURE hTex);
void Sprite_SetTextureRect(HSPRITE hSpr, float x, float y, float w, float h);
int Lua_Sprite_SetColor(LuaPlus::LuaState *lua);
int Lua_Sprite_SetZ(LuaPlus::LuaState *lua);
void Sprite_SetBlendMode(HSPRITE hSpr, int nBlend);
void Sprite_SetHotSpot(HSPRITE hSpr, float x, float y);

RUGE::HTEXTURE Sprite_GetTexture(HSPRITE hSpr);
int Lua_Sprite_GetTextureRect(LuaPlus::LuaState *lua);
int Lua_Sprite_GetColor(LuaPlus::LuaState *lua);
int Lua_Sprite_GetZ(LuaPlus::LuaState *lua);
int Sprite_GetBlendMode(HSPRITE hSpr);
int Lua_Sprite_GetHotSpot(LuaPlus::LuaState *lua);
float Sprite_GetWidth(HSPRITE hSpr);
float Sprite_GetHeight(HSPRITE hSpr);
int Lua_Sprite_GetBoundingBox(LuaPlus::LuaState *lua);
