/*
RUGE Copyright (C) 2009 ”Œœ¿UFO

This file is part of RUGE.

RUGE is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RUGE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RUGE.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "StdAfx.h"
#include "ParticleSystem.h"

CParticleSystem::CParticleSystem(const char *pcszPath, CSprite *pSpr)
	: m_pApp(GetRUGE())
	, m_fTx(0)
	, m_fTy(0)
	, m_fScale(1.0f)
	, m_fEmissionResidue(0.0f)
	, m_nParticlesAlive(0)
	, m_fAge(-2.0)
	, m_bUpdateBoundingBox(false)
{
	FILE *pIn=fopen(pcszPath, "rb");
	__int64 nSize=0;

	if (pIn==NULL) return;
	fread(&m_Info, 1, sizeof(PARTICLESYSTEMINFO), pIn);
	m_Info.pSprite=pSpr;
	m_rectBoundingBox.Clear();
}

CParticleSystem::CParticleSystem(PPARTICLESYSTEMINFO pPsi)
	: m_pApp(GetRUGE())
	, m_fTx(0)
	, m_fTy(0)
	, m_fScale(1.0f)
	, m_fEmissionResidue(0.0f)
	, m_nParticlesAlive(0)
	, m_fAge(-2.0)
	, m_bUpdateBoundingBox(false)
{
	memcpy(&m_Info, pPsi, sizeof(PARTICLESYSTEMINFO));
	m_rectBoundingBox.Clear();
}

CParticleSystem::CParticleSystem(const CParticleSystem &ps)
	: m_pApp(GetRUGE())
	, m_Info(ps.m_Info)
	, m_fAge(ps.m_fAge)
	, m_fEmissionResidue(ps.m_fEmissionResidue)
	, m_vecPrevLocation(ps.m_vecPrevLocation)
	, m_vecLocation(ps.m_vecLocation)
	, m_fTx(ps.m_fTx)
	, m_fTy(ps.m_fTy)
	, m_fScale(ps.m_fScale)
	, m_nParticlesAlive(ps.m_nParticlesAlive)
	, m_rectBoundingBox(ps.m_rectBoundingBox)
	, m_bUpdateBoundingBox(false)
{
	memcpy(m_Particles, ps.m_Particles, MAX_PARTICLES);
}

CParticleSystem::~CParticleSystem()
{
	m_pApp->Release();
}

CParticleSystem& CParticleSystem::operator = (const CParticleSystem &ps)
{
	m_Info=ps.m_Info;
	m_fAge=ps.m_fAge;
	m_fEmissionResidue=ps.m_fEmissionResidue;
	m_vecPrevLocation=ps.m_vecPrevLocation;
	m_vecLocation=ps.m_vecLocation;
	m_fTx=ps.m_fTx;
	m_fTy=ps.m_fTy;
	m_fScale=ps.m_fScale;
	m_nParticlesAlive=ps.m_nParticlesAlive;
	m_rectBoundingBox=ps.m_rectBoundingBox;
	memcpy(m_Particles, ps.m_Particles, MAX_PARTICLES);
	return *this;
}

void CParticleSystem::Render()
{
	DWORD dwColor=m_Info.pSprite->GetColor();
	PPARTICLE pPar=m_Particles;

	for (int i=0; i<m_nParticlesAlive; i++, pPar++)
	{
		if(m_Info.colColorStart.r<0) m_Info.pSprite->SetColor(SETA(m_Info.pSprite->GetColor(), pPar->colColor.a*255.0f));
		else m_Info.pSprite->SetColor(pPar->colColor.GetColor());
		m_Info.pSprite->Render(pPar->vecLocation.x*m_fScale+m_fTx, pPar->vecLocation.y*m_fScale+m_fTy, pPar->fSpin*pPar->fAge, pPar->fSize*m_fScale);
	}
	m_Info.pSprite->SetColor(dwColor);
}

void CParticleSystem::Fire()
{
	if (m_Info.fLifetime==-1.0f) m_fAge=-1.0f;
	else m_fAge=0.0f;
}

void CParticleSystem::FireAt(float x, float y)
{
	Stop();
	MoveTo(x, y);
	Fire();
}

void CParticleSystem::Stop(bool bKillParticles/* =false */)
{
	m_fAge=-2.0f;
	if(bKillParticles) 
	{
		m_nParticlesAlive=0;
		m_rectBoundingBox.Clear();
	}
}

