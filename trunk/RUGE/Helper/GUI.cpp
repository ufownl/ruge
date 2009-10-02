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
#include "GUI.h"

CGUI::CGUI()
	: m_pApp(GetRUGE())
	, m_pCtrlList(NULL)
	, m_pCtrlLock(NULL)
	, m_pCtrlFocus(NULL)
	, m_pCtrlOver(NULL)
	, m_dwNavMode(NAV_NONAVKEYS)
	, m_nEnterExit(0)
	, m_psprCursor(NULL)
	, m_fCurX(0)
	, m_fCurY(0)
	, m_fOldX(0)
	, m_fOldY(0)
	, m_nWheel(0)
	, m_nWheelOld(0)
	, m_bLPressed(FALSE)
	, m_bLReleased(FALSE)
	, m_bRPressed(FALSE)
	, m_bRReleased(FALSE)
{
}

CGUI::~CGUI()
{
	for (CControl *p=m_pCtrlList; p!=NULL; )
	{
		CControl *pCtrlDel=p;

		p=p->m_pNext;
		if (pCtrlDel->m_bManaged) delete pCtrlDel;
	}
	m_pApp->Release();
}

void CGUI::AddCtrl(CControl *pCtrl, BOOL bManaged/* =TRUE */)
{
	pCtrl->m_pGUI=this;
	pCtrl->m_bManaged=bManaged;
	if (m_pCtrlList==NULL)
	{
		m_pCtrlList=pCtrl;
		pCtrl->m_pPrev=NULL;
		pCtrl->m_pNext=NULL;
	}
	else
	{
		CControl *pLast=m_pCtrlList;

		while (pLast->m_pNext!=NULL) pLast=pLast->m_pNext;
		pLast->m_pNext=pCtrl;
		pCtrl->m_pPrev=pLast;
		pCtrl->m_pNext=NULL;
	}
}

void CGUI::DelCtrl(int nID)
{
	for (CControl *p=m_pCtrlList; p!=NULL; p=p->m_pNext)
	{
		if (p->m_nID=nID)
		{
			if (p->m_pPrev!=NULL) p->m_pPrev->m_pNext=p->m_pNext;
			else m_pCtrlList=p->m_pNext;
			if (p->m_pNext!=NULL) p->m_pNext->m_pPrev=p->m_pPrev;
			if (p->m_bManaged) delete p;
			return;
		}
	}
}

CControl* CGUI::GetCtrl(int nID) const
{
	for (CControl *p=m_pCtrlList; p!=NULL; p=p->m_pNext)
	{
		if (p->m_nID==nID) return p;
	}
	return NULL;
}

CControl* CGUI::MoveCtrl(int nID, float x, float y)
{
	CControl *pCtrl=GetCtrl(nID);

	if (pCtrl!=NULL)
	{
		pCtrl->m_Rect.x2=x+(pCtrl->m_Rect.x2-pCtrl->m_Rect.x1);
		pCtrl->m_Rect.y2=y+(pCtrl->m_Rect.y2-pCtrl->m_Rect.y1);
		pCtrl->m_Rect.x1=x;
		pCtrl->m_Rect.y1=y;
	}
	return pCtrl;
}

CControl* CGUI::ShowCtrl(int nID, BOOL bVisible/* =TRUE */)
{
	CControl *pCtrl=GetCtrl(nID);

	if (pCtrl!=NULL) pCtrl->m_bVisible=bVisible;
	return pCtrl;
}

CControl* CGUI::EnableCtrl(int nID, BOOL bEnabled/* =TRUE */)
{
	CControl *pCtrl=GetCtrl(nID);

	if (pCtrl!=NULL) pCtrl->m_bEnabled=bEnabled;
	return pCtrl;
}

void CGUI::SetNavMode(DWORD dwNavMode)
{
	m_dwNavMode=dwNavMode;
}

void CGUI::SetCursor(CSprite *psprCursor)
{
	m_psprCursor=psprCursor;
}

void CGUI::SetColor(DWORD dwColor)
{
	for (CControl *p=m_pCtrlList; p!=NULL; p=p->m_pNext) p->SetColor(dwColor);
}

