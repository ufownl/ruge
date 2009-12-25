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
#include "RugeLuaParticleSystem.h"
#include <ParticleSystem.h>

int Lua_ParticleSystem_Create(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	const char *pcszPath=NULL;
	RUGE::CSprite *pSpr=NULL;
	RUGE::CParticleSystem *pSrc=NULL, *pRes=NULL;

	switch (args.Count())
	{
	case 1:
		if (args[1].IsLightUserData())
		{
			pSrc=(RUGE::CParticleSystem*)args[1].GetLightUserData();
			pRes=new RUGE::CParticleSystem(*pSrc);
		}
		else if (args[1].IsTable())
		{
			RUGE::PARTICLESYSTEMINFO Info={0};

			if (args[1]["Sprite"].IsLightUserData()) Info.pSprite=(RUGE::CSprite*)args[1]["Sprite"].GetLightUserData();
			if (args[1]["Emission"].IsInteger()) Info.nEmission=args[1]["Emission"].GetInteger();
			if (args[1]["Lifetime"].IsNumber()) Info.fLifetime=args[1]["Lifetime"].GetFloat();
			if (args[1]["ParticleLifeMin"].IsNumber()) Info.fParticleLifeMin=args[1]["ParticleLifeMin"].GetFloat();
			if (args[1]["ParticleLifeMax"].IsNumber()) Info.fParticleLifeMax=args[1]["ParticleLifeMax"].GetFloat();
			if (args[1]["Direction"].IsNumber()) Info.fDirection=args[1]["Direction"].GetFloat();
			if (args[1]["Spread"].IsNumber()) Info.fSpread=args[1]["Spread"].GetFloat();
			if (args[1]["Relative"].IsBoolean()) Info.bRelative=args[1]["Relative"].GetBoolean();
			if (args[1]["SpeedMin"].IsNumber()) Info.fSpeedMin=args[1]["SpeedMin"].GetFloat();
			if (args[1]["SpeedMax"].IsNumber()) Info.fSpeedMax=args[1]["SpeedMax"].GetFloat();
			if (args[1]["GravityMin"].IsNumber()) Info.fGravityMin=args[1]["GravityMin"].GetFloat();
			if (args[1]["GravityMax"].IsNumber()) Info.fGravityMax=args[1]["GravityMax"].GetFloat();
			if (args[1]["RadialAccelMin"].IsNumber()) Info.fRadialAccelMin=args[1]["RadialAccelMin"].GetFloat();
			if (args[1]["RadialAccelMax"].IsNumber()) Info.fRadialAccelMax=args[1]["RadialAccelMax"].GetFloat();
			if (args[1]["TangentialAccelMin"].IsNumber()) Info.fTangentialAccelMin=args[1]["TangentialAccelMin"].GetFloat();
			if (args[1]["TangentialAccelMax"].IsNumber()) Info.fTangentialAccelMax=args[1]["TangentialAccelMax"].GetFloat();
			if (args[1]["SizeStart"].IsNumber()) Info.fSizeStart=args[1]["SizeStart"].GetFloat();
			if (args[1]["SizeEnd"].IsNumber()) Info.fSizeEnd=args[1]["SizeEnd"].GetFloat();
			if (args[1]["SizeVar"].IsNumber()) Info.fSizeVar=args[1]["SizeVar"].GetFloat();
			if (args[1]["SpinStart"].IsNumber()) Info.fSpinStart=args[1]["SpinStart"].GetFloat();
			if (args[1]["SpinEnd"].IsNumber()) Info.fSpinEnd=args[1]["SpinEnd"].GetFloat();
			if (args[1]["SpinVar"].IsNumber()) Info.fSpinVar=args[1]["SpinVar"].GetFloat();
			if (args[1]["ColorStart"].IsTable())
			{
				float a=0, r=0, g=0, b=0;

				if (args[1]["ColorStart"]["a"].IsNumber()) a=args[1]["ColorStart"]["a"].GetFloat();
				if (args[1]["ColorStart"]["r"].IsNumber()) r=args[1]["ColorStart"]["r"].GetFloat();
				if (args[1]["ColorStart"]["g"].IsNumber()) g=args[1]["ColorStart"]["g"].GetFloat();
				if (args[1]["ColorStart"]["b"].IsNumber()) b=args[1]["ColorStart"]["b"].GetFloat();
				Info.colColorStart=RUGE::CColor(a, r, g, b);
			}
			if (args[1]["ColorEnd"].IsTable())
			{
				float a=0, r=0, g=0, b=0;

				if (args[1]["ColorEnd"]["a"].IsNumber()) a=args[1]["ColorEnd"]["a"].GetFloat();
				if (args[1]["ColorEnd"]["r"].IsNumber()) r=args[1]["ColorEnd"]["r"].GetFloat();
				if (args[1]["ColorEnd"]["g"].IsNumber()) g=args[1]["ColorEnd"]["g"].GetFloat();
				if (args[1]["ColorEnd"]["b"].IsNumber()) b=args[1]["ColorEnd"]["b"].GetFloat();
				Info.colColorEnd=RUGE::CColor(a, r, g, b);
			}
			if (args[1]["ColorVar"].IsNumber()) Info.fColorVar=args[1]["ColorVar"].GetFloat();
			if (args[1]["AlphaVar"].IsNumber()) Info.fAlphaVar=args[1]["fAlphaVar"].GetFloat();
			pRes=new RUGE::CParticleSystem(&Info);
		}
		break;
	case 2:
		if (args[1].IsString()) pcszPath=args[1].GetString();
		if (args[2].IsLightUserData()) pSpr=(RUGE::CSprite*)args[2].GetLightUserData();
		pRes=new RUGE::CParticleSystem(pcszPath, pSpr);
		break;
	}

	lua->PushLightUserData(pRes);
	return 1;
}

