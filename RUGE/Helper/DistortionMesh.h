#pragma once

#ifndef _DISTORTIONMESH_H_
#define _DISTORTIONMESH_H_

#define DISP_NODE		0
#define DISP_CENTER		1
#define DISP_TOPLEFT	2

class CDistortionMesh
{
public:
	CDistortionMesh(int nRows, int nCols);
	CDistortionMesh(const CDistortionMesh &dm);
	virtual ~CDistortionMesh();

	CDistortionMesh& operator = (const CDistortionMesh &dm);

	void Clear(DWORD dwColor=0xFFFFFFFF, float z=0.5f);
	void Render(float x, float y);

	void SetTexture(HTEXTURE hTex);
	void SetTextureRect(float x, float y, float w, float h);
	void SetBlendMode(DWORD dwBlend);
	void SetZ(int nRow, int nCol, float z);
	void SetColor(int nRow, int nCol, DWORD dwColor);
	void SetDisplacement(int nCol, int nRow, float dx, float dy, DWORD dwMode);

	HTEXTURE GetTexture() const;
	void GetTextureRect(float &x, float &y, float &w, float &h) const;
	DWORD GetBlendMode() const;
	float GetZ(int nRow, int nCol) const;
	DWORD GetColor(int nRow, int nCol) const;
	void GetDisplacement(int nCol, int nRow, float &dx, float &dy, DWORD dwMode) const;
	int GetRows() const;
	int GetCols() const;

protected:
	PAPPLICATION m_pApp;
	VERTEX *m_pVertexArray;
	int	m_nRows, m_nCols;
	float m_fCellWidth, m_fCellHeight, m_fLeft, m_fTop, m_fWidth, m_fHeight;
	QUAD m_quadTex;
};

#endif  // _DISTORTIONMESH_H_
