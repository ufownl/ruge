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
#include "Table.h"

void TableCopy(LuaPlus::LuaObject *pDst, LuaPlus::LuaStackObject *pSrc)
{
	for (LuaPlus::LuaStackTableIterator Iter(*pSrc); Iter; Iter.Next())
	{
		if (Iter.GetKey().IsString())
		{
			if (Iter.GetValue().IsBoolean()) pDst->SetBoolean(Iter.GetKey().GetString(), Iter.GetValue().GetBoolean());
			else if (Iter.GetValue().IsNumber()) pDst->SetNumber(Iter.GetKey().GetString(), Iter.GetValue().GetNumber());
			else if (Iter.GetValue().IsLightUserData()) pDst->SetLightUserData(Iter.GetKey().GetString(), Iter.GetValue().GetLightUserData());
			else if (Iter.GetValue().IsString()) pDst->SetString(Iter.GetKey().GetString(), Iter.GetValue().GetString());
			else if (Iter.GetValue().IsTable()) TableCopy(&pDst->CreateTable(Iter.GetKey().GetString()), &Iter.GetValue());
		}
	}
}

void TableCopy(LuaPlus::LuaStackObject *pDst, LuaPlus::LuaObject *pSrc)
{
	for (LuaPlus::LuaTableIterator Iter(*pSrc); Iter; Iter.Next())
	{
		if (Iter.GetKey().IsString())
		{
			if (Iter.GetValue().IsBoolean()) pDst->SetBoolean(Iter.GetKey().GetString(), Iter.GetValue().GetBoolean());
			else if (Iter.GetValue().IsNumber()) pDst->SetNumber(Iter.GetKey().GetString(), Iter.GetValue().GetNumber());
			else if (Iter.GetValue().IsLightUserData()) pDst->SetLightUserData(Iter.GetKey().GetString(), Iter.GetValue().GetLightUserData());
			else if (Iter.GetValue().IsString()) pDst->SetString(Iter.GetKey().GetString(), Iter.GetValue().GetString());
			else if (Iter.GetValue().IsTable()) TableCopy(&pDst->CreateTable(Iter.GetKey().GetString()), &Iter.GetValue());
		}
	}
}

void TableCopy(LuaPlus::LuaStackObject *pDst, LuaPlus::LuaStackObject *pSrc)
{
	for (LuaPlus::LuaStackTableIterator Iter(*pSrc); Iter; Iter.Next())
	{
		if (Iter.GetKey().IsString())
		{
			if (Iter.GetValue().IsBoolean()) pDst->SetBoolean(Iter.GetKey().GetString(), Iter.GetValue().GetBoolean());
			else if (Iter.GetValue().IsNumber()) pDst->SetNumber(Iter.GetKey().GetString(), Iter.GetValue().GetNumber());
			else if (Iter.GetValue().IsLightUserData()) pDst->SetLightUserData(Iter.GetKey().GetString(), Iter.GetValue().GetLightUserData());
			else if (Iter.GetValue().IsString()) pDst->SetString(Iter.GetKey().GetString(), Iter.GetValue().GetString());
			else if (Iter.GetValue().IsTable()) TableCopy(&pDst->CreateTable(Iter.GetKey().GetString()), &Iter.GetValue());
		}
	}
}