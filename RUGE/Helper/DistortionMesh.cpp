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
#include "DistortionMesh.h"

CDistortionMesh::CDistortionMesh(int nRows, int nCols)
	: m_pApp(GetRUGE(RUGE_VERSION))
	, m_nRows(nRows)
	, m_nCols(nCols)
	, m_fCellWidth(0.0f)
	, m_fCellHeight(0.0f)
	, m_fLeft(0.0f)
	, m_fTop(0.0f)
	, m_fWidth(0.0f)
	, m_fHeight(0.0f)
{
	m_quadTex.hTex=NULL;
	m_quadTex.dwBlend=BLEND_DEFAULT;
	m_pVertexArray=new VERTEX[nRows*nCols];
	for (int i=0; i<nRows*nCols; i++)
	{
		m_pVertexArray[i].x=0.0f;
		m_pVertexArray[i].y=0.0f;
		m_pVertexArray[i].z=0.5f;
		m_pVertexArray[i].rhw=1.0f;
		m_pVertexArray[i].dwColor=0xFFFFFFFF;
		m_pVertexArray[i].tu=0.0f;
		m_pVertexArray[i].tv=0.0f;
	}
}

CDistortionMesh::CDistortionMesh(const CDistortionMesh &dm)
	: m_pApp(GetRUGE(RUGE_VERSION))
	, m_nRows(dm.m_nRows)
	, m_nCols(dm.m_nCols)
	, m_fCellWidth(dm.m_fCellWidth)
	, m_fCellHeight(dm.m_fCellHeight)
	, m_fLeft(dm.m_fLeft)
	, m_fTop(dm.m_fTop)
	, m_fWidth(dm.m_fWidth)
	, m_fHeight(dm.m_fHeight)
	, m_quadTex(dm.m_quadTex)
{
	m_pVertexArray=new VERTEX[m_nRows*m_nCols];
	memcpy(m_pVertexArray, dm.m_pVertexArray, sizeof(VERTEX)*m_nRows*m_nCols);
}

CDistortionMesh::~CDistortionMesh()
{
	delete m_pVertexArray;
	m_pApp->Release();
}

CDistortionMesh& CDistortionMesh::operator = (const CDistortionMesh &dm)
{
	if (this!=&dm)
	{
		m_nRows=dm.m_nRows;
		m_nCols=dm.m_nCols;
		m_fCellWidth=dm.m_fCellWidth;
		m_fCellHeight=dm.m_fCellHeight;
		m_fLeft=dm.m_fLeft;
		m_fTop=dm.m_fTop;
		m_fWidth=dm.m_fWidth;
		m_fHeight=dm.m_fHeight;
		m_quadTex=dm.m_quadTex;
		m_pVertexArray=new VERTEX[m_nRows*m_nCols];
		memcpy(m_pVertexArray, dm.m_pVertexArray, sizeof(VERTEX)*m_nRows*m_nCols);
	}
	return *this;
}

void CDistortionMesh::Clear(DWORD dwColor/* =0xFFFFFFFF */, float z/* =0.5f */)
{
	for (int i=0; i<m_nRows; i++)
	{
		for (int j=0; j<m_nCols; j++)
		{
			int nIndex=i*m_nCols+j;

			m_pVertexArray[nIndex].x=j*m_fCellWidth;
			m_pVertexArray[nIndex].y=i*m_fCellHeight;
			m_pVertexArray[nIndex].z=z;
			m_pVertexArray[nIndex].dwColor=dwColor;
		}
	}
}

void CDistortionMesh::Render(float x, float y)
{
	for(int i=0; i<m_nRows-1; i++)
	{
		for(int j=0; j<m_nCols-1; j++)
		{
			int nIndex=i*m_nCols+j;

			m_quadTex.v[0].tu=m_pVertexArray[nIndex].tu;
			m_quadTex.v[0].tv=m_pVertexArray[nIndex].tv;
			m_quadTex.v[0].x=x+m_pVertexArray[nIndex].x;
			m_quadTex.v[0].y=y+m_pVertexArray[nIndex].y;
			m_quadTex.v[0].z=m_pVertexArray[nIndex].z;
			m_quadTex.v[0].rhw=m_pVertexArray[nIndex].rhw;
			m_quadTex.v[0].dwColor=m_pVertexArray[nIndex].dwColor;

			m_quadTex.v[1].tu=m_pVertexArray[nIndex+1].tu;
			m_quadTex.v[1].tv=m_pVertexArray[nIndex+1].tv;
			m_quadTex.v[1].x=x+m_pVertexArray[nIndex+1].x;
			m_quadTex.v[1].y=y+m_pVertexArray[nIndex+1].y;
			m_quadTex.v[1].z=m_pVertexArray[nIndex+1].z;
			m_quadTex.v[1].rhw=m_pVertexArray[nIndex+1].rhw;
			m_quadTex.v[1].dwColor=m_pVertexArray[nIndex+1].dwColor;

			m_quadTex.v[2].tu=m_pVertexArray[nIndex+m_nCols+1].tu;
			m_quadTex.v[2].tv=m_pVertexArray[nIndex+m_nCols+1].tv;
			m_quadTex.v[2].x=x+m_pVertexArray[nIndex+m_nCols+1].x;
			m_quadTex.v[2].y=y+m_pVertexArray[nIndex+m_nCols+1].y;
			m_quadTex.v[2].z=m_pVertexArray[nIndex+m_nCols+1].z;
			m_quadTex.v[2].rhw=m_pVertexArray[nIndex+m_nCols+1].rhw;
			m_quadTex.v[2].dwColor=m_pVertexArray[nIndex+m_nCols+1].dwColor;

			m_quadTex.v[3].tu=m_pVertexArray[nIndex+m_nCols].tu;
			m_quadTex.v[3].tv=m_pVertexArray[nIndex+m_nCols].tv;
			m_quadTex.v[3].x=x+m_pVertexArray[nIndex+m_nCols].x;
			m_quadTex.v[3].y=y+m_pVertexArray[nIndex+m_nCols].y;
			m_quadTex.v[3].z=m_pVertexArray[nIndex+m_nCols].z;
			m_quadTex.v[3].rhw=m_pVertexArray[nIndex+m_nCols].rhw;
			m_quadTex.v[3].dwColor=m_pVertexArray[nIndex+m_nCols].dwColor;

			m_pApp->Gfx_RenderQuad(&m_quadTex);
		}
	}
}

