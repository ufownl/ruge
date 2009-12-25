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

#define DISP_NODE		0
#define DISP_CENTER		1
#define DISP_TOPLEFT	2

typedef HANDLE HDISTORTIONMESH;

int Lua_DistortionMesh_Create(LuaPlus::LuaState *lua);
void DistortionMesh_Free(HDISTORTIONMESH hDis);

HDISTORTIONMESH DistiortionMesh_Assign(HDISTORTIONMESH hDst, HDISTORTIONMESH hSrc);

int Lua_DistortionMesh_Clear(LuaPlus::LuaState *lua);
void DistortionMesh_Render(HDISTORTIONMESH hDis, float x, float y);

void DistortionMesh_SetTexture(HDISTORTIONMESH hDis, RUGE::HTEXTURE hTex);
void DistortionMesh_SetTextureRect(HDISTORTIONMESH hDis, float x, float y, float w, float h);
void DistortionMesh_SetBlendMode(HDISTORTIONMESH hDis, int nBlend);
void DistortionMesh_SetZ(HDISTORTIONMESH hDis, int nRow, int nCol, float z);
void DistortionMesh_SetColor(HDISTORTIONMESH hDis, int nRow, int nCol, int nColor);
void DistortionMesh_SetDisplacement(HDISTORTIONMESH hDis, int nRow, int nCol, float dx, float dy, int nMode);

RUGE::HTEXTURE DistortionMesh_GetTexture(HDISTORTIONMESH hDis);
int Lua_DistortionMesh_GetTextureRect(LuaPlus::LuaState *lua);
int DistortionMesh_GetBlendMode(HDISTORTIONMESH hDis);
float DistortionMesh_GetZ(HDISTORTIONMESH hDis, int nRow, int nCol);
int DistortionMesh_GetColor(HDISTORTIONMESH hDis, int nRow, int nCol);
int Lua_DistortionMesh_GetDisplacement(LuaPlus::LuaState *lua);
int DistortionMesh_GetRows(HDISTORTIONMESH hDis);
int DistortionMesh_GetCols(HDISTORTIONMESH hDis);