void CParticleSystem::Update(float fDeltaTime)
{
	float fAng;
	PPARTICLE pPar;
	CVector vecAccel, vecAccel2;

	if (m_fAge >= 0)
	{
		m_fAge+=fDeltaTime;
		if(m_fAge>=m_Info.fLifetime) m_fAge=-2.0f;
	}
	if (m_bUpdateBoundingBox) m_rectBoundingBox.Clear();
	pPar=m_Particles;
	for (int i=0; i<m_nParticlesAlive; i++, pPar++)
	{
		pPar->fAge+=fDeltaTime;
		if(pPar->fAge>=pPar->fTerminalAge)
		{
			m_nParticlesAlive--;
			memcpy(pPar, m_Particles+m_nParticlesAlive, sizeof(PARTICLE));
			i--;
			continue;
		}
		vecAccel=pPar->vecLocation-m_vecLocation;
		vecAccel.Normalize();
		vecAccel2=vecAccel;
		vecAccel*=pPar->fRadialAccel;
		fAng=vecAccel2.x;
		vecAccel2.x=-vecAccel2.y;
		vecAccel2.y=fAng;
		vecAccel2*=pPar->fTangentialAccel;
		pPar->vecVelocity+=(vecAccel+vecAccel2)*fDeltaTime;
		pPar->vecVelocity.y+=pPar->fGravity*fDeltaTime;
		pPar->vecLocation+=pPar->vecVelocity*fDeltaTime;
		pPar->fSpin+=pPar->fSpinDelta*fDeltaTime;
		pPar->fSize+=pPar->fSizeDelta*fDeltaTime;
		pPar->colColor+=pPar->colColorDelta*fDeltaTime;
		if(m_bUpdateBoundingBox) m_rectBoundingBox.Encapsulate(pPar->vecLocation.x, pPar->vecLocation.y);
	}
	if (m_fAge != -2.0f)
	{
		float fParticlesNeeded=m_Info.nEmission*fDeltaTime+m_fEmissionResidue;
		int nParticlesCreated=(int)fParticlesNeeded;

		m_fEmissionResidue=fParticlesNeeded-nParticlesCreated;
		pPar=m_Particles+m_nParticlesAlive;
		for (int i=0; i<nParticlesCreated; i++, pPar++, m_nParticlesAlive++)
		{
			if (m_nParticlesAlive>=MAX_PARTICLES) break;
			pPar->fAge=0.0f;
			pPar->fTerminalAge=m_pApp->Random_Float(m_Info.fParticleLifeMin, m_Info.fParticleLifeMax);
			pPar->vecLocation=m_vecPrevLocation+(m_vecLocation-m_vecPrevLocation)*m_pApp->Random_Float(0.0f, 1.0f);
			pPar->vecLocation.x+=m_pApp->Random_Float(-2.0f, 2.0f);
			pPar->vecLocation.y+=m_pApp->Random_Float(-2.0f, 2.0f);
			fAng=m_Info.fDirection-M_PI_2+m_pApp->Random_Float(0, m_Info.fSpread)-m_Info.fSpread/2.0f;
			if(m_Info.bRelative) fAng+=(m_vecPrevLocation-m_vecLocation).Angle()+M_PI_2;
			pPar->vecVelocity.x=cosf(fAng);
			pPar->vecVelocity.y=sinf(fAng);
			pPar->vecVelocity*=m_pApp->Random_Float(m_Info.fSpeedMin, m_Info.fSpeedMax);
			pPar->fGravity=m_pApp->Random_Float(m_Info.fGravityMin, m_Info.fGravityMax);
			pPar->fRadialAccel=m_pApp->Random_Float(m_Info.fRadialAccelMin, m_Info.fRadialAccelMax);
			pPar->fTangentialAccel=m_pApp->Random_Float(m_Info.fTangentialAccelMin, m_Info.fTangentialAccelMax);
			pPar->fSize=m_pApp->Random_Float(m_Info.fSizeStart, m_Info.fSizeStart+(m_Info.fSizeEnd-m_Info.fSizeStart)*m_Info.fSizeVar);
			pPar->fSizeDelta=(m_Info.fSizeEnd-pPar->fSize)/pPar->fTerminalAge;
			pPar->fSpin=m_pApp->Random_Float(m_Info.fSpinStart, m_Info.fSpinStart+(m_Info.fSpinEnd-m_Info.fSpinStart)*m_Info.fSpinVar);
			pPar->fSpinDelta=(m_Info.fSpinEnd-pPar->fSpin)/pPar->fTerminalAge;
			pPar->colColor.a=m_pApp->Random_Float(m_Info.colColorStart.a, m_Info.colColorStart.a+(m_Info.colColorEnd.a-m_Info.colColorStart.a)*m_Info.fAlphaVar);
			pPar->colColor.r=m_pApp->Random_Float(m_Info.colColorStart.r, m_Info.colColorStart.r+(m_Info.colColorEnd.r-m_Info.colColorStart.r)*m_Info.fColorVar);
			pPar->colColor.g=m_pApp->Random_Float(m_Info.colColorStart.g, m_Info.colColorStart.g+(m_Info.colColorEnd.g-m_Info.colColorStart.g)*m_Info.fColorVar);
			pPar->colColor.b=m_pApp->Random_Float(m_Info.colColorStart.b, m_Info.colColorStart.b+(m_Info.colColorEnd.b-m_Info.colColorStart.b)*m_Info.fColorVar);
			pPar->colColorDelta.a=(m_Info.colColorEnd.a-pPar->colColor.a)/pPar->fTerminalAge;
			pPar->colColorDelta.r=(m_Info.colColorEnd.r-pPar->colColor.r)/pPar->fTerminalAge;
			pPar->colColorDelta.g=(m_Info.colColorEnd.g-pPar->colColor.g)/pPar->fTerminalAge;
			pPar->colColorDelta.b=(m_Info.colColorEnd.b-pPar->colColor.b)/pPar->fTerminalAge;
			if(m_bUpdateBoundingBox) m_rectBoundingBox.Encapsulate(pPar->vecLocation.x, pPar->vecLocation.y);
		}
	}
	m_vecPrevLocation=m_vecLocation;
}