void ParticleSystem_Free(HPARTICLESYSTEM hPar)
{
	delete (RUGE::CParticleSystem*)hPar;
}

HPARTICLESYSTEM ParticleSystem_Assign(HPARTICLESYSTEM hDst, HPARTICLESYSTEM hSrc)
{
	*(RUGE::CParticleSystem*)hDst=*(RUGE::CParticleSystem*)hSrc;
	return hDst;
}

void ParticleSystem_Render(HPARTICLESYSTEM hPar)
{
	((RUGE::CParticleSystem*)hPar)->Render();
}

void ParticleSystem_Fire(HPARTICLESYSTEM hPar)
{
	((RUGE::CParticleSystem*)hPar)->Fire();
}

void ParticleSystem_FireAt(HPARTICLESYSTEM hPar, float x, float y)
{
	((RUGE::CParticleSystem*)hPar)->FireAt(x, y);
}

int Lua_ParticleSystem_Stop(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CParticleSystem *pPar=NULL;
	bool bKillParticles=false;
	
	switch (args.Count())
	{
	case 2:
		if (args[2].IsBoolean()) bKillParticles=args[2].GetBoolean();
	case 1:
		if (args[1].IsLightUserData()) pPar=(RUGE::CParticleSystem*)args[1].GetLightUserData();
		break;
	}
	pPar->Stop((BOOL)bKillParticles);
	return 0;
}

void ParticleSystem_Update(HPARTICLESYSTEM hPar, float fDelta)
{
	((RUGE::CParticleSystem*)hPar)->Update(fDelta);
}

int Lua_ParticleSystem_MoveTo(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CParticleSystem *pPar=NULL;
	float x=0, y=0;
	bool bMoveParticles=false;

	switch (args.Count())
	{
	case 4:
		if (args[4].IsBoolean()) bMoveParticles=args[4].GetBoolean();
	case 3:
		if (args[1].IsLightUserData()) pPar=(RUGE::CParticleSystem*)args[1].GetLightUserData();
		if (args[2].IsNumber()) x=args[2].GetFloat();
		if (args[3].IsNumber()) y=args[3].GetFloat();
		break;
	}
	pPar->MoveTo(x, y, (BOOL)bMoveParticles);
	return 0;
}

void ParticleSystem_Transpose(HPARTICLESYSTEM hPar, float x, float y)
{
	((RUGE::CParticleSystem*)hPar)->Transpose(x, y);
}

void ParticleSystem_SetScale(HPARTICLESYSTEM hPar, float fScale)
{
	((RUGE::CParticleSystem*)hPar)->SetScale(fScale);
}