void CGUI::SetFocus(int nID)
{
	CControl *pCtrlFocus=GetCtrl(nID);

	if (pCtrlFocus==m_pCtrlFocus) return;
	if (pCtrlFocus==NULL)
	{
		m_pCtrlFocus->Focus(FALSE);
		m_pCtrlFocus=NULL;
	}
	else if (!pCtrlFocus->m_bStatic && pCtrlFocus->m_bVisible && pCtrlFocus->m_bEnabled)
	{
		if (m_pCtrlFocus!=NULL) m_pCtrlFocus->Focus(FALSE);
		pCtrlFocus->Focus(TRUE);
		m_pCtrlFocus=pCtrlFocus;
	}
}

int CGUI::GetFocus() const
{
	if (m_pCtrlFocus==NULL) return 0;
	return m_pCtrlFocus->m_nID;
}

void CGUI::Enter()
{
	for (CControl *p=m_pCtrlList; p!=NULL; p=p->m_pNext) p->Enter();
	m_nEnterExit=2;
}

void CGUI::Exit()
{
	for (CControl *p=m_pCtrlList; p!=NULL; p=p->m_pNext) p->Exit();
	m_pCtrlLock=NULL;
	m_pCtrlFocus=NULL;
	m_pCtrlOver=NULL;
	m_nEnterExit=1;
}

void CGUI::Reset()
{
	for (CControl *p=m_pCtrlList; p!=NULL; p=p->m_pNext) p->Reset();
	m_pCtrlLock=NULL;
	m_pCtrlFocus=NULL;
	m_pCtrlOver=NULL;
}

void CGUI::Move(float dx, float dy)
{
	for (CControl *p=m_pCtrlList; p!=NULL; p=p->m_pNext)
	{
		p->m_Rect.x1+=dx;
		p->m_Rect.y1+=dy;
		p->m_Rect.x2+=dx;
		p->m_Rect.y2+=dy;
	}
}

int CGUI::Update(float fDelta)
{
	m_pApp->Input_GetMousePos(&m_fCurX, &m_fCurY);
	m_nWheel=m_pApp->Input_GetMouseWheel();
	m_bLPressed=m_pApp->Input_KeyPressed(VK_LBUTTON);
	m_bLReleased=!m_bLPressed;
	m_bRPressed=m_pApp->Input_KeyPressed(VK_RBUTTON);
	m_bRReleased=!m_bRPressed;

	for (CControl *p=m_pCtrlList; p!=NULL; p=p->m_pNext) p->Update(fDelta);

	if (m_nEnterExit>0)
	{
		BOOL bDone=TRUE;

		for (CControl *p=m_pCtrlList; p!=NULL; p=p->m_pNext)
		{
			if (!p->IsDone())
			{
				bDone=FALSE;
				break;
			}
		}
		if (!bDone) return 0;
		else
		{
			if (m_nEnterExit==1) return -1;
			else m_nEnterExit=0;
		}
	}

	int nVKey=m_pApp->Input_GetKey();

	if ((m_dwNavMode&NAV_LEFTRIGHT) && nVKey==VK_LEFT || (m_dwNavMode & NAV_UPDOWN) && nVKey==VK_UP)
	{
		CControl *pCtrl=m_pCtrlFocus;

		if (pCtrl==NULL)
		{
			pCtrl=m_pCtrlList;
			if (pCtrl==NULL) return 0;
		}
		do 
		{
			pCtrl=pCtrl->m_pPrev;
			if (pCtrl==NULL && ((m_dwNavMode&NAV_CYCLED) || m_pCtrlFocus==NULL))
			{
				pCtrl=m_pCtrlList;
				while (pCtrl->m_pNext!=NULL) pCtrl=pCtrl->m_pNext;
			}
			if (pCtrl==NULL || pCtrl==m_pCtrlFocus) break;
		} while (pCtrl->m_bStatic==TRUE || pCtrl->m_bVisible==FALSE || pCtrl->m_bEnabled==FALSE);
		if (pCtrl!=NULL && pCtrl!=m_pCtrlFocus)
		{
			if (m_pCtrlFocus!=NULL) m_pCtrlFocus->Focus(FALSE);
			pCtrl->Focus(TRUE);
			m_pCtrlFocus=pCtrl;
		}
	}
	else if ((m_dwNavMode&NAV_LEFTRIGHT) && nVKey==VK_RIGHT || (m_dwNavMode & NAV_UPDOWN) && nVKey==VK_DOWN)
	{
		CControl *pCtrl=m_pCtrlFocus;

		if (pCtrl==NULL)
		{
			pCtrl=m_pCtrlList;
			if (pCtrl==NULL) return 0;
			while (pCtrl->m_pNext!=NULL) pCtrl=pCtrl->m_pNext;
		}
		do 
		{
			pCtrl=pCtrl->m_pNext;
			if (pCtrl==NULL && ((m_dwNavMode&NAV_CYCLED) || m_pCtrlFocus==NULL)) pCtrl=m_pCtrlList;
			if (pCtrl==NULL || pCtrl==m_pCtrlFocus) break;
		} while (pCtrl->m_bStatic==TRUE || pCtrl->m_bVisible==FALSE || pCtrl->m_bEnabled==FALSE);
		if (pCtrl!=NULL && pCtrl!=m_pCtrlFocus)
		{
			if (m_pCtrlFocus!=NULL) m_pCtrlFocus->Focus(FALSE);
			pCtrl->Focus(TRUE);
			m_pCtrlFocus=pCtrl;
		}
	}
	else if (m_pCtrlFocus!=NULL && nVKey!=0 && nVKey!=VK_LBUTTON && nVKey!=VK_RBUTTON)
	{
		if (m_pCtrlFocus->KeyClick(nVKey, m_pApp->Input_GetChar())) return m_pCtrlFocus->m_nID;
	}

	if (m_pCtrlLock!=NULL)
	{
		CControl *pCtrl=m_pCtrlLock;

		if (!m_bLPressed && !m_bRPressed) m_pCtrlLock=NULL;
		if (ProcessCtrl(pCtrl)) return pCtrl->m_nID;
	}
	else
	{
		CControl *pCtrl=m_pCtrlList;

		if (pCtrl!=NULL)
		{
			while (pCtrl->m_pNext!=NULL) pCtrl=pCtrl->m_pNext;
		}
		for ( ; pCtrl!=NULL; pCtrl=pCtrl->m_pPrev)
		{
			if (pCtrl->m_Rect.TestPoint(m_fCurX, m_fCurY) && pCtrl->m_bEnabled)
			{
				if (pCtrl!=m_pCtrlOver)
				{
					if (m_pCtrlOver!=NULL) m_pCtrlOver->MouseOver(FALSE);
					pCtrl->MouseOver(TRUE);
					m_pCtrlOver=pCtrl;
				}
				if (ProcessCtrl(pCtrl)) return pCtrl->m_nID;
				else return 0;
			}
		}
		if (m_pCtrlOver!=NULL)
		{
			m_pCtrlOver->MouseOver(FALSE);
			m_pCtrlOver=NULL;
		}
	}

	return 0;
}

