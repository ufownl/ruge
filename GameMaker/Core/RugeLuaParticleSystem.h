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

#include "RugeLuaSprite.h"
#include "RugeLuaVector.h"
#include "RugeLuaColor.h"

typedef HANDLE HPARTICLESYSTEM;

int Lua_ParticleSystem_Create(LuaPlus::LuaState *lua);
void ParticleSystem_Free(HPARTICLESYSTEM hPar);

HPARTICLESYSTEM ParticleSystem_Assign(HPARTICLESYSTEM hDst, HPARTICLESYSTEM hSrc);

void ParticleSystem_Render(HPARTICLESYSTEM hPar);
void ParticleSystem_Fire(HPARTICLESYSTEM hPar);
void ParticleSystem_FireAt(HPARTICLESYSTEM hPar, float x, float y);
int Lua_ParticleSystem_Stop(LuaPlus::LuaState *lua);
void ParticleSystem_Update(HPARTICLESYSTEM hPar, float fDelta);
int Lua_ParticleSystem_MoveTo(LuaPlus::LuaState *lua);
void ParticleSystem_Transpose(HPARTICLESYSTEM hPar, float x, float y);
void ParticleSystem_SetScale(HPARTICLESYSTEM hPar, float fScale);
void ParticleSystem_TrackBoundingBox(HPARTICLESYSTEM hPar, bool bTrack);

int ParticleSystem_GetParticlesAlive(HPARTICLESYSTEM hPar);
float ParticleSystem_GetAge(HPARTICLESYSTEM hPar);
int Lua_ParticleSystem_GetPosition(LuaPlus::LuaState *lua);
int Lua_ParticleSystem_GetTransposition(LuaPlus::LuaState *lua);
float ParticleSystemm_GetScale(HPARTICLESYSTEM hPar);
int Lua_ParticleSystem_GetBoundingBox(LuaPlus::LuaState *lua);

int Lua_ParticleSystem_SetInfo(LuaPlus::LuaState *lua);
int Lua_ParticleSystem_GetInfo(LuaPlus::LuaState *lua);
int Lua_ParticleSystem_SerializeInfo(LuaPlus::LuaState *lua);