void ParticleSystem_TrackBoundingBox(HPARTICLESYSTEM hPar, bool bTrack)
{
	((RUGE::CParticleSystem*)hPar)->TrackBoundingBox((BOOL)bTrack);
}

int ParticleSystem_GetParticlesAlive(HPARTICLESYSTEM hPar)
{
	return ((RUGE::CParticleSystem*)hPar)->GetParticlesAlive();
}

float ParticleSystem_GetAge(HPARTICLESYSTEM hPar)
{
	return ((RUGE::CParticleSystem*)hPar)->GetAge();
}

int Lua_ParticleSystem_GetPosition(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CParticleSystem *pPar=NULL;
	float x=0, y=0;

	if (args.Count()==1 && args[1].IsLightUserData()) pPar=(RUGE::CParticleSystem*)args[1].GetLightUserData();
	pPar->GetPosition(&x, &y);
	
	lua->PushNumber(x);
	lua->PushNumber(y);
	return 2;
}

int Lua_ParticleSystem_GetTransposition(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CParticleSystem *pPar=NULL;
	float x=0, y=0;

	if (args.Count()==1 && args[1].IsLightUserData()) pPar=(RUGE::CParticleSystem*)args[1].GetLightUserData();
	pPar->GetTransposition(&x, &y);
	
	lua->PushNumber(x);
	lua->PushNumber(y);
	return 2;
}

float ParticleSystemm_GetScale(HPARTICLESYSTEM hPar)
{
	return ((RUGE::CParticleSystem*)hPar)->GetScale();
}

int Lua_ParticleSystem_GetBoundingBox(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CParticleSystem *pPar=NULL;
	RUGE::CRect rect;

	if (args.Count()==1 && args[1].IsLightUserData()) pPar=(RUGE::CParticleSystem*)args[1].GetLightUserData();
	pPar->GetBoundingBox(&rect);

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetNumber("Left", rect.x1);
	table.SetNumber("Top", rect.y1);
	table.SetNumber("Right", rect.x2);
	table.SetNumber("Bottom", rect.y2);
	return 1;
}

