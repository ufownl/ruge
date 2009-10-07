#pragma once

#define ENTER_START		0
#define ENTER_RESUME	1

#define STARCNT	40

struct STARINFO
{
	float fx, fy, fdx, fdy, fRot;
};

class CStarsScene : public RUGE::CScene
{
public:
	CStarsScene(int nID);
	virtual ~CStarsScene();

protected:
	virtual void Render();
	virtual BOOL Update(float fDelta);

	virtual BOOL Enter(WPARAM wParam, LPARAM lParam);
	virtual void Exit();

protected:
	BOOL m_bGameOver;
	float m_fRes;

	RUGE::HFONT m_hFont;
	RUGE::HTEXTURE m_hTex;
	RUGE::HAUDIO m_hMusic, m_hSound;
	RUGE::HCHANNEL m_hChannel;

	RUGE::CSprite *m_pSpr, *m_pSpt, *m_psprStar;
	RUGE::CParticleSystem *m_pPar;

	float m_fx, m_fy, m_fdx, m_fdy;
	const float m_cfSpeed;

	STARINFO m_StarInfo[STARCNT];
};