void CDistortionMesh::SetTexture(HTEXTURE hTex)
{
	m_quadTex.hTex=hTex;
}

void CDistortionMesh::SetTextureRect(float x, float y, float w, float h)
{
	m_fLeft=x;
	m_fTop=y;
	m_fWidth=w;
	m_fHeight=h;
	m_fCellWidth=w/(m_nCols-1);
	m_fCellHeight=h/(m_nRows-1);

	float tw, th;

	if (m_quadTex.hTex==NULL)
	{
		tw=w;
		th=h;
	}
	else
	{
		tw=(float)m_pApp->Texture_GetWidth(m_quadTex.hTex);
		th=(float)m_pApp->Texture_GetHeight(m_quadTex.hTex);
	}
	for (int i=0; i<m_nRows; i++)
	{
		for (int j=0; j<m_nCols; j++)
		{
			int nIndex=i*m_nCols+j;

			m_pVertexArray[nIndex].x=j*m_fCellWidth;
			m_pVertexArray[nIndex].y=i*m_fCellHeight;
			m_pVertexArray[nIndex].tu=(x+m_pVertexArray[nIndex].x)/tw;
			m_pVertexArray[nIndex].tv=(y+m_pVertexArray[nIndex].y)/th;
		}
	}
}

void CDistortionMesh::SetBlendMode(DWORD dwBlend)
{
	m_quadTex.dwBlend=dwBlend;
}

void CDistortionMesh::SetZ(int nRow, int nCol, float z)
{
	if (0<=nRow && nRow<m_nRows && 0<=nCol && nCol<m_nCols) m_pVertexArray[nRow*m_nCols+nCol].z=z;
}

void CDistortionMesh::SetColor(int nRow, int nCol, DWORD dwColor)
{
	if (0<=nRow && nRow<m_nRows && 0<=nCol && nCol<m_nCols) m_pVertexArray[nRow*m_nCols+nCol].dwColor=dwColor;
}

void CDistortionMesh::SetDisplacement(int nRow, int nCol, float dx, float dy, DWORD dwMode)
{
	if (0<=nRow && nRow<m_nRows && 0<=nCol && nCol<m_nCols)
	{
		switch(dwMode)
		{
		case DISP_NODE:
			dx+=nCol*m_fCellWidth;
			dy+=nRow*m_fCellHeight;
			break;
		case DISP_CENTER:
			dx+=m_fCellWidth*(m_nCols-1)/2;
			dy+=m_fCellHeight*(m_nRows-1)/2;
			break;
		case DISP_TOPLEFT:
			break;
		}

		int nIndex=nRow*m_nCols+nCol;

		m_pVertexArray[nIndex].x=dx;
		m_pVertexArray[nIndex].y=dy;
	}
}

HTEXTURE CDistortionMesh::GetTexture() const
{
	return m_quadTex.hTex;
}

void CDistortionMesh::GetTextureRect(float &x, float &y, float &w, float &h) const
{
	x=m_fLeft;
	y=m_fTop;
	w=m_fWidth;
	h=m_fHeight;
}

DWORD CDistortionMesh::GetBlendMode() const
{
	return m_quadTex.dwBlend;
}

float CDistortionMesh::GetZ(int nRow, int nCol) const
{
	if (0<=nRow && nRow<m_nRows && 0<=nCol && nCol<m_nCols) return m_pVertexArray[nRow*m_nCols+nCol].z;
	return 0.0f;
}

DWORD CDistortionMesh::GetColor(int nRow, int nCol) const
{
	if (0<=nRow && nRow<m_nRows && 0<=nCol && nCol<m_nCols) return m_pVertexArray[nRow*m_nCols+nCol].dwColor;
	return 0;
}

void CDistortionMesh::GetDisplacement(int nRow, int nCol, float &dx, float &dy, DWORD dwMode) const
{
	if (0<=nRow && nRow<m_nRows && 0<=nCol && nCol<m_nCols)
	{
		int nIndex=nRow*m_nCols+nCol;

		switch(dwMode)
		{
		case DISP_NODE:
			dx=m_pVertexArray[nIndex].x-nCol*m_fCellWidth;
			dy=m_pVertexArray[nIndex].y-nRow*m_fCellHeight;
			break;
		case DISP_CENTER:
			dx=m_pVertexArray[nIndex].x-m_fCellWidth*(m_nCols-1)/2;
			dy=m_pVertexArray[nIndex].x-m_fCellHeight*(m_nRows-1)/2;
			break;
		case DISP_TOPLEFT:
			dx=m_pVertexArray[nIndex].x;
			dy=m_pVertexArray[nIndex].y;
			break;
		}
	}
}

int CDistortionMesh::GetRows() const
{
	return m_nRows;
}

int CDistortionMesh::GetCols() const
{
	return m_nCols;
}