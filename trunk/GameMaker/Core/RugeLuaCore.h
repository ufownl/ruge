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

#define APP_CAPTION		(100+RUGE::APP_CAPTION)
#define APP_ICON		(100+RUGE::APP_ICON)
#define APP_INIFILE		(100+RUGE::APP_INIFILE)

#define APP_WIDTH		(200+RUGE::APP_WIDTH)
#define APP_HEIGHT		(200+RUGE::APP_HEIGHT)
#define APP_MAXCHANNELS	(200+RUGE::APP_MAXCHANNELS)

#define APP_WINDOWED	(300+RUGE::APP_WINDOWED)
#define APP_DEVICELOST	(300+RUGE::APP_DEVICELOST)
#define APP_ACTIVE		(300+RUGE::APP_ACTIVE)
#define APP_HIDECURSOR	(300+RUGE::APP_HIDECURSOR)
#define APP_NOTSUSPEND	(300+RUGE::APP_NOTSUSPEND)

#define APP_VSYNC		(400+RUGE::APP_VSYNC)
#define APP_MAGFILTER	(400+RUGE::APP_MAGFILTER)
#define APP_MINFILTER	(400+RUGE::APP_MINFILTER)

#define APP_DEVICE		(500+RUGE::APP_DEVICE)
#define APP_MAINWINDOW	(500+RUGE::APP_MAINWINDOW)

int Lua_System_SetState(LuaPlus::LuaState *lua);
int Lua_System_GetState(LuaPlus::LuaState *lua);

void Ini_SetInt(LPCSTR lpcszSection, LPCSTR lpcszName, int nVal);
void Ini_SetFloat(LPCSTR lpcszSection, LPCSTR lpcszName, float fVal);
void Ini_SetString(LPCSTR lpcszSection, LPCSTR lpcszName, LPCSTR lpcszVal);

int Lua_Ini_GetInt(LuaPlus::LuaState *lua);
int Lua_Ini_GetFloat(LuaPlus::LuaState *lua);
int Lua_Ini_GetString(LuaPlus::LuaState *lua);

void Gfx_BeginTarget(RUGE::HTARGET hTarg);
void Gfx_EndTarget();
int Lua_Gfx_Clear(LuaPlus::LuaState *lua);
int Lua_Gfx_RenderLine(LuaPlus::LuaState *lua);
int Lua_Gfx_RenderTriangle(LuaPlus::LuaState *lua);
int Lua_Gfx_RenderQuad(LuaPlus::LuaState *lua);
int Lua_Gfx_Shotsnap(LuaPlus::LuaState *lua);

RUGE::HTEXTURE Texture_Create(int nWidth, int nHeight);
RUGE::HTEXTURE Texture_Load(LPCSTR lpcszPath);
void Texture_Free(RUGE::HTEXTURE hTex);
int Texture_GetWidth(RUGE::HTEXTURE hTex);
int Texture_GetHeight(RUGE::HTEXTURE hTex);

RUGE::HTARGET Target_Create(int nWidth, int nHeight);
void Target_Free(RUGE::HTARGET hTarg);
RUGE::HTEXTURE Target_GetTexture(RUGE::HTARGET hTarg);

RUGE::HFONT Font_Create(int nHeight, int nWidth, int nWeight, bool bItalic, LPCSTR lpcszFont);
void Font_Free(RUGE::HFONT hFont);
int Lua_Font_DrawText(LuaPlus::LuaState *lua);

bool Input_KeyDown(int nVKey);
bool Input_KeyPressed(int nVKey);
bool Input_KeyUp(int nVKey);
int Input_GetKey();
int Input_GetChar();
LPCSTR Input_GetKeyName(int nVKey);

int Lua_Input_GetMousePos(LuaPlus::LuaState *lua);
void Input_SetMousePos(float x, float y);
int Input_GetMouseWheel();
bool Input_IsMouseOver();

RUGE::HAUDIO Effect_Load(LPCSTR lpcszPath);
int Lua_Effect_Play(LuaPlus::LuaState *lua);

RUGE::HAUDIO Music_Load(LPCSTR lpcszPath);
int Lua_Music_Play(LuaPlus::LuaState *lua);

float Audio_GetLength(RUGE::HAUDIO hAudio);
void Audio_Free(RUGE::HAUDIO hAudio);

void Channel_Pause(RUGE::HCHANNEL hChannel);
void Channel_Resume(RUGE::HCHANNEL hChannel);
void Channel_Stop(RUGE::HCHANNEL hChannel);
bool Channel_IsPlaying(RUGE::HCHANNEL hChannel);

void Channel_SetVolume(RUGE::HCHANNEL hChannel, int nVolume);
void Channel_SetPan(RUGE::HCHANNEL hChannel, int nPan);
void Channel_SetPitch(RUGE::HCHANNEL hChannel, float fPitch);
void Channel_SetPosition(RUGE::HCHANNEL hChannel, float fPos);

int Channel_GetVolume(RUGE::HCHANNEL hChannel);
int Channel_GetPan(RUGE::HCHANNEL hChannel);
float Channel_GetPosition(RUGE::HCHANNEL hChannel);

void Random_Seed(int nSeed);
int Random_Int(int nMax, int nMin);
float Random_Float(float fMax, float fMin);

float Timer_GetTime();
float Timer_GetDelta();
int Timer_GetFPS();

int HW_ARGB(int a, int r, int g, int b);
int HW_XRGB(int r, int g, int b);
int HW_GETA(int nColor);
int HW_GETR(int nColor);
int HW_GETG(int nColor);
int HW_GETB(int nColor);
int HW_SETA(int nColor, int a);
int HW_SETR(int nColor, int r);
int HW_SETG(int nColor, int g);
int HW_SETB(int nColor, int b);

int Lua_Bit_and(LuaPlus::LuaState *lua);
int Lua_Bit_or(LuaPlus::LuaState *lua);
int Bit_not(int x);
int Lua_Bit_xor(LuaPlus::LuaState *lua);
int Bit_lsh(int x, int n);
int Bit_rsh(int x, int n);
