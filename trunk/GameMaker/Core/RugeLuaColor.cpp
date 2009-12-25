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
#include "RugeLuaColor.h"
#include <Color.h>

int Lua_Color_SetColor(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	int nColor=0;

	if (args.Count()==1 && args[1].IsInteger()) nColor=args[1].GetInteger();

	RUGE::CColor col((DWORD)nColor);
	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("a", col.a);
	table.SetNumber("r", col.r);
	table.SetNumber("g", col.g);
	table.SetNumber("b", col.b);
	return 1;
}

int Lua_Color_GetColor(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float a=0, r=0, g=0, b=0;

	if (args.Count()==1 && args[1].IsTable())
	{
		if (args[1]["a"].IsNumber()) a=args[1]["a"].GetFloat();
		if (args[1]["r"].IsNumber()) r=args[1]["r"].GetFloat();
		if (args[1]["g"].IsNumber()) g=args[1]["g"].GetFloat();
		if (args[1]["b"].IsNumber()) b=args[1]["b"].GetFloat();
	}

	RUGE::CColor col(a, r, g, b);

	lua->PushInteger(col.GetColor());
	return 1;
}

int Lua_Color_Clamp(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float a=0, r=0, g=0, b=0;

	if (args.Count()==1 && args[1].IsTable())
	{
		if (args[1]["a"].IsNumber()) a=args[1]["a"].GetFloat();
		if (args[1]["r"].IsNumber()) r=args[1]["r"].GetFloat();
		if (args[1]["g"].IsNumber()) g=args[1]["g"].GetFloat();
		if (args[1]["b"].IsNumber()) b=args[1]["b"].GetFloat();
	}

	RUGE::CColor col(a, r, g, b);

	col.Clamp();

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("a", col.a);
	table.SetNumber("r", col.r);
	table.SetNumber("g", col.g);
	table.SetNumber("b", col.b);
	return 1;
}

int Lua_Color_Add(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float a[2]={0}, r[2]={0}, g[2]={0}, b[2]={0};

	if (args.Count()==2)
	{
		for (int i=0; i<2; i++)
		{
			if (args[i+1].IsTable())
			{
				if (args[i+1]["a"].IsNumber()) a[i]=args[i+1]["a"].GetFloat();
				if (args[i+1]["r"].IsNumber()) r[i]=args[i+1]["r"].GetFloat();
				if (args[i+1]["g"].IsNumber()) g[i]=args[i+1]["g"].GetFloat();
				if (args[i+1]["b"].IsNumber()) b[i]=args[i+1]["b"].GetFloat();
			}
		}
	}

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("a", a[0]+a[1]);
	table.SetNumber("r", r[0]+r[1]);
	table.SetNumber("g", g[0]+g[1]);
	table.SetNumber("b", b[0]+b[1]);
	return 1;
}

int Lua_Color_Sub(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float a[2]={0}, r[2]={0}, g[2]={0}, b[2]={0};

	if (args.Count()==2)
	{
		for (int i=0; i<2; i++)
		{
			if (args[i+1].IsTable())
			{
				if (args[i+1]["a"].IsNumber()) a[i]=args[i+1]["a"].GetFloat();
				if (args[i+1]["r"].IsNumber()) r[i]=args[i+1]["r"].GetFloat();
				if (args[i+1]["g"].IsNumber()) g[i]=args[i+1]["g"].GetFloat();
				if (args[i+1]["b"].IsNumber()) b[i]=args[i+1]["b"].GetFloat();
			}
		}
	}

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("a", a[0]-a[1]);
	table.SetNumber("r", r[0]-r[1]);
	table.SetNumber("g", g[0]-g[1]);
	table.SetNumber("b", b[0]-b[1]);
	return 1;
}

int Lua_Color_Mul(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float a[2]={0}, r[2]={0}, g[2]={0}, b[2]={0};

	if (args.Count()==2)
	{
		if (args[1].IsTable() && args[2].IsTable())
		{
			for (int i=0; i<2; i++)
			{
				if (args[i+1]["a"].IsNumber()) a[i]=args[i+1]["a"].GetFloat();
				if (args[i+1]["r"].IsNumber()) r[i]=args[i+1]["r"].GetFloat();
				if (args[i+1]["g"].IsNumber()) g[i]=args[i+1]["g"].GetFloat();
				if (args[i+1]["b"].IsNumber()) b[i]=args[i+1]["b"].GetFloat();
			}
		}
		else
		{
			if (args[1].IsTable() && args[2].IsNumber())
			{
				if (args[1]["a"].IsNumber()) a[0]=args[1]["a"].GetFloat();
				if (args[1]["r"].IsNumber()) r[0]=args[1]["r"].GetFloat();
				if (args[1]["g"].IsNumber()) g[0]=args[1]["g"].GetFloat();
				if (args[1]["b"].IsNumber()) b[0]=args[1]["b"].GetFloat();
				a[1]=args[2].GetFloat();
			}
			else if (args[1].IsNumber() && args[2].IsTable())
			{
				a[1]=args[1].GetFloat();
				if (args[2]["a"].IsNumber()) a[0]=args[2]["a"].GetFloat();
				if (args[2]["r"].IsNumber()) r[0]=args[2]["r"].GetFloat();
				if (args[2]["g"].IsNumber()) g[0]=args[2]["g"].GetFloat();
				if (args[2]["b"].IsNumber()) b[0]=args[2]["b"].GetFloat();
			}
			r[1]=a[1];
			g[1]=a[1];
			b[1]=a[1];
		}
	}

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("a", a[0]*a[1]);
	table.SetNumber("r", r[0]*r[1]);
	table.SetNumber("g", g[0]*g[1]);
	table.SetNumber("b", b[0]*b[1]);
	return 1;
}

int Lua_Color_Div(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float a=0, r=0, g=0, b=0, fScale=1;

	if (args.Count()==2)
	{
		if (args[1].IsTable())
		{
			if (args[1]["a"].IsNumber()) a=args[1]["a"].GetFloat();
			if (args[1]["r"].IsNumber()) r=args[1]["r"].GetFloat();
			if (args[1]["g"].IsNumber()) g=args[1]["g"].GetFloat();
			if (args[1]["b"].IsNumber()) b=args[1]["b"].GetFloat();
		}
		if (args[2].IsNumber()) fScale=args[2].GetFloat();
	}

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("a", a/fScale);
	table.SetNumber("r", r/fScale);
	table.SetNumber("g", g/fScale);
	table.SetNumber("b", b/fScale);
	return 1;
}

int Lua_Color_Equal(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float a[2]={0}, r[2]={0}, g[2]={0}, b[2]={0};

	if (args.Count()==2)
	{
		for (int i=0; i<2; i++)
		{
			if (args[i+1].IsTable())
			{
				if (args[i+1]["a"].IsNumber()) a[i]=args[i+1]["a"].GetFloat();
				if (args[i+1]["r"].IsNumber()) r[i]=args[i+1]["r"].GetFloat();
				if (args[i+1]["g"].IsNumber()) g[i]=args[i+1]["g"].GetFloat();
				if (args[i+1]["b"].IsNumber()) b[i]=args[i+1]["b"].GetFloat();
			}
		}
	}

	RUGE::CColor col1(a[0], r[0], g[0], b[0]), col2(a[1], r[1], g[1], b[1]);

	lua->PushBoolean(col1==col2 ? true : false);
	return 1;
}