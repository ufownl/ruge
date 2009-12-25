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
#include "Register.h"
#include "RugeLuaCore.h"
#include "RugeLuaParticleSystem.h"
#include "RugeLuaDistortionMesh.h"
#include "RugeLuaGUI.h"
#include "RugeLuaAnimation.h"
#include "RugeLuaSceneManager.h"

void RegisterAPI(LuaPlus::LuaState *lua)
{
	lua->GetGlobals().SetLightUserData("NULL", NULL);

	lua->GetGlobals().SetNumber("M_PI", M_PI);
	lua->GetGlobals().SetNumber("M_PI_2", M_PI_2);
	lua->GetGlobals().SetNumber("M_PI_4", M_PI_4);
	lua->GetGlobals().SetNumber("M_1_PI", M_1_PI);
	lua->GetGlobals().SetNumber("M_2_PI", M_2_PI);

	lua->GetGlobals().SetInteger("APP_CAPTION", APP_CAPTION);
	lua->GetGlobals().SetInteger("APP_ICON", APP_ICON);
	lua->GetGlobals().SetInteger("APP_INIFILE", APP_INIFILE);

	lua->GetGlobals().SetInteger("APP_WIDTH", APP_WIDTH);
	lua->GetGlobals().SetInteger("APP_HEIGHT", APP_HEIGHT);
	lua->GetGlobals().SetInteger("APP_MAXCHANNELS", APP_MAXCHANNELS);

	lua->GetGlobals().SetInteger("APP_WINDOWED", APP_WINDOWED);
	lua->GetGlobals().SetInteger("APP_DEVICELOST", APP_DEVICELOST);
	lua->GetGlobals().SetInteger("APP_ACTIVE", APP_ACTIVE);
	lua->GetGlobals().SetInteger("APP_HIDECURSOR", APP_HIDECURSOR);
	lua->GetGlobals().SetInteger("APP_NOTSUSPEND", APP_NOTSUSPEND);

	lua->GetGlobals().SetInteger("APP_VSYNC", APP_VSYNC);
	lua->GetGlobals().SetInteger("APP_MAGFILTER", APP_MAGFILTER);
	lua->GetGlobals().SetInteger("APP_MINFILTER", APP_MINFILTER);

	lua->GetGlobals().SetInteger("VSYNC_DEFAULT", VSYNC_DEFAULT);
	lua->GetGlobals().SetInteger("VSYNC_ONE", VSYNC_ONE);
	lua->GetGlobals().SetInteger("VSYNC_TWO", VSYNC_TWO);
	lua->GetGlobals().SetInteger("VSYNC_THREE", VSYNC_THREE);
	lua->GetGlobals().SetInteger("VSYNC_FOUR", VSYNC_FOUR);
	lua->GetGlobals().SetInteger("VSYNC_IMMEDIATE", VSYNC_IMMEDIATE);

	lua->GetGlobals().SetInteger("TEXF_NEAREST", TEXF_NEAREST);
	lua->GetGlobals().SetInteger("TEXF_LINEAR", TEXF_LINEAR);

	lua->GetGlobals().SetInteger("APP_DEVICE", APP_DEVICE);
	lua->GetGlobals().SetInteger("APP_MAINWINDOW", APP_MAINWINDOW);

	lua->GetGlobals().SetInteger("BLEND_COLORADD", BLEND_COLORADD);
	lua->GetGlobals().SetInteger("BLEND_COLORMUL", BLEND_COLORMUL);
	lua->GetGlobals().SetInteger("BLEND_ALPHABLEND", BLEND_ALPHABLEND);
	lua->GetGlobals().SetInteger("BLEND_ALPHAADD", BLEND_ALPHAADD);
	lua->GetGlobals().SetInteger("BLEND_ZWRITE", BLEND_ZWRITE);
	lua->GetGlobals().SetInteger("BLEND_NOZWRITE", BLEND_NOZWRITE);
	lua->GetGlobals().SetInteger("BLEND_DEFAULT", BLEND_DEFAULT);

	lua->GetGlobals().SetInteger("IFF_BMP", IFF_BMP);
	lua->GetGlobals().SetInteger("IFF_JPG", IFF_JPG);
	lua->GetGlobals().SetInteger("IFF_TGA", IFF_TGA);
	lua->GetGlobals().SetInteger("IFF_PNG", IFF_PNG);
	lua->GetGlobals().SetInteger("IFF_DDS", IFF_DDS);
	lua->GetGlobals().SetInteger("IFF_PPM", IFF_PPM);
	lua->GetGlobals().SetInteger("IFF_DIB", IFF_DIB);
	lua->GetGlobals().SetInteger("IFF_HDR", IFF_HDR);
	lua->GetGlobals().SetInteger("IFF_PFM", IFF_PFM);

	lua->GetGlobals().SetInteger("DT_TOP", DT_TOP);
	lua->GetGlobals().SetInteger("DT_LEFT", DT_LEFT);
	lua->GetGlobals().SetInteger("DT_CENTER", DT_CENTER);
	lua->GetGlobals().SetInteger("DT_RIGHT", DT_RIGHT);
	lua->GetGlobals().SetInteger("DT_VCENTER", DT_VCENTER);
	lua->GetGlobals().SetInteger("DT_BOTTOM", DT_BOTTOM);
	lua->GetGlobals().SetInteger("DT_WORDBREAK", DT_WORDBREAK);
	lua->GetGlobals().SetInteger("DT_SINGLELINE", DT_SINGLELINE);
	lua->GetGlobals().SetInteger("DT_EXPANDTABS", DT_EXPANDTABS);
	lua->GetGlobals().SetInteger("DT_TABSTOP", DT_TABSTOP);
	lua->GetGlobals().SetInteger("DT_NOCLIP", DT_NOCLIP);
	lua->GetGlobals().SetInteger("DT_EXTERNALLEADING", DT_EXTERNALLEADING);
	lua->GetGlobals().SetInteger("DT_CALCRECT", DT_CALCRECT);
	lua->GetGlobals().SetInteger("DT_NOPREFIX", DT_NOPREFIX);
	lua->GetGlobals().SetInteger("DT_INTERNAL", DT_INTERNAL);

	lua->GetGlobals().SetInteger("VK_LBUTTON", VK_LBUTTON);
	lua->GetGlobals().SetInteger("VK_RBUTTON", VK_RBUTTON);
	lua->GetGlobals().SetInteger("VK_CANCEL", VK_CANCEL);
	lua->GetGlobals().SetInteger("VK_MBUTTON", VK_MBUTTON);

	lua->GetGlobals().SetInteger("VK_BACK", VK_BACK);
	lua->GetGlobals().SetInteger("VK_TAB", VK_TAB);

	lua->GetGlobals().SetInteger("VK_CLEAR", VK_CLEAR);
	lua->GetGlobals().SetInteger("VK_RETURN", VK_RETURN);

	lua->GetGlobals().SetInteger("VK_SHIFT", VK_SHIFT);
	lua->GetGlobals().SetInteger("VK_CONTROL", VK_CONTROL);
	lua->GetGlobals().SetInteger("VK_MENU", VK_MENU);
	lua->GetGlobals().SetInteger("VK_PAUSE", VK_PAUSE);
	lua->GetGlobals().SetInteger("VK_CAPITAL", VK_CAPITAL);

	lua->GetGlobals().SetInteger("VK_KANA", VK_KANA);
	lua->GetGlobals().SetInteger("VK_HANGEUL", VK_HANGEUL);
	lua->GetGlobals().SetInteger("VK_HANGUL", VK_HANGUL);
	lua->GetGlobals().SetInteger("VK_JUNJA", VK_JUNJA);
	lua->GetGlobals().SetInteger("VK_FINAL", VK_FINAL);
	lua->GetGlobals().SetInteger("VK_HANJA", VK_HANJA);
	lua->GetGlobals().SetInteger("VK_KANJI", VK_KANJI);

	lua->GetGlobals().SetInteger("VK_ESCAPE", VK_ESCAPE);

	lua->GetGlobals().SetInteger("VK_CONVERT", VK_CONVERT);
	lua->GetGlobals().SetInteger("VK_NONCONVERT", VK_NONCONVERT);
	lua->GetGlobals().SetInteger("VK_ACCEPT", VK_ACCEPT);
	lua->GetGlobals().SetInteger("VK_MODECHANGE", VK_MODECHANGE);

	lua->GetGlobals().SetInteger("VK_SPACE", VK_SPACE);
	lua->GetGlobals().SetInteger("VK_PRIOR", VK_PRIOR);
	lua->GetGlobals().SetInteger("VK_NEXT", VK_NEXT);
	lua->GetGlobals().SetInteger("VK_END", VK_END);
	lua->GetGlobals().SetInteger("VK_HOME", VK_HOME);
	lua->GetGlobals().SetInteger("VK_LEFT", VK_LEFT);
	lua->GetGlobals().SetInteger("VK_UP", VK_UP);
	lua->GetGlobals().SetInteger("VK_RIGHT", VK_RIGHT);
	lua->GetGlobals().SetInteger("VK_DOWN", VK_DOWN);
	lua->GetGlobals().SetInteger("VK_SELECT", VK_SELECT);
	lua->GetGlobals().SetInteger("VK_PRINT", VK_PRINT);
	lua->GetGlobals().SetInteger("VK_EXECUTE", VK_EXECUTE);
	lua->GetGlobals().SetInteger("VK_SNAPSHOT", VK_SNAPSHOT);
	lua->GetGlobals().SetInteger("VK_INSERT", VK_INSERT);
	lua->GetGlobals().SetInteger("VK_DELETE", VK_DELETE);
	lua->GetGlobals().SetInteger("VK_HELP", VK_HELP);

	lua->GetGlobals().SetInteger("VK_LWIN", VK_LWIN);
	lua->GetGlobals().SetInteger("VK_RWIN", VK_RWIN);
	lua->GetGlobals().SetInteger("VK_APPS", VK_APPS);

	lua->GetGlobals().SetInteger("VK_SLEEP", VK_SLEEP);

	lua->GetGlobals().SetInteger("VK_NUMPAD0", VK_NUMPAD0);
	lua->GetGlobals().SetInteger("VK_NUMPAD1", VK_NUMPAD1);
	lua->GetGlobals().SetInteger("VK_NUMPAD2", VK_NUMPAD2);
	lua->GetGlobals().SetInteger("VK_NUMPAD3", VK_NUMPAD3);
	lua->GetGlobals().SetInteger("VK_NUMPAD4", VK_NUMPAD4);
	lua->GetGlobals().SetInteger("VK_NUMPAD5", VK_NUMPAD5);
	lua->GetGlobals().SetInteger("VK_NUMPAD6", VK_NUMPAD6);
	lua->GetGlobals().SetInteger("VK_NUMPAD7", VK_NUMPAD7);
	lua->GetGlobals().SetInteger("VK_NUMPAD8", VK_NUMPAD8);
	lua->GetGlobals().SetInteger("VK_NUMPAD9", VK_NUMPAD9);
	lua->GetGlobals().SetInteger("VK_MULTIPLY", VK_MULTIPLY);
	lua->GetGlobals().SetInteger("VK_ADD", VK_ADD);
	lua->GetGlobals().SetInteger("VK_SEPARATOR", VK_SEPARATOR);
	lua->GetGlobals().SetInteger("VK_SUBTRACT", VK_SUBTRACT);
	lua->GetGlobals().SetInteger("VK_DECIMAL", VK_DECIMAL);
	lua->GetGlobals().SetInteger("VK_DIVIDE", VK_DIVIDE);
	lua->GetGlobals().SetInteger("VK_F1", VK_F1);
	lua->GetGlobals().SetInteger("VK_F2", VK_F2);
	lua->GetGlobals().SetInteger("VK_F3", VK_F3);
	lua->GetGlobals().SetInteger("VK_F4", VK_F4);
	lua->GetGlobals().SetInteger("VK_F5", VK_F5);
	lua->GetGlobals().SetInteger("VK_F6", VK_F6);
	lua->GetGlobals().SetInteger("VK_F7", VK_F7);
	lua->GetGlobals().SetInteger("VK_F8", VK_F8);
	lua->GetGlobals().SetInteger("VK_F9", VK_F9);
	lua->GetGlobals().SetInteger("VK_F10", VK_F10);
	lua->GetGlobals().SetInteger("VK_F11", VK_F11);
	lua->GetGlobals().SetInteger("VK_F12", VK_F12);
	lua->GetGlobals().SetInteger("VK_F13", VK_F13);
	lua->GetGlobals().SetInteger("VK_F14", VK_F14);
	lua->GetGlobals().SetInteger("VK_F15", VK_F15);
	lua->GetGlobals().SetInteger("VK_F16", VK_F16);
	lua->GetGlobals().SetInteger("VK_F17", VK_F17);
	lua->GetGlobals().SetInteger("VK_F18", VK_F18);
	lua->GetGlobals().SetInteger("VK_F19", VK_F19);
	lua->GetGlobals().SetInteger("VK_F20", VK_F20);
	lua->GetGlobals().SetInteger("VK_F21", VK_F21);
	lua->GetGlobals().SetInteger("VK_F22", VK_F22);
	lua->GetGlobals().SetInteger("VK_F23", VK_F23);
	lua->GetGlobals().SetInteger("VK_F24", VK_F24);

	lua->GetGlobals().SetInteger("VK_NUMLOCK", VK_NUMLOCK);
	lua->GetGlobals().SetInteger("VK_SCROLL", VK_SCROLL);

	lua->GetGlobals().SetInteger("VK_LSHIFT", VK_LSHIFT);
	lua->GetGlobals().SetInteger("VK_RSHIFT", VK_RSHIFT);
	lua->GetGlobals().SetInteger("VK_LCONTROL", VK_LCONTROL);
	lua->GetGlobals().SetInteger("VK_RCONTROL", VK_RCONTROL);
	lua->GetGlobals().SetInteger("VK_LMENU", VK_LMENU);
	lua->GetGlobals().SetInteger("VK_RMENU", VK_RMENU);

	lua->GetGlobals().Register("System_SetState", Lua_System_SetState);
	lua->GetGlobals().Register("System_GetState", Lua_System_GetState);

	lua->GetGlobals().RegisterDirect("Ini_SetInt", Ini_SetInt);
	lua->GetGlobals().RegisterDirect("Ini_SetFloat", Ini_SetFloat);
	lua->GetGlobals().RegisterDirect("Ini_SetString", Ini_SetString);

	lua->GetGlobals().Register("Ini_GetInt", Lua_Ini_GetInt);
	lua->GetGlobals().Register("Ini_GetFloat", Lua_Ini_GetFloat);
	lua->GetGlobals().Register("Ini_GetString", Lua_Ini_GetString);

	lua->GetGlobals().RegisterDirect("Gfx_BeginTarget", Gfx_BeginTarget);
	lua->GetGlobals().RegisterDirect("Gfx_EndTarget", Gfx_EndTarget);
	lua->GetGlobals().Register("Gfx_Clear", Lua_Gfx_Clear);
	lua->GetGlobals().Register("Gfx_RenderLine", Lua_Gfx_RenderLine);
	lua->GetGlobals().Register("Gfx_RenderTriangle", Lua_Gfx_RenderTriangle);
	lua->GetGlobals().Register("Gfx_RenderQuad", Lua_Gfx_RenderQuad);
	lua->GetGlobals().Register("Gfx_Shotsnap", Lua_Gfx_Shotsnap);

	lua->GetGlobals().RegisterDirect("Texture_Create", Texture_Create);
	lua->GetGlobals().RegisterDirect("Texture_Load", Texture_Load);
	lua->GetGlobals().RegisterDirect("Texture_Free", Texture_Free);
	lua->GetGlobals().RegisterDirect("Texture_GetWidth", Texture_GetWidth);
	lua->GetGlobals().RegisterDirect("Texture_GetHeight", Texture_GetHeight);

	lua->GetGlobals().RegisterDirect("Target_Create", Target_Create);
	lua->GetGlobals().RegisterDirect("Target_Free", Target_Free);
	lua->GetGlobals().RegisterDirect("Target_GetTexture", Target_GetTexture);

	lua->GetGlobals().RegisterDirect("Font_Create", Font_Create);
	lua->GetGlobals().RegisterDirect("Font_Free", Font_Free);
	lua->GetGlobals().Register("Font_DrawText", Lua_Font_DrawText);

	lua->GetGlobals().RegisterDirect("Input_KeyDown", Input_KeyDown);
	lua->GetGlobals().RegisterDirect("Input_KeyPressed", Input_KeyPressed);
	lua->GetGlobals().RegisterDirect("Input_KeyUp", Input_KeyUp);
	lua->GetGlobals().RegisterDirect("Input_GetKey", Input_GetKey);
	lua->GetGlobals().RegisterDirect("Input_GetChar", Input_GetChar);
	lua->GetGlobals().RegisterDirect("Input_GetKeyName", Input_GetKeyName);

	lua->GetGlobals().Register("Input_GetMousePos", Lua_Input_GetMousePos);
	lua->GetGlobals().RegisterDirect("Input_SetMousePos", Input_SetMousePos);
	lua->GetGlobals().RegisterDirect("Input_GetMouseWheel", Input_GetMouseWheel);
	lua->GetGlobals().RegisterDirect("Input_IsMouseOver", Input_IsMouseOver);

	lua->GetGlobals().RegisterDirect("Effect_Load", Effect_Load);
	lua->GetGlobals().Register("Effect_Play", Lua_Effect_Play);

	lua->GetGlobals().RegisterDirect("Music_Load", Music_Load);
	lua->GetGlobals().Register("Music_Play", Lua_Music_Play);

	lua->GetGlobals().RegisterDirect("Audio_GetLength", Audio_GetLength);
	lua->GetGlobals().RegisterDirect("Audio_Free", Audio_Free);

	lua->GetGlobals().RegisterDirect("Channel_Pause", Channel_Pause);
	lua->GetGlobals().RegisterDirect("Channel_Resume", Channel_Resume);
	lua->GetGlobals().RegisterDirect("Channel_Stop", Channel_Stop);
	lua->GetGlobals().RegisterDirect("Channel_IsPlaying", Channel_IsPlaying);

	lua->GetGlobals().RegisterDirect("Channel_SetVolume", Channel_SetVolume);
	lua->GetGlobals().RegisterDirect("Channel_SetPan", Channel_SetPan);
	lua->GetGlobals().RegisterDirect("Channel_SetPitch", Channel_SetPitch);
	lua->GetGlobals().RegisterDirect("Channel_SetPosition", Channel_SetPosition);

	lua->GetGlobals().RegisterDirect("Channel_GetVolume", Channel_GetVolume);
	lua->GetGlobals().RegisterDirect("Channel_GetPan", Channel_GetPan);
	lua->GetGlobals().RegisterDirect("Channel_GetPosition", Channel_GetPosition);

	lua->GetGlobals().RegisterDirect("Random_Seed", Random_Seed);
	lua->GetGlobals().RegisterDirect("Random_Int", Random_Int);
	lua->GetGlobals().RegisterDirect("Random_Float", Random_Float);

	lua->GetGlobals().RegisterDirect("Timer_GetTime", Timer_GetTime);
	lua->GetGlobals().RegisterDirect("Timer_GetDelta", Timer_GetDelta);
	lua->GetGlobals().RegisterDirect("Timer_GetFPS", Timer_GetFPS);

	lua->GetGlobals().RegisterDirect("ARGB", HW_ARGB);
	lua->GetGlobals().RegisterDirect("XRGB", HW_XRGB);
	lua->GetGlobals().RegisterDirect("GETA", HW_GETA);
	lua->GetGlobals().RegisterDirect("GETR", HW_GETR);
	lua->GetGlobals().RegisterDirect("GETG", HW_GETG);
	lua->GetGlobals().RegisterDirect("GETB", HW_GETB);
	lua->GetGlobals().RegisterDirect("SETA", HW_SETA);
	lua->GetGlobals().RegisterDirect("SETR", HW_SETR);
	lua->GetGlobals().RegisterDirect("SETG", HW_SETG);
	lua->GetGlobals().RegisterDirect("SETB", HW_SETB);

	lua->GetGlobals().Register("Bit_and", Lua_Bit_and);
	lua->GetGlobals().Register("Bit_or", Lua_Bit_or);
	lua->GetGlobals().RegisterDirect("Bit_not", Bit_not);
	lua->GetGlobals().Register("Bit_xor", Lua_Bit_xor);
	lua->GetGlobals().RegisterDirect("Bit_lsh", Bit_lsh);
	lua->GetGlobals().RegisterDirect("Bit_rsh", Bit_rsh);

	lua->GetGlobals().Register("Rect_SetRadius", Lua_Rect_SetRadius);
	lua->GetGlobals().Register("Rect_Encapsulate", Lua_Rect_Encapsulate);
	lua->GetGlobals().Register("Rect_TestPoint", Lua_Rect_TestPoint);
	lua->GetGlobals().Register("Rect_Intersect", Lua_Rect_Intersect);

	lua->GetGlobals().Register("Sprite_Create", Lua_Sprite_Create);
	lua->GetGlobals().RegisterDirect("Sprite_Free", Sprite_Free);

	lua->GetGlobals().RegisterDirect("Sprite_Assign", Sprite_Assign);

	lua->GetGlobals().Register("Sprite_Flip", Lua_Sprite_Flip);
	lua->GetGlobals().RegisterDirect("Sprite_Render", Sprite_Render);
	lua->GetGlobals().Register("Sprite_RenderEx", Lua_Sprite_RenderEx);
	lua->GetGlobals().RegisterDirect("Sprite_RenderStretch", Sprite_RenderStretch);
	lua->GetGlobals().Register("Sprite_Render4V", Lua_Sprite_Render4V);

	lua->GetGlobals().RegisterDirect("Sprite_SetTexture", Sprite_SetTexture);
	lua->GetGlobals().RegisterDirect("Sprite_SetTextureRect", Sprite_SetTextureRect);
	lua->GetGlobals().Register("Sprite_SetColor", Lua_Sprite_SetColor);
	lua->GetGlobals().Register("Sprite_SetZ", Lua_Sprite_SetZ);
	lua->GetGlobals().RegisterDirect("Sprite_SetBlendMode", Sprite_SetBlendMode);
	lua->GetGlobals().RegisterDirect("Sprite_SetHotSpot", Sprite_SetHotSpot);

	lua->GetGlobals().RegisterDirect("Sprite_GetTexture", Sprite_GetTexture);
	lua->GetGlobals().Register("Sprite_GetTextureRect", Lua_Sprite_GetTextureRect);
	lua->GetGlobals().Register("Sprite_GetColor", Lua_Sprite_GetColor);
	lua->GetGlobals().Register("Sprite_GetZ", Lua_Sprite_GetZ);
	lua->GetGlobals().RegisterDirect("Sprite_GetBlendMode", Sprite_GetBlendMode);
	lua->GetGlobals().Register("Sprite_GetHotSpot", Lua_Sprite_GetHotSpot);
	lua->GetGlobals().RegisterDirect("Sprite_GetWidth", Sprite_GetWidth);
	lua->GetGlobals().RegisterDirect("Sprite_GetHeight", Sprite_GetHeight);
	lua->GetGlobals().Register("Sprite_GetBoundingBox", Lua_Sprite_GetBoundingBox);

	lua->GetGlobals().Register("Vector_Negative", Lua_Vector_Negative);
	lua->GetGlobals().Register("Vector_Sub", Lua_Vector_Sub);
	lua->GetGlobals().Register("Vector_Add", Lua_Vector_Add);

	lua->GetGlobals().Register("Vector_Div", Lua_Vector_Div);
	lua->GetGlobals().Register("Vector_Mul", Lua_Vector_Mul);

	lua->GetGlobals().Register("Vector_Angle", Lua_Vector_Angle);
	lua->GetGlobals().Register("Vector_Dot", Lua_Vector_Dot);

	lua->GetGlobals().Register("Vector_Equal", Lua_Vector_Equal);

	lua->GetGlobals().Register("Vector_Length", Lua_Vector_Length);
	lua->GetGlobals().Register("Vector_Clamp", Lua_Vector_Clamp);
	lua->GetGlobals().Register("Vector_Normalize", Lua_Vector_Normalize);
	lua->GetGlobals().Register("Vector_Rotate", Lua_Vector_Rotate);

	lua->GetGlobals().Register("Color_SetColor", Lua_Color_SetColor);
	lua->GetGlobals().Register("Color_GetColor", Lua_Color_GetColor);
	lua->GetGlobals().Register("Color_Clamp", Lua_Color_Clamp);

	lua->GetGlobals().Register("Color_Add", Lua_Color_Add);
	lua->GetGlobals().Register("Color_Sub", Lua_Color_Sub);
	lua->GetGlobals().Register("Color_Mul", Lua_Color_Mul);
	lua->GetGlobals().Register("Color_Div", Lua_Color_Div);

	lua->GetGlobals().Register("Color_Equal", Lua_Color_Equal);

	lua->GetGlobals().Register("ParticleSystem_Create", Lua_ParticleSystem_Create);
	lua->GetGlobals().RegisterDirect("ParticleSystem_Free", ParticleSystem_Free);

	lua->GetGlobals().RegisterDirect("ParticleSystem_Assign", ParticleSystem_Assign);

	lua->GetGlobals().RegisterDirect("ParticleSystem_Render", ParticleSystem_Render);
	lua->GetGlobals().RegisterDirect("ParticleSystem_Fire", ParticleSystem_Fire);
	lua->GetGlobals().RegisterDirect("ParticleSystem_FireAt", ParticleSystem_FireAt);
	lua->GetGlobals().Register("ParticleSystem_Stop", Lua_ParticleSystem_Stop);
	lua->GetGlobals().RegisterDirect("ParticleSystem_Update", ParticleSystem_Update);
	lua->GetGlobals().Register("ParticleSystem_MoveTo", Lua_ParticleSystem_MoveTo);
	lua->GetGlobals().RegisterDirect("ParticleSystem_Transpose", ParticleSystem_Transpose);
	lua->GetGlobals().RegisterDirect("ParticleSystem_SetScale", ParticleSystem_SetScale);
	lua->GetGlobals().RegisterDirect("ParticleSystem_TrackBoundingBox", ParticleSystem_TrackBoundingBox);

	lua->GetGlobals().RegisterDirect("ParticleSystem_GetParticlesAlive", ParticleSystem_GetParticlesAlive);
	lua->GetGlobals().RegisterDirect("ParticleSystem_GetAge", ParticleSystem_GetAge);
	lua->GetGlobals().Register("ParticleSystem_GetPosition", Lua_ParticleSystem_GetPosition);
	lua->GetGlobals().Register("ParticleSystem_GetTransposition", Lua_ParticleSystem_GetTransposition);
	lua->GetGlobals().RegisterDirect("ParticleSystemm_GetScale", ParticleSystemm_GetScale);
	lua->GetGlobals().Register("ParticleSystem_GetBoundingBox", Lua_ParticleSystem_GetBoundingBox);

	lua->GetGlobals().Register("ParticleSystem_SetInfo", Lua_ParticleSystem_SetInfo);
	lua->GetGlobals().Register("ParticleSystem_GetInfo", Lua_ParticleSystem_GetInfo);
	lua->GetGlobals().Register("ParticleSystem_SerializeInfo", Lua_ParticleSystem_SerializeInfo);

	lua->GetGlobals().SetInteger("DISP_NODE", DISP_NODE);
	lua->GetGlobals().SetInteger("DISP_CENTER", DISP_CENTER);
	lua->GetGlobals().SetInteger("DISP_TOPLEFT", DISP_TOPLEFT);

	lua->GetGlobals().Register("DistortionMesh_Create", Lua_DistortionMesh_Create);
	lua->GetGlobals().RegisterDirect("DistortionMesh_Free", DistortionMesh_Free);

	lua->GetGlobals().RegisterDirect("DistiortionMesh_Assign", DistiortionMesh_Assign);

	lua->GetGlobals().Register("DistortionMesh_Clear", Lua_DistortionMesh_Clear);
	lua->GetGlobals().RegisterDirect("DistortionMesh_Render", DistortionMesh_Render);

	lua->GetGlobals().RegisterDirect("DistortionMesh_SetTexture", DistortionMesh_SetTexture);
	lua->GetGlobals().RegisterDirect("DistortionMesh_SetTextureRect", DistortionMesh_SetTextureRect);
	lua->GetGlobals().RegisterDirect("DistortionMesh_SetBlendMode", DistortionMesh_SetBlendMode);
	lua->GetGlobals().RegisterDirect("DistortionMesh_SetZ", DistortionMesh_SetZ);
	lua->GetGlobals().RegisterDirect("DistortionMesh_SetColor", DistortionMesh_SetColor);
	lua->GetGlobals().RegisterDirect("DistortionMesh_SetDisplacement", DistortionMesh_SetDisplacement);

	lua->GetGlobals().RegisterDirect("DistortionMesh_GetTexture", DistortionMesh_GetTexture);
	lua->GetGlobals().Register("DistortionMesh_GetTextureRect", Lua_DistortionMesh_GetTextureRect);
	lua->GetGlobals().RegisterDirect("DistortionMesh_GetBlendMode", DistortionMesh_GetBlendMode);
	lua->GetGlobals().RegisterDirect("DistortionMesh_GetZ", DistortionMesh_GetZ);
	lua->GetGlobals().RegisterDirect("DistortionMesh_GetColor", DistortionMesh_GetColor);
	lua->GetGlobals().Register("DistortionMesh_GetDisplacement", Lua_DistortionMesh_GetDisplacement);
	lua->GetGlobals().RegisterDirect("DistortionMesh_GetRows", DistortionMesh_GetRows);
	lua->GetGlobals().RegisterDirect("DistortionMesh_GetCols", DistortionMesh_GetCols);

	lua->GetGlobals().Register("Control_Create", Lua_Control_Create);
	lua->GetGlobals().RegisterDirect("Control_Free", Control_Free);

	lua->GetGlobals().RegisterDirect("Control_SetStatic", Control_SetStatic);
	lua->GetGlobals().RegisterDirect("Control_SetVisible", Control_SetVisible);
	lua->GetGlobals().RegisterDirect("Control_SetEnabled", Control_SetEnabled);
	lua->GetGlobals().Register("Control_SetRect", Lua_Control_SetRect);
	lua->GetGlobals().RegisterDirect("Control_SetColor", Control_SetColor);
	lua->GetGlobals().Register("Control_SetAttribute", Lua_Control_SetAttribute);

	lua->GetGlobals().RegisterDirect("Control_GetGUI", Control_GetGUI);
	lua->GetGlobals().RegisterDirect("Control_GetID", Control_GetID);
	lua->GetGlobals().RegisterDirect("Control_GetStatic", Control_GetStatic);
	lua->GetGlobals().RegisterDirect("Control_GetVisible", Control_GetVisible);
	lua->GetGlobals().RegisterDirect("Control_GetEnabled", Control_GetEnabled);
	lua->GetGlobals().Register("Control_GetRect", Lua_Control_GetRect);
	lua->GetGlobals().RegisterDirect("Control_GetColor", Control_GetColor);
	lua->GetGlobals().Register("Control_GetAttribute", Lua_Control_GetAttribute);

	lua->GetGlobals().SetInteger("NAV_NONAVKEYS", NAV_NONAVKEYS);
	lua->GetGlobals().SetInteger("NAV_LEFTRIGHT", NAV_LEFTRIGHT);
	lua->GetGlobals().SetInteger("NAV_UPDOWN", NAV_UPDOWN);
	lua->GetGlobals().SetInteger("NAV_CYCLED", NAV_CYCLED);

	lua->GetGlobals().RegisterDirect("GUI_Create", GUI_Create);
	lua->GetGlobals().RegisterDirect("GUI_Free", GUI_Free);

	lua->GetGlobals().Register("GUI_AddCtrl", Lua_GUI_AddCtrl);
	lua->GetGlobals().RegisterDirect("GUI_DelCtrl", GUI_DelCtrl);
	lua->GetGlobals().RegisterDirect("GUI_GetCtrl", GUI_GetCtrl);
	lua->GetGlobals().RegisterDirect("GUI_MoveCtrl", GUI_MoveCtrl);
	lua->GetGlobals().Register("GUI_ShowCtrl", Lua_GUI_ShowCtrl);
	lua->GetGlobals().Register("GUI_EnableCtrl", Lua_GUI_EnableCtrl);

	lua->GetGlobals().RegisterDirect("GUI_SetNavMode", GUI_SetNavMode);
	lua->GetGlobals().RegisterDirect("GUI_SetCursor", GUI_SetCursor);
	lua->GetGlobals().RegisterDirect("GUI_SetColor", GUI_SetColor);
	lua->GetGlobals().RegisterDirect("GUI_SetFocus", GUI_SetFocus);
	lua->GetGlobals().RegisterDirect("GUI_GetFocus", GUI_GetFocus);

	lua->GetGlobals().RegisterDirect("GUI_Enter", GUI_Enter);
	lua->GetGlobals().RegisterDirect("GUI_Exit", GUI_Exit);
	lua->GetGlobals().RegisterDirect("GUI_Reset", GUI_Reset);
	lua->GetGlobals().RegisterDirect("GUI_Move", GUI_Move);

	lua->GetGlobals().RegisterDirect("GUI_Update", GUI_Update);
	lua->GetGlobals().RegisterDirect("GUI_Render", GUI_Render);

	lua->GetGlobals().SetInteger("ANIM_FWD", ANIM_FWD);
	lua->GetGlobals().SetInteger("ANIM_REV", ANIM_REV);
	lua->GetGlobals().SetInteger("ANIM_PINGPONG", ANIM_PINGPONG);
	lua->GetGlobals().SetInteger("ANIM_NOPINGPONG", ANIM_NOPINGPONG);
	lua->GetGlobals().SetInteger("ANIM_LOOP", ANIM_LOOP);
	lua->GetGlobals().SetInteger("ANIM_NOLOOP", ANIM_NOLOOP);
	lua->GetGlobals().SetInteger("ANIM_DEFAULT", ANIM_DEFAULT);

	lua->GetGlobals().RegisterDirect("Animation_Create", Animation_Create);
	lua->GetGlobals().RegisterDirect("Animation_Free", Animation_Free);

	lua->GetGlobals().RegisterDirect("Animation_Assign", Animation_Assign);

	lua->GetGlobals().RegisterDirect("Animation_Play", Animation_Play);
	lua->GetGlobals().RegisterDirect("Animation_Stop", Animation_Stop);
	lua->GetGlobals().RegisterDirect("Animation_Resume", Animation_Resume);
	lua->GetGlobals().RegisterDirect("Animation_Update", Animation_Update);
	lua->GetGlobals().RegisterDirect("Animation_IsPlaying", Animation_IsPlaying);

	lua->GetGlobals().RegisterDirect("Animation_SetMode", Animation_SetMode);
	lua->GetGlobals().RegisterDirect("Animation_SetSpeed", Animation_SetSpeed);
	lua->GetGlobals().RegisterDirect("Animation_SetFrame", Animation_SetFrame);
	lua->GetGlobals().RegisterDirect("Animation_SetFrames", Animation_SetFrames);

	lua->GetGlobals().RegisterDirect("Animation_GetMode", Animation_GetMode);
	lua->GetGlobals().RegisterDirect("Animation_GetSpeed", Animation_GetSpeed);
	lua->GetGlobals().RegisterDirect("Animation_GetFrame", Animation_GetFrame);
	lua->GetGlobals().RegisterDirect("Animation_GetFrames", Animation_GetFrames);

	lua->GetGlobals().Register("Animation_Flip", Lua_Sprite_Flip);
	lua->GetGlobals().RegisterDirect("Animation_Render", Sprite_Render);
	lua->GetGlobals().Register("Animation_RenderEx", Lua_Sprite_RenderEx);
	lua->GetGlobals().RegisterDirect("Animation_RenderStretch", Sprite_RenderStretch);
	lua->GetGlobals().Register("Animation_Render4V", Lua_Sprite_Render4V);

	lua->GetGlobals().RegisterDirect("Animation_SetTexture", Sprite_SetTexture);
	lua->GetGlobals().RegisterDirect("Animation_SetTextureRect", Sprite_SetTextureRect);
	lua->GetGlobals().Register("Animation_SetColor", Lua_Sprite_SetColor);
	lua->GetGlobals().Register("Animation_SetZ", Lua_Sprite_SetZ);
	lua->GetGlobals().RegisterDirect("Animation_SetBlendMode", Sprite_SetBlendMode);
	lua->GetGlobals().RegisterDirect("Animation_SetHotSpot", Sprite_SetHotSpot);

	lua->GetGlobals().RegisterDirect("Animation_GetTexture", Sprite_GetTexture);
	lua->GetGlobals().Register("Animation_GetTextureRect", Lua_Sprite_GetTextureRect);
	lua->GetGlobals().Register("Animation_GetColor", Lua_Sprite_GetColor);
	lua->GetGlobals().Register("Animation_GetZ", Lua_Sprite_GetZ);
	lua->GetGlobals().RegisterDirect("Animation_GetBlendMode", Sprite_GetBlendMode);
	lua->GetGlobals().Register("Animation_GetHotSpot", Lua_Sprite_GetHotSpot);
	lua->GetGlobals().RegisterDirect("Animation_GetWidth", Sprite_GetWidth);
	lua->GetGlobals().RegisterDirect("Animation_GetHeight", Sprite_GetHeight);
	lua->GetGlobals().Register("Animation_GetBoundingBox", Lua_Sprite_GetBoundingBox);

	lua->GetGlobals().Register("Button_Create", Lua_Button_Create);
	lua->GetGlobals().RegisterDirect("Button_Free", Button_Free);

	lua->GetGlobals().RegisterDirect("Button_SetColor", Button_SetColor);

	lua->GetGlobals().RegisterDirect("Button_SetMode", Button_SetMode);
	lua->GetGlobals().RegisterDirect("Button_SetState", Button_SetState);
	lua->GetGlobals().RegisterDirect("Button_GetState", Button_GetState);

	lua->GetGlobals().Register("Listbox_Create", Lua_Listbox_Create);
	lua->GetGlobals().RegisterDirect("Listbox_Free", Listbox_Free);

	lua->GetGlobals().RegisterDirect("Listbox_SetColor", Listbox_SetColor);

	lua->GetGlobals().RegisterDirect("Listbox_AddItem", Listbox_AddItem);
	lua->GetGlobals().RegisterDirect("Listbox_DelItem", Listbox_DelItem);

	lua->GetGlobals().RegisterDirect("Listbox_SetSelected", Listbox_SetSelected);
	lua->GetGlobals().RegisterDirect("Listbox_SetTop", Listbox_SetTop);
	lua->GetGlobals().RegisterDirect("Listbox_SetItemText", Listbox_SetItemText);

	lua->GetGlobals().RegisterDirect("Listbox_GetSelected", Listbox_GetSelected);
	lua->GetGlobals().RegisterDirect("Listbox_GetTop", Listbox_GetTop);
	lua->GetGlobals().RegisterDirect("Listbox_GetItemText", Listbox_GetItemText);
	lua->GetGlobals().RegisterDirect("Listbox_GetNumItems", Listbox_GetNumItems);
	lua->GetGlobals().RegisterDirect("Listbox_GetNumRows", Listbox_GetNumRows);

	lua->GetGlobals().RegisterDirect("Listbox_Clear", Listbox_Clear);

	lua->GetGlobals().SetInteger("SLIDER_BAR", SLIDER_BAR);
	lua->GetGlobals().SetInteger("SLIDER_BARRELATIVE", SLIDER_BARRELATIVE);
	lua->GetGlobals().SetInteger("SLIDER_SLIDER", SLIDER_SLIDER);

	lua->GetGlobals().Register("Slider_Create", Lua_Slider_Create);
	lua->GetGlobals().RegisterDirect("Slider_Free", Slider_Free);

	lua->GetGlobals().RegisterDirect("Slider_SetColor", Slider_SetColor);

	lua->GetGlobals().RegisterDirect("Slider_SetMode", Slider_SetMode);
	lua->GetGlobals().RegisterDirect("Slider_SetValue", Slider_SetValue);
	lua->GetGlobals().RegisterDirect("Slider_GetValue", Slider_GetValue);

	lua->GetGlobals().RegisterDirect("Text_Create", Text_Create);
	lua->GetGlobals().RegisterDirect("Text_Free", Text_Free);

	lua->GetGlobals().RegisterDirect("Text_SetColor", Text_SetColor);

	lua->GetGlobals().RegisterDirect("Text_SetMode", Text_SetMode);
	lua->GetGlobals().RegisterDirect("Text_SetText", Text_SetText);

	lua->GetGlobals().Register("Scene_Create", Lua_Scene_Create);
	lua->GetGlobals().RegisterDirect("Scene_Free", Scene_Free);

	lua->GetGlobals().Register("Scene_SetAttribute", Lua_Scene_SetAttribute);

	lua->GetGlobals().RegisterDirect("Scene_GetID", Scene_GetID);
	lua->GetGlobals().RegisterDirect("Scene_GetManager", Scene_GetManager);
	lua->GetGlobals().Register("Scene_GetAttribute", Lua_Scene_GetAttribute);

	lua->GetGlobals().RegisterDirect("SceneManager_Create", SceneManager_Create);
	lua->GetGlobals().RegisterDirect("SceneManager_Free", SceneManager_Free);

	lua->GetGlobals().Register("SceneManager_AddScene", Lua_SceneManager_AddScene);
	lua->GetGlobals().RegisterDirect("SceneManager_DelScene", SceneManager_DelScene);
	lua->GetGlobals().RegisterDirect("SceneManager_GetScene", SceneManager_GetScene);
	lua->GetGlobals().Register("SceneManager_Switch", Lua_SceneManager_Switch);

	lua->GetGlobals().RegisterDirect("SceneManager_Update", SceneManager_Update);
	lua->GetGlobals().RegisterDirect("SceneManager_Render", SceneManager_Render);
}