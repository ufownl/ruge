/*
RUGE Copyright (C) 2009 游侠UFO

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

#pragma once

class CEventHandler : public RUGE::IApplicationEventHandler  // 实现RUGE Application事件处理接口
{
public:
	CEventHandler();
	virtual ~CEventHandler();

	virtual HRESULT InitResource();
	virtual void ReleaseResource();
	virtual BOOL Frame(float fDelta);
	virtual void Render();
	virtual void Pretreat(int nPitch, void *pBits);
	virtual void WndEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	void CreateGUI();

	BOOL HandleKey(int nVKey);
	BOOL HandleCommand(int nID);

	void ChangePreset(int n);
	void SavePreset(int n);
	void LoadPreset(int n);
	void ChangeColor(int nID);

protected:
	RUGE::PAPPLICATION m_pApp;

	RUGE::HFONT m_hFont;
	RUGE::HTEXTURE m_htexGUI, m_htexPar;

	RUGE::CSprite *m_psprLPane1, *m_psprLPane2, *m_psprRPane1, *m_psprRPane2, *m_psprCursor, *m_psprColor, *m_psprBBox;
	RUGE::CAnimation *m_panimPar;
	RUGE::CParticleSystem *m_pParsys;
	RUGE::CGUI *m_pGUI;

	BOOL m_bHelp, m_bBBox, m_bIFace, m_bVSync;
	int m_nPreset;
	float m_fPsx, m_fPsy;
};
