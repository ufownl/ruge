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

#define SLIDER_BAR			0
#define SLIDER_BARRELATIVE	1
#define SLIDER_SLIDER		2

typedef HANDLE HSLIDER;

int Lua_Slider_Create(LuaPlus::LuaState *lua);
void Slider_Free(HSLIDER hSlider);

void Slider_SetColor(HSLIDER hSlider, int nColor);

void Slider_SetMode(HSLIDER hSlider, float fMin, float fMax, int nMode);
void Slider_SetValue(HSLIDER hSlider, float fVal);
float Slider_GetValue(HSLIDER hSlider);
