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
#include "RugeLuaVector.h"
#include <Vector.h>

int Lua_Vector_Negative(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x=0, y=0;

	if (args.Count()==1 && args[1].IsTable())
	{
		if (args[1]["x"].IsNumber()) x=args[1]["x"].GetFloat();
		if (args[1]["y"].IsNumber()) y=args[1]["y"].GetFloat();
	}
	
	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("x", -x);
	table.SetNumber("y", -y);
	return 1;
}

int Lua_Vector_Sub(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x[2]={0}, y[2]={0};

	if (args.Count()==2)
	{
		for (int i=0; i<2; i++)
		{
			if (args[i+1].IsTable())
			{
				if (args[i+1]["x"].IsNumber()) x[i]=args[i+1]["x"].GetFloat();
				if (args[i+1]["y"].IsNumber()) y[i]=args[i+1]["y"].GetFloat();
			}
		}
	}

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("x", x[0]-x[1]);
	table.SetNumber("y", y[0]-y[1]);
	return 1;
}

int Lua_Vector_Add(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x[2]={0}, y[2]={0};

	if (args.Count()==2)
	{
		for (int i=0; i<2; i++)
		{
			if (args[i+1].IsTable())
			{
				if (args[i+1]["x"].IsNumber()) x[i]=args[i+1]["x"].GetFloat();
				if (args[i+1]["y"].IsNumber()) y[i]=args[i+1]["y"].GetFloat();
			}
		}
	}

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("x", x[0]+x[1]);
	table.SetNumber("y", y[0]+y[1]);
	return 1;
}

int Lua_Vector_Div(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x=0, y=0, fScale=1;

	if (args.Count()==2)
	{
		if (args[1].IsTable())
		{
			if (args[1]["x"].IsNumber()) x=args[1]["x"].GetFloat();
			if (args[1]["y"].IsNumber()) y=args[1]["y"].GetFloat();
		}
		if (args[2].IsNumber()) fScale=args[2].GetFloat();
	}

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("x", x/fScale);
	table.SetNumber("y", y/fScale);
	return 1;
}

int Lua_Vector_Mul(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x=0, y=0, fScale=1;

	if (args.Count()==2)
	{
		if (args[1].IsTable() && args[2].IsNumber())
		{
			if (args[1]["x"].IsNumber()) x=args[1]["x"].GetFloat();
			if (args[1]["y"].IsNumber()) y=args[1]["y"].GetFloat();
			fScale=args[2].GetFloat();
		}
		else if (args[1].IsNumber() && args[2].IsTable())
		{
			fScale=args[1].GetFloat();
			if (args[2]["x"].IsNumber()) x=args[2]["x"].GetFloat();
			if (args[2]["y"].IsNumber()) y=args[2]["y"].GetFloat();
		}
	}

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("x", x*fScale);
	table.SetNumber("y", y*fScale);
	return 1;
}

int Lua_Vector_Angle(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x[2]={0}, y[2]={0};

	if (args.Count()==2)
	{
		for (int i=0; i<2; i++)
		{
			if (args[i+1].IsTable())
			{
				if (args[i+1]["x"].IsNumber()) x[i]=args[i+1]["x"].GetFloat();
				if (args[i+1]["y"].IsNumber()) y[i]=args[i+1]["y"].GetFloat();
			}
		}
	}

	RUGE::CVector s(x[0], y[0]), t(x[1], y[1]);

	lua->PushNumber(s.Angle(&t));
	return 1;
}

int Lua_Vector_Dot(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x[2]={0}, y[2]={0};

	if (args.Count()==2)
	{
		for (int i=0; i<2; i++)
		{
			if (args[i+1].IsTable())
			{
				if (args[i+1]["x"].IsNumber()) x[i]=args[i+1]["x"].GetFloat();
				if (args[i+1]["y"].IsNumber()) y[i]=args[i+1]["y"].GetFloat();
			}
		}
	}

	RUGE::CVector s(x[0], y[0]), t(x[1], y[1]);

	lua->PushNumber(s.Dot(&t));
	return 1;
}

int Lua_Vector_Equal(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x[2]={0}, y[2]={0};

	if (args.Count()==2)
	{
		for (int i=0; i<2; i++)
		{
			if (args[i+1].IsTable())
			{
				if (args[i+1]["x"].IsNumber()) x[i]=args[i+1]["x"].GetFloat();
				if (args[i+1]["y"].IsNumber()) y[i]=args[i+1]["y"].GetFloat();
			}
		}
	}

	RUGE::CVector s(x[0], y[0]), t(x[1], y[1]);

	lua->PushBoolean(s==t ? true : false);
	return 1;
}

int Lua_Vector_Length(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x=0, y=0;

	if (args.Count()==1 && args[1].IsTable())
	{
		if (args[1]["x"].IsNumber()) x=args[1]["x"].GetFloat();
		if (args[1]["y"].IsNumber()) y=args[1]["y"].GetFloat();
	}

	RUGE::CVector s(x, y);

	lua->PushNumber(s.Length());
	return 1;
}

int Lua_Vector_Clamp(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x=0, y=0, fMax=0;

	if (args.Count()==2)
	{
		if (args[1].IsTable())
		{
			if (args[1]["x"].IsNumber()) x=args[1]["x"].GetFloat();
			if (args[1]["y"].IsNumber()) y=args[1]["y"].GetFloat();
		}
		if (args[2].IsNumber()) fMax=args[2].GetFloat();
	}

	RUGE::CVector s(x, y);

	s.Clamp(fMax);

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("x", s.x);
	table.SetNumber("y", s.y);
	return 1;
}

int Lua_Vector_Normalize(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x=0, y=0;

	if (args.Count()==1 && args[1].IsTable())
	{
		if (args[1]["x"].IsNumber()) x=args[1]["x"].GetFloat();
		if (args[1]["y"].IsNumber()) y=args[1]["y"].GetFloat();
	}

	RUGE::CVector s(x, y);

	s.Normalize();

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("x", s.x);
	table.SetNumber("y", s.y);
	return 1;
}

int Lua_Vector_Rotate(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	float x=0, y=0, a=0;

	if (args.Count()==2)
	{
		if (args[1].IsTable())
		{
			if (args[1]["x"].IsNumber()) x=args[1]["x"].GetFloat();
			if (args[1]["y"].IsNumber()) y=args[1]["y"].GetFloat();
		}
		if (args[2].IsNumber()) a=args[2].GetFloat();
	}

	RUGE::CVector s(x, y);

	s.Rotate(a);

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("x", s.x);
	table.SetNumber("y", s.y);
	return 1;
}