void CGUI::Render()
{
	for (CControl *p=m_pCtrlList; p!=NULL; p=p->m_pNext)
	{
		if (p->m_bVisible) p->Render();
	}
	if (m_pApp->Input_IsMouseOver() && m_psprCursor!=NULL) m_psprCursor->Render(m_fCurX, m_fCurY);
}

BOOL CGUI::ProcessCtrl(CControl *pCtrl)
{
	BOOL bResult=FALSE;

	if (m_pApp->Input_KeyDown(VK_LBUTTON))
	{
		m_pCtrlLock=pCtrl;
		SetFocus(pCtrl->m_nID);
		bResult=bResult || pCtrl->MouseLBtn(TRUE);
	}
	if (m_pApp->Input_KeyDown(VK_RBUTTON))
	{
		m_pCtrlLock=pCtrl;
		SetFocus(pCtrl->m_nID);
		bResult=bResult || pCtrl->MouseRBtn(TRUE);
	}
	if (m_pApp->Input_KeyUp(VK_LBUTTON)) bResult=bResult || pCtrl->MouseLBtn(FALSE);
	if (m_pApp->Input_KeyUp(VK_RBUTTON)) bResult=bResult || pCtrl->MouseRBtn(FALSE);
	if (m_nWheel!=m_nWheelOld)
	{
		bResult=bResult || pCtrl->MouseWheel(m_nWheel);
		m_nWheelOld=m_nWheel;
	}
	if (m_fCurX!=m_fOldX || m_fCurY!=m_fOldY)
	{
		bResult=bResult || pCtrl->MouseMove(m_fCurX-pCtrl->m_Rect.x1, m_fCurY-pCtrl->m_Rect.y1);
		m_fOldX=m_fCurX;
		m_fOldY=m_fCurY;
	}
	return bResult;
}