int Lua_ParticleSystem_SetInfo(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CParticleSystem *pPar=NULL;

	if (args.Count()==2)
	{
		if (args[1].IsLightUserData()) pPar=(RUGE::CParticleSystem*)args[1].GetLightUserData();
		if (args[2].IsTable())
		{
			if (args[2]["Sprite"].IsLightUserData()) pPar->m_Info.pSprite=(RUGE::CSprite*)args[2]["Sprite"].GetLightUserData();
			if (args[2]["Emission"].IsInteger()) pPar->m_Info.nEmission=args[2]["Emission"].GetInteger();
			if (args[2]["Lifetime"].IsNumber()) pPar->m_Info.fLifetime=args[2]["Lifetime"].GetFloat();
			if (args[2]["ParticleLifeMin"].IsNumber()) pPar->m_Info.fParticleLifeMin=args[2]["ParticleLifeMin"].GetFloat();
			if (args[2]["ParticleLifeMax"].IsNumber()) pPar->m_Info.fParticleLifeMax=args[2]["ParticleLifeMax"].GetFloat();
			if (args[2]["Direction"].IsNumber()) pPar->m_Info.fDirection=args[2]["Direction"].GetFloat();
			if (args[2]["Spread"].IsNumber()) pPar->m_Info.fSpread=args[2]["Spread"].GetFloat();
			if (args[2]["Relative"].IsBoolean()) pPar->m_Info.bRelative=args[2]["Relative"].GetBoolean();
			if (args[2]["SpeedMin"].IsNumber()) pPar->m_Info.fSpeedMin=args[2]["SpeedMin"].GetFloat();
			if (args[2]["SpeedMax"].IsNumber()) pPar->m_Info.fSpeedMax=args[2]["SpeedMax"].GetFloat();
			if (args[2]["GravityMin"].IsNumber()) pPar->m_Info.fGravityMin=args[2]["GravityMin"].GetFloat();
			if (args[2]["GravityMax"].IsNumber()) pPar->m_Info.fGravityMax=args[2]["GravityMax"].GetFloat();
			if (args[2]["RadialAccelMin"].IsNumber()) pPar->m_Info.fRadialAccelMin=args[2]["RadialAccelMin"].GetFloat();
			if (args[2]["RadialAccelMax"].IsNumber()) pPar->m_Info.fRadialAccelMax=args[2]["RadialAccelMax"].GetFloat();
			if (args[2]["TangentialAccelMin"].IsNumber()) pPar->m_Info.fTangentialAccelMin=args[2]["TangentialAccelMin"].GetFloat();
			if (args[2]["TangentialAccelMax"].IsNumber()) pPar->m_Info.fTangentialAccelMax=args[2]["TangentialAccelMax"].GetFloat();
			if (args[2]["SizeStart"].IsNumber()) pPar->m_Info.fSizeStart=args[2]["SizeStart"].GetFloat();
			if (args[2]["SizeEnd"].IsNumber()) pPar->m_Info.fSizeEnd=args[2]["SizeEnd"].GetFloat();
			if (args[2]["SizeVar"].IsNumber()) pPar->m_Info.fSizeVar=args[2]["SizeVar"].GetFloat();
			if (args[2]["SpinStart"].IsNumber()) pPar->m_Info.fSpinStart=args[2]["SpinStart"].GetFloat();
			if (args[2]["SpinEnd"].IsNumber()) pPar->m_Info.fSpinEnd=args[2]["SpinEnd"].GetFloat();
			if (args[2]["SpinVar"].IsNumber()) pPar->m_Info.fSpinVar=args[2]["SpinVar"].GetFloat();
			if (args[2]["ColorStart"].IsTable())
			{
				if (args[2]["ColorStart"]["a"].IsNumber()) pPar->m_Info.colColorStart.a=args[2]["ColorStart"]["a"].GetFloat();
				if (args[2]["ColorStart"]["r"].IsNumber()) pPar->m_Info.colColorStart.r=args[2]["ColorStart"]["r"].GetFloat();
				if (args[2]["ColorStart"]["g"].IsNumber()) pPar->m_Info.colColorStart.g=args[2]["ColorStart"]["g"].GetFloat();
				if (args[2]["ColorStart"]["b"].IsNumber()) pPar->m_Info.colColorStart.b=args[2]["ColorStart"]["b"].GetFloat();
			}
			if (args[2]["ColorEnd"].IsTable())
			{
				if (args[2]["ColorEnd"]["a"].IsNumber()) pPar->m_Info.colColorEnd.a=args[2]["ColorEnd"]["a"].GetFloat();
				if (args[2]["ColorEnd"]["r"].IsNumber()) pPar->m_Info.colColorEnd.r=args[2]["ColorEnd"]["r"].GetFloat();
				if (args[2]["ColorEnd"]["g"].IsNumber()) pPar->m_Info.colColorEnd.g=args[2]["ColorEnd"]["g"].GetFloat();
				if (args[2]["ColorEnd"]["b"].IsNumber()) pPar->m_Info.colColorEnd.b=args[2]["ColorEnd"]["b"].GetFloat();
			}
			if (args[2]["ColorVar"].IsNumber()) pPar->m_Info.fColorVar=args[2]["ColorVar"].GetFloat();
			if (args[2]["AlphaVar"].IsNumber()) pPar->m_Info.fAlphaVar=args[2]["fAlphaVar"].GetFloat();
		}
	}
	return 0;
}