void CParticleSystem::MoveTo(float x, float y, bool bMoveParticles/* =false */)
{
	if(bMoveParticles)
	{
		float dx=x-m_vecLocation.x, dy=y-m_vecLocation.y;

		for (int i=0; i<m_nParticlesAlive; i++)
		{
			m_Particles[i].vecLocation.x+=dx;
			m_Particles[i].vecLocation.y+=dy;
		}
		m_vecPrevLocation.x=m_vecPrevLocation.x+dx;
		m_vecPrevLocation.y=m_vecPrevLocation.y+dy;
	}
	else
	{
		if (m_fAge==-2.0)
		{
			m_vecPrevLocation.x=x;
			m_vecPrevLocation.y=y;
		}
		else
		{
			m_vecPrevLocation.x=m_vecLocation.x;
			m_vecPrevLocation.y=m_vecLocation.y;
		}
	}
	m_vecLocation.x=x;
	m_vecLocation.y=y;
}

void CParticleSystem::Transpose(float x, float y)
{
	m_fTx=x;
	m_fTy=y;
}

void CParticleSystem::SetScale(float fScale)
{
	m_fScale=fScale;
}

void CParticleSystem::TrackBoundingBox(bool bTrack)
{
	m_bUpdateBoundingBox=bTrack;
}

int CParticleSystem::GetParticlesAlive() const
{
	return m_nParticlesAlive;
}

float CParticleSystem::GetAge() const
{
	return m_fAge;
}

void CParticleSystem::GetTransposition(float &x, float &y) const
{
	x=m_fTx;
	y=m_fTy;
}

float CParticleSystem::GetScale() const
{
	return m_fScale;
}

CRect* CParticleSystem::GetBoundingBox(CRect *pRect) const
{
	if (pRect==NULL) return NULL;
	*pRect=m_rectBoundingBox;
	pRect->x1*=m_fScale;
	pRect->y1*=m_fScale;
	pRect->x2*=m_fScale;
	pRect->y2*=m_fScale;
	return pRect;
}