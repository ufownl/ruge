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

int Lua_Color_SetColor(LuaPlus::LuaState *lua);
int Lua_Color_GetColor(LuaPlus::LuaState *lua);
int Lua_Color_Clamp(LuaPlus::LuaState *lua);

int Lua_Color_Add(LuaPlus::LuaState *lua);
int Lua_Color_Sub(LuaPlus::LuaState *lua);
int Lua_Color_Mul(LuaPlus::LuaState *lua);
int Lua_Color_Div(LuaPlus::LuaState *lua);

int Lua_Color_Equal(LuaPlus::LuaState *lua);