int Lua_ParticleSystem_GetInfo(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CParticleSystem *pPar=NULL;

	if (args.Count()==1 && args[1].IsLightUserData()) pPar=(RUGE::CParticleSystem*)args[1].GetLightUserData();

	LuaPlus::LuaStackObject table=lua->CreateTable();

	table.SetLightUserData("Sprite", pPar->m_Info.pSprite);
	table.SetNumber("Emission", pPar->m_Info.nEmission);
	table.SetNumber("Lifetime", pPar->m_Info.fLifetime);
	table.SetNumber("ParticleLifeMin", pPar->m_Info.fParticleLifeMin);
	table.SetNumber("ParticleLifeMax", pPar->m_Info.fParticleLifeMax);
	table.SetNumber("Direction", pPar->m_Info.fDirection);
	table.SetNumber("Spread", pPar->m_Info.fSpread);
	table.SetBoolean("Relative", pPar->m_Info.bRelative ? true : false);
	table.SetNumber("SpeedMin", pPar->m_Info.fSpeedMin);
	table.SetNumber("SpeedMax", pPar->m_Info.fSpeedMax);
	table.SetNumber("GravityMin", pPar->m_Info.fGravityMin);
	table.SetNumber("GravityMax", pPar->m_Info.fGravityMax);
	table.SetNumber("RadialAccelMin", pPar->m_Info.fRadialAccelMin);
	table.SetNumber("RadialAccelMax", pPar->m_Info.fRadialAccelMax);
	table.SetNumber("TangentialAccelMin", pPar->m_Info.fTangentialAccelMin);
	table.SetNumber("TangentialAccelMax", pPar->m_Info.fTangentialAccelMax);
	table.SetNumber("SizeStart", pPar->m_Info.fSizeStart);
	table.SetNumber("SizeEnd", pPar->m_Info.fSizeEnd);
	table.SetNumber("SizeVar", pPar->m_Info.fSizeVar);
	table.SetNumber("SpinStart", pPar->m_Info.fSpinStart);
	table.SetNumber("SpinEnd", pPar->m_Info.fSpinEnd);
	table.SetNumber("SpinVar", pPar->m_Info.fSpinVar);

	LuaPlus::LuaStackObject ColorStart=table.CreateTable("ColorStart"), ColorEnd=table.CreateTable("ColorEnd");

	ColorStart.SetNumber("a", pPar->m_Info.colColorStart.a);
	ColorStart.SetNumber("r", pPar->m_Info.colColorStart.r);
	ColorStart.SetNumber("g", pPar->m_Info.colColorStart.g);
	ColorStart.SetNumber("b", pPar->m_Info.colColorStart.b);

	ColorEnd.SetNumber("a", pPar->m_Info.colColorEnd.a);
	ColorEnd.SetNumber("r", pPar->m_Info.colColorEnd.r);
	ColorEnd.SetNumber("g", pPar->m_Info.colColorEnd.g);
	ColorEnd.SetNumber("b", pPar->m_Info.colColorEnd.b);

	table.SetNumber("ColorVar", pPar->m_Info.fColorVar);
	table.SetNumber("AlphaVar", pPar->m_Info.fAlphaVar);

	lua->Pop();
	lua->Pop();
	return 1;
}

int Lua_ParticleSystem_SerializeInfo(LuaPlus::LuaState *lua)
{
	LuaPlus::LuaStack args(lua);
	RUGE::CParticleSystem *pPar=NULL;
	LPCSTR lpcszPath=NULL;
	bool bWrite=false;
	WORD wHi=0, wLo=0;

	switch (args.Count())
	{
	case 5:
		if (args[5].IsInteger()) wLo=args[5].GetInteger();
	case 4:
		if (args[4].IsInteger()) wHi=args[4].GetInteger();
	case 3:
		if (args[3].IsBoolean()) bWrite=args[3].GetBoolean();
	case 2:
		if (args[1].IsLightUserData()) pPar=(RUGE::CParticleSystem*)args[1].GetLightUserData();
		if (args[2].IsString()) lpcszPath=args[2].GetString();
		break;
	}

	if (bWrite)
	{
		FILE *pOut=NULL;
		RUGE::CSprite *pSpr=pPar->m_Info.pSprite;

		pOut=fopen(lpcszPath, "w");
		if (pOut==NULL) return 0;
		pPar->m_Info.pSprite=(RUGE::CSprite*)(DWORD_PTR)(wLo|wHi<<16);
		fwrite(&pPar->m_Info, 1, sizeof(RUGE::PARTICLESYSTEMINFO), pOut);
		fclose(pOut);
		pPar->m_Info.pSprite=pSpr;
		return 0;
	}
	else
	{
		FILE *pIn=NULL;
		RUGE::CSprite *pSpr=pPar->m_Info.pSprite;

		pIn=fopen(lpcszPath, "r");
		if (pIn==NULL) return 0;
		fread(&pPar->m_Info, 1, sizeof(RUGE::PARTICLESYSTEMINFO), pIn);
		fclose(pIn);
		lua->PushInteger((DWORD)(DWORD_PTR)pPar->m_Info.pSprite>>16);
		lua->PushInteger((DWORD)(DWORD_PTR)pPar->m_Info.pSprite&0xFFFF);
		pPar->m_Info.pSprite=pSpr;
		return 2;
	}
}