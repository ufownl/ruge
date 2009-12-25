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

int Lua_Vector_Negative(LuaPlus::LuaState *lua);
int Lua_Vector_Sub(LuaPlus::LuaState *lua);
int Lua_Vector_Add(LuaPlus::LuaState *lua);

int Lua_Vector_Div(LuaPlus::LuaState *lua);
int Lua_Vector_Mul(LuaPlus::LuaState *lua);

int Lua_Vector_Angle(LuaPlus::LuaState *lua);
int Lua_Vector_Dot(LuaPlus::LuaState *lua);

int Lua_Vector_Equal(LuaPlus::LuaState *lua);

int Lua_Vector_Length(LuaPlus::LuaState *lua);
int Lua_Vector_Clamp(LuaPlus::LuaState *lua);
int Lua_Vector_Normalize(LuaPlus::LuaState *lua);
int Lua_Vector_Rotate(LuaPlus::LuaState *lua);