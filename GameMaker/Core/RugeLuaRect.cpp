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
#include "RugeLuaRect.h"
#include <Rect.h>

int Lua_Rect_SetRadius(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x=0, y=0, r=0;

	if (args.Count()==3)
	{
		if (args[1].IsNumber()) x=args[1].GetFloat();
		if (args[2].IsNumber()) y=args[2].GetFloat();
		if (args[3].IsNumber()) r=args[3].GetFloat();
	}

	RUGE::CRect rect;

	rect.SetRadius(x, y, r);

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("Left", rect.x1);
	table.SetNumber("Top", rect.y1);
	table.SetNumber("Right", rect.x2);
	table.SetNumber("Bottom", rect.y2);
	return 1;
}

int Lua_Rect_Encapsulate(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x1=0, y1=0, x2=0, y2=0, x=0, y=0;

	if (args.Count()==3)
	{
		if (args[1].IsTable())
		{
			if (args[1]["Left"].IsNumber()) x1=args[1]["Left"].GetFloat();
			if (args[1]["Top"].IsNumber()) y1=args[1]["Top"].GetFloat();
			if (args[1]["Right"].IsNumber()) x2=args[1]["Right"].GetFloat();
			if (args[1]["Bottom"].IsNumber()) y2=args[1]["Bottom"].GetFloat();
		}
		if (args[2].IsNumber()) x=args[2].GetFloat();
		if (args[3].IsNumber()) y=args[3].GetFloat();
	}

	RUGE::CRect rect(x1, y1, x2, y2);

	rect.Encapsulate(x, y);

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("Left", rect.x1);
	table.SetNumber("Top", rect.y1);
	table.SetNumber("Right", rect.x2);
	table.SetNumber("Bottom", rect.y2);
	return 1;
}

int Lua_Rect_TestPoint(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x1=0, y1=0, x2=0, y2=0, x=0, y=0;

	if (args.Count()==3)
	{
		if (args[1].IsTable())
		{
			if (args[1]["Left"].IsNumber()) x1=args[1]["Left"].GetFloat();
			if (args[1]["Top"].IsNumber()) y1=args[1]["Top"].GetFloat();
			if (args[1]["Right"].IsNumber()) x2=args[1]["Right"].GetFloat();
			if (args[1]["Bottom"].IsNumber()) y2=args[1]["Bottom"].GetFloat();
		}
		if (args[2].IsNumber()) x=args[2].GetFloat();
		if (args[3].IsNumber()) y=args[3].GetFloat();
	}

	RUGE::CRect rect(x1, y1, x2, y2);

	lua->PushBoolean(rect.TestPoint(x, y) ? true : false);
	return 1;
}

int Lua_Rect_Intersect(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float fLeft1=0, fTop1=0, fRight1=0, fBottom1=0, fLeft2=0, fTop2=0, fRight2=0, fBottom2=0;

	if (args.Count()==2)
	{
		if (args[1].IsTable())
		{
			if (args[1]["Left"].IsNumber()) fLeft1=args[1]["Left"].GetFloat();
			if (args[1]["Top"].IsNumber()) fTop1=args[1]["Top"].GetFloat();
			if (args[1]["Right"].IsNumber()) fRight1=args[1]["Right"].GetFloat();
			if (args[1]["Bottom"].IsNumber()) fBottom1=args[1]["Bottom"].GetFloat();
		}
		if (args[2].IsTable())
		{
			if (args[2]["Left"].IsNumber()) fLeft2=args[2]["Left"].GetFloat();
			if (args[2]["Top"].IsNumber()) fTop2=args[2]["Top"].GetFloat();
			if (args[2]["Right"].IsNumber()) fRight2=args[2]["Right"].GetFloat();
			if (args[2]["Bottom"].IsNumber()) fBottom2=args[2]["Bottom"].GetFloat();
		}
	}

	RUGE::CRect rect1(fLeft1, fTop1, fRight1, fBottom1), rect2(fLeft2, fTop2, fRight2, fBottom2);

	lua->PushBoolean(rect1.Intersect(&rect2) ? true : false);
	return 1;
}