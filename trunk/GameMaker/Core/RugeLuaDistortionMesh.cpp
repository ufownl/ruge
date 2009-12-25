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
#include "RugeLuaDistortionMesh.h"
#include <DistortionMesh.h>

int Lua_DistortionMesh_Create(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	int nRows=0, nCols=0;
	RUGE::CDistortionMesh *pSrc=NULL, *pRes=NULL;

	switch (args.Count())
	{
	case 1:
		if (args[1].IsLightUserData()) pSrc=(RUGE::CDistortionMesh*)args[1].IsLightUserData();
		pRes=new RUGE::CDistortionMesh(*pSrc);
		break;
	case 2:
		if (args[1].IsInteger()) nRows=args[1].GetInteger();
		if (args[2].IsInteger()) nCols=args[2].GetInteger();
		pRes=new RUGE::CDistortionMesh(nRows, nCols);
		break;
	}

	lua->PushLightUserData(pRes);
	return 1;
}

void DistortionMesh_Free(HDISTORTIONMESH hDis)
{
	delete (RUGE::CDistortionMesh*)hDis;
}

HDISTORTIONMESH DistiortionMesh_Assign(HDISTORTIONMESH hDst, HDISTORTIONMESH hSrc)
{
	*(RUGE::CDistortionMesh*)hDst=*(RUGE::CDistortionMesh*)hSrc;
	return hDst;
}

int Lua_DistortionMesh_Clear(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CDistortionMesh *pDis=NULL;
	int nColor=-1;
	float z=0.5f;

	switch (args.Count())
	{
	case 3:
		if (args[3].IsNumber()) z=args[3].GetFloat();
	case 2:
		if (args[2].IsInteger()) nColor=args[2].GetInteger();
	case 1:
		if (args[1].IsLightUserData()) pDis=(RUGE::CDistortionMesh*)args[1].GetLightUserData();
		break;
	}
	pDis->Clear(nColor, z);
	return 0;
}

void DistortionMesh_Render(HDISTORTIONMESH hDis, float x, float y)
{
	((RUGE::CDistortionMesh*)hDis)->Render(x, y);
}

void DistortionMesh_SetTexture(HDISTORTIONMESH hDis, RUGE::HTEXTURE hTex)
{
	((RUGE::CDistortionMesh*)hDis)->SetTexture(hTex);
}

void DistortionMesh_SetTextureRect(HDISTORTIONMESH hDis, float x, float y, float w, float h)
{
	((RUGE::CDistortionMesh*)hDis)->SetTextureRect(x, y, w, h);
}

void DistortionMesh_SetBlendMode(HDISTORTIONMESH hDis, int nBlend)
{
	((RUGE::CDistortionMesh*)hDis)->SetBlendMode(nBlend);
}

void DistortionMesh_SetZ(HDISTORTIONMESH hDis, int nRow, int nCol, float z)
{
	((RUGE::CDistortionMesh*)hDis)->SetZ(nRow, nCol, z);
}

void DistortionMesh_SetColor(HDISTORTIONMESH hDis, int nRow, int nCol, int nColor)
{
	((RUGE::CDistortionMesh*)hDis)->SetColor(nRow, nCol, nColor);
}

void DistortionMesh_SetDisplacement(HDISTORTIONMESH hDis, int nRow, int nCol, float dx, float dy, int nMode)
{
	((RUGE::CDistortionMesh*)hDis)->SetDisplacement(nRow, nCol, dx, dy, nMode);
}

RUGE::HTEXTURE DistortionMesh_GetTexture(HDISTORTIONMESH hDis)
{
	return ((RUGE::CDistortionMesh*)hDis)->GetTexture();
}

int Lua_DistortionMesh_GetTextureRect(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CDistortionMesh *pDis=NULL;
	float x=0, y=0, w=0, h=0;

	if (args.Count()==1 && args[1].IsLightUserData()) pDis=(RUGE::CDistortionMesh*)args[1].GetLightUserData();
	pDis->GetTextureRect(&x, &y, &w, &h);

	lua->PushNumber(x);
	lua->PushNumber(y);
	lua->PushNumber(w);
	lua->PushNumber(h);
	return 4;
}

int DistortionMesh_GetBlendMode(HDISTORTIONMESH hDis)
{
	return ((RUGE::CDistortionMesh*)hDis)->GetBlendMode();
}

float DistortionMesh_GetZ(HDISTORTIONMESH hDis, int nRow, int nCol)
{
	return ((RUGE::CDistortionMesh*)hDis)->GetZ(nRow, nCol);
}

int DistortionMesh_GetColor(HDISTORTIONMESH hDis, int nRow, int nCol)
{
	return ((RUGE::CDistortionMesh*)hDis)->GetColor(nRow, nCol);
}

int Lua_DistortionMesh_GetDisplacement(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CDistortionMesh *pDis=NULL;
	int nRow=0, nCol=0, nMode=DISP_NODE;
	float dx=0, dy=0;

	if (args.Count()==4)
	{
		if (args[1].IsLightUserData()) pDis=(RUGE::CDistortionMesh*)args[1].GetLightUserData();
		if (args[2].IsInteger()) nRow=args[2].GetInteger();
		if (args[3].IsInteger()) nCol=args[3].GetInteger();
		if (args[4].IsInteger()) nMode=args[4].GetInteger();
	}
	pDis->GetDisplacement(nRow, nCol, &dx, &dy, nMode);

	lua->PushNumber(dx);
	lua->PushNumber(dy);
	return 2;
}

int DistortionMesh_GetRows(HDISTORTIONMESH hDis)
{
	return ((RUGE::CDistortionMesh*)hDis)->GetRows();
}

int DistortionMesh_GetCols(HDISTORTIONMESH hDis)
{
	return ((RUGE::CDistortionMesh*)hDis)->GetCols();
}