#pragma once

#define MODE_START	0
#define MODE_RESUME	1

#define STARCNT	40

struct STARINFO
{
	float fx, fy, fdx, fdy, fRot;
};

class CStarsScene : public IScene
{
public:
	CStarsScene(PSCENE pParentScene);
	virtual ~CStarsScene();

	virtual BOOL EnterScene(WPARAM wParam, LPARAM lParam);
	virtual void ExitScene();
	virtual BOOL Update(CSceneManager *pSceneManager, float fDelta);
	virtual void Render();

protected:
	PAPPLICATION m_pApp;
	IRandomPtr m_pRand;

	int m_nState;
	float m_fRes;

	HFONTX m_hFont, m_hFontHint;
	HTEXTURE m_hTex, m_hTexBg;
	HAUDIO m_hAudioBg, m_hAudioLost;
	HCHANNEL m_hChannelBg;

	CSprite *m_pSpr, *m_pSpt, *m_pSprStar, *m_pSprBg;
	CParticleSystem *m_pPar;

	float m_fx, m_fy, m_fdx, m_fdy;
	const float m_cfSpeed;

	STARINFO m_StarInfo[STARCNT];

	PSCENE m_pParentScene;
};
