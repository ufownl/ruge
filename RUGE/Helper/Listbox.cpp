#include "StdAfx.h"
#include "Listbox.h"

namespace RUGE
{

	CListbox::CListbox(int nID, float x, float y, float w, float h, HFONT hFont, DWORD dwTextColor, DWORD dwTextHLColor, DWORD dwHLColor)
		: CControl(nID)
		, m_hFont(hFont)
		, m_dwTextColor(dwTextColor)
		, m_dwTextHLColor(dwTextHLColor)
		, m_dwHLColor(dwHLColor)
		, m_nItems(0)
		, m_nSelected(0)
		, m_nTop(0)
		, m_nRowHeight(0)
		, m_nRows(0)
		, m_nWheel(0)
		, m_psprHighlight(NULL)
		, m_pItemList(NULL)
	{
		m_bStatic=FALSE;
		m_bVisible=TRUE;
		m_bEnabled=TRUE;
		m_Rect.Set(x, y, x+w, y+h);

		RECT rect={0, 0, 0, 0};

		m_pApp->Font_DrawText(hFont, "RUGE", &rect, 0, DT_CALCRECT);
		m_nRowHeight=rect.bottom;
		m_nRows=(int)h/m_nRowHeight;
		m_psprHighlight=new CSprite(NULL, 0, 0, w, (float)m_nRowHeight);
	}

	CListbox::~CListbox()
	{
		Clear();
		delete m_psprHighlight;
	}

	int CListbox::AddItem(LPCSTR lpcszItem)
	{
		PLISTBOXITEM pNew=new LISTBOXITEM;

		strcpy(pNew->szText, lpcszItem);
		pNew->pNext=NULL;

		PLISTBOXITEM pItem=m_pItemList, pPrev=NULL;

		while (pItem!=NULL)
		{
			pPrev=pItem;
			pItem=pItem->pNext;
		}
		if (pPrev!=NULL) pPrev->pNext=pNew;
		else m_pItemList=pNew;
		return m_nItems++;
	}

	void CListbox::DelItem(int n)
	{
		if (n<0 || n>=m_nItems) return;

		PLISTBOXITEM pItem=m_pItemList, pPrev=NULL;

		for (int i=0; i<n; i++)
		{
			pPrev=pItem;
			pItem=pItem->pNext;
		}
		if(pPrev!=NULL) pPrev->pNext=pItem->pNext;
		else m_pItemList=pItem->pNext;
		delete pItem;
		m_nItems--;
	}

	void CListbox::SetSelected(int n)
	{
		if (0<=n && n<m_nItems) m_nSelected=n;
	}

	void CListbox::SetTop(int n)
	{
		if (0<=n && n<m_nItems) m_nTop=n;
	}

	void CListbox::SetItemText(int n, LPCSTR lpcszItem)
	{
		if (n<0 || n>=m_nItems) return;

		PLISTBOXITEM pItem=m_pItemList;

		for (int i=0; i<n; i++) pItem=pItem->pNext;
		strcpy(pItem->szText, lpcszItem);
	}

	int CListbox::GetSelected() const
	{
		return m_nSelected;
	}

	int CListbox::GetTop() const
	{
		return m_nTop;
	}

	LPCSTR CListbox::GetItemText(int n) const
	{
		if (n<0 || n>=m_nItems) return NULL;

		PLISTBOXITEM pItem=m_pItemList;

		for (int i=0; i<n; i++) pItem=pItem->pNext;
		return pItem->szText;
	}

	int CListbox::GetNumItems() const
	{
		return m_nItems;
	}

	int CListbox::GetNumRows() const
	{
		return m_nRows;
	}

	void CListbox::Clear()
	{
		for (PLISTBOXITEM p=m_pItemList; p!=NULL; )
		{
			PLISTBOXITEM pDel=p;

			p=p->pNext;
			delete pDel;
		}
		m_nItems=0;
		m_nSelected=0;
		m_nTop=0;
		m_pItemList=NULL;
	}

	void CListbox::Render()
	{
		PLISTBOXITEM pItem=m_pItemList;

		for (int i=0; i<m_nTop; i++) pItem=pItem->pNext;
		for (int i=0; i<m_nRows; i++)
		{
			if (i>=m_nItems) break;

			RECT rect={(LONG)m_Rect.x1+3, (LONG)m_Rect.y1+i*m_nRowHeight, (LONG)m_Rect.x2-3, (LONG)m_Rect.y1+(i+1)*m_nRowHeight};

			if (m_nTop+i==m_nSelected)
			{
				m_psprHighlight->SetColor(m_dwHLColor&m_dwColor);
				m_psprHighlight->Render(m_Rect.x1, m_Rect.y1+i*m_nRowHeight);
				m_pApp->Font_DrawText(m_hFont, pItem->szText, &rect, 0, DT_LEFT|DT_TOP, m_dwTextHLColor&m_dwColor);
			}
			else m_pApp->Font_DrawText(m_hFont, pItem->szText, &rect, 0, DT_LEFT|DT_TOP, m_dwTextColor&m_dwColor);
			pItem=pItem->pNext;
		}
	}

	BOOL CListbox::MouseLBtn(BOOL bDown, float x, float y)
	{
		if (bDown)
		{
			int n=m_nTop+(int)y/m_nRowHeight;

			if (n<m_nItems)
			{
				m_nSelected=n;
				return TRUE;
			}
		}
		return FALSE;
	}

	void CListbox::MouseOver(BOOL bOver)
	{
		if (bOver) m_nWheel=m_pApp->Input_GetMouseWheel();
	}

	BOOL CListbox::MouseWheel(SHORT nWheel)
	{
		m_nTop+=m_nWheel-nWheel;
		m_nWheel=nWheel;
		if (m_nTop<0) m_nTop=0;
		if (m_nTop>m_nItems-m_nRows) m_nTop=m_nItems-m_nRows;
		return TRUE;
	}

	BOOL CListbox::KeyClick(int nVKey, char chChar)
	{
		switch (nVKey)
		{
		case VK_DOWN:
			if (m_nSelected<m_nItems-1)
			{
				m_nSelected++;
				if (m_nSelected>m_nTop+m_nRows-1) m_nTop=m_nSelected-m_nRows+1;
				return TRUE;
			}
			break;
		case VK_UP:
			if (m_nSelected>0)
			{
				m_nSelected--;
				if (m_nSelected<m_nTop) m_nTop=m_nSelected;
				return TRUE;
			}
			break;
		}
		return FALSE;
	}

}