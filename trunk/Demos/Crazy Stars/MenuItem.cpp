#include "StdAfx.h"
#include "MenuItem.h"

CMenuItem::CMenuItem(int nID, HFONTX hFont, HAUDIO hSound, float x, float y, float fDelay, LPSTR lpcszTitle)
	: CControl(nID)
	, m_hFont(hFont)
	, m_hSound(hSound)
	, m_fDelay(fDelay)
	, m_lpcszTitle(lpcszTitle)
	, m_fOffsetSrc(0)
	, m_fOffsetDelta(0)
	, m_fOffset(0)
	, m_fTime(-1)
	, m_fTime2(-1)
{
	m_colColor.SetColor(0xFFFFE060);
	m_colShadow.SetColor(0x30000000);

	m_bStatic=FALSE;
	m_bVisible=TRUE;
	m_bEnabled=TRUE;

	RECT rect={0, 0, 0, 0};

	m_pApp->Font_DrawText(m_hFont, m_lpcszTitle, &rect, 0, DT_CALCRECT);
	m_Rect.Set(x-(float)rect.right/2, y, x+(float)rect.right/2, y+rect.bottom);
}

CMenuItem::~CMenuItem()
{
}

void CMenuItem::Render()
{
	RECT rect={(LONG)m_Rect.x1+(LONG)m_fOffset+3, (LONG)m_Rect.y1+3, 0, 0};

	m_pApp->Font_DrawText(m_hFont, m_lpcszTitle, &rect, 0, DT_CALCRECT);
	m_pApp->Font_DrawText(m_hFont, m_lpcszTitle, &rect, 0, DT_TOP|DT_LEFT, m_colShadow.GetColor());
	rect.left=(LONG)m_Rect.x1-(LONG)m_fOffset;
	rect.top=(LONG)m_Rect.y1-(LONG)m_fOffset;
	m_pApp->Font_DrawText(m_hFont, m_lpcszTitle, &rect, 0, DT_CALCRECT);
	m_pApp->Font_DrawText(m_hFont, m_lpcszTitle, &rect, 0, DT_TOP|DT_LEFT, m_colColor.GetColor());
}

void CMenuItem::Update(float fDelta)
{
	if (m_fTime2!=-1)
	{
		m_fTime2+=fDelta;
		if (m_fTime2>=m_fDelay+0.1f)
		{
			m_colColor=m_colSrc2+m_colDelta2;
			m_colShadow=m_colShadowSrc+m_colShadowDelta;
			m_fOffset=0;
			m_fTime2=-1;
		}
		else
		{
			if (m_fTime2<m_fDelay)
			{
				m_colColor=m_colSrc2;
				m_colShadow=m_colShadowSrc;
			}
			else
			{
				m_colColor=m_colSrc2+m_colDelta2*(m_fTime2-m_fDelay)*10;
				m_colShadow=m_colShadowSrc+m_colShadowDelta*(m_fTime2-m_fDelay)*10;
			}
		}
	}
	else if (m_fTime!=-1)
	{
		m_fTime+=fDelta;
		if (m_fTime>=0.2f)
		{
			m_colColor=m_colSrc+m_colDelta;
			m_fOffset=m_fOffsetSrc+m_fOffsetDelta;
			m_fTime=-1.0f;
		}
		else
		{
			m_colColor=m_colSrc+m_colDelta*m_fTime*5;
			m_fOffset=m_fOffsetSrc+m_fOffsetDelta*m_fTime*5;
		}
	}
}

void CMenuItem::Enter()
{
	CColor colTemp;

	m_colSrc2.SetColor(0x00FFE060);
	colTemp.SetColor(0xFFFFE060);
	m_colDelta2=colTemp-m_colSrc2;
	m_colShadowSrc.SetColor(0x00000000);
	colTemp.SetColor(0x30000000);
	m_colShadowDelta=colTemp-m_colShadowSrc;
	m_fTime2=0.0f;
}

void CMenuItem::Exit()
{
	CColor colTemp;

	m_colSrc2.SetColor(0xFFFFE060);
	colTemp.SetColor(0x00FFE060);
	m_colDelta2=colTemp-m_colSrc2;
	m_colShadowSrc.SetColor(0x30000000);
	colTemp.SetColor(0x00000000);
	m_colShadowDelta=colTemp-m_colShadowSrc;
	m_fTime2=0.0f;
}

BOOL CMenuItem::IsDone()
{
	if (m_fTime2==-1.0f) return TRUE;
	else return FALSE;
}

void CMenuItem::Focus(BOOL bFocused)
{
	CColor colTemp;
	
	if(bFocused)
	{
		m_pApp->Effect_Play(m_hSound);
		m_colSrc.SetColor(0xFFFFE060);
		colTemp.SetColor(0xFFFFFFFF);
		m_fOffsetSrc=0;
		m_fOffsetDelta=4;
	}
	else
	{
		m_colSrc.SetColor(0xFFFFFFFF);
		colTemp.SetColor(0xFFFFE060);
		m_fOffsetSrc=4;
		m_fOffsetDelta=-4;
	}
	m_colDelta=colTemp-m_colSrc;
	m_fTime=0.0f;
}

void CMenuItem::MouseOver(BOOL bOver)
{
	if (bOver) m_pGUI->SetFocus(m_nID);
}

BOOL CMenuItem::MouseLBtn(BOOL bDown)
{
	if (bDown)
	{
		m_pApp->Effect_Play(m_hSound);
		m_fOffset=0;
		return FALSE;
	}
	else
	{
		m_fOffset=4;
		return TRUE;
	}
}

BOOL CMenuItem::KeyClick(int nVKey, char chChar)
{
	if (nVKey==VK_RETURN)
	{
		MouseLBtn(TRUE);
		return MouseLBtn(FALSE);
	}
	return FALSE;
}
