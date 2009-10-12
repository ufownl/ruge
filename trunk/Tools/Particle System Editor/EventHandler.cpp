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

#include "StdAfx.h"
#include "EventHandler.h"

#define PARTICLE_SIZE	32

#define ButtonGetState(nID)			((RUGE::CButton*)m_pGUI->GetCtrl(nID))->GetState()
#define ButtonSetState(nID, bState)	((RUGE::CButton*)m_pGUI->GetCtrl(nID))->SetState(bState)
#define SliderGetValue(nID)			((RUGE::CSlider*)m_pGUI->GetCtrl(nID))->GetValue()
#define SliderSetValue(nID, fVal)	((RUGE::CSlider*)m_pGUI->GetCtrl(nID))->SetValue(fVal)
#define GetTextCtrl(nID)			((RUGE::CText*)m_pGUI->GetCtrl(nID))

#define CMD_EXIT				1
#define CMD_HELP				2
#define CMD_PRESET1				3
#define CMD_PRESET2				4
#define CMD_PRESET3				5
#define CMD_PRESET4				6
#define CMD_PRESET5				7
#define CMD_PRESET6				8
#define CMD_PRESET7				9
#define CMD_PRESET8				10
#define CMD_PRESET9				11
#define CMD_BOUNDINGBOX			12
#define CMD_NPARTICLES			13
#define CMD_FPS					14

#define CMD_SYS_LIFETIME		15
#define CMD_SYS_TLIFETIME		16
#define CMD_SYS_LIFECONT		17
#define CMD_SYS_EMISSION		18
#define CMD_SYS_TEMISSION		19
#define CMD_SYS_PARLIFETIMEMIN	20
#define CMD_SYS_PARLIFETIMEMAX	21
#define CMD_SYS_PARLIFETIMELOCK	22
#define CMD_SYS_BLENDADDITIVE	23
#define CMD_SYS_BLENDBLEND		24
#define CMD_SYS_TEXTURE			25

#define CMD_PM_DIRECTION		26
#define CMD_PM_TDIRECTION		27
#define CMD_PM_RELATIVE			28
#define CMD_PM_SPREAD			29
#define CMD_PM_TSPREAD			30

#define CMD_PM_STARTSPEEDMIN	31
#define CMD_PM_STARTSPEEDMAX	32
#define CMD_PM_STARTSPEEDLOCK	33

#define CMD_PM_GRAVITYMIN		34
#define CMD_PM_GRAVITYMAX		35
#define CMD_PM_GRAVITYLOCK		36

#define CMD_PM_RADIALMIN		37
#define CMD_PM_RADIALMAX		38
#define CMD_PM_RADIALLOCK		39

#define CMD_PM_TANGENTIALMIN	40
#define CMD_PM_TANGENTIALMAX	41
#define CMD_PM_TANGENTIALLOCK	42

#define CMD_PA_SIZESTART		43
#define CMD_PA_SIZEEND			44
#define CMD_PA_SIZEVAR			45
#define CMD_PA_SIZELOCK			46

#define CMD_PA_SPINSTART		47
#define CMD_PA_SPINEND			48
#define CMD_PA_SPINVAR			49
#define CMD_PA_SPINLOCK			50

#define CMD_PA_ALPHASTART		51
#define CMD_PA_ALPHAEND			52
#define CMD_PA_ALPHAVAR			53
#define CMD_PA_ALPHALOCK		54

#define CMD_PA_RSTART			55
#define CMD_PA_GSTART			56
#define CMD_PA_BSTART			57
#define CMD_PA_REND				58
#define CMD_PA_GEND				59
#define CMD_PA_BEND				60
#define CMD_PA_RGBVAR			61

CEventHandler::CEventHandler()
	: m_pApp(RUGE::GetRUGE())
	, m_hFont(NULL)
	, m_htexGUI(NULL)
	, m_htexPar(NULL)
	, m_psprLPane1(NULL)
	, m_psprLPane2(NULL)
	, m_psprRPane1(NULL)
	, m_psprRPane2(NULL)
	, m_psprCursor(NULL)
	, m_psprColor(NULL)
	, m_psprBBox(NULL)
	, m_panimPar(NULL)
	, m_pParsys(NULL)
	, m_pGUI(NULL)
	, m_bHelp(FALSE)
	, m_bBBox(FALSE)
	, m_bIFace(TRUE)
	, m_bVSync(TRUE)
	, m_nPreset(1)
	, m_fPsx(400)
	, m_fPsy(300)
{
}

CEventHandler::~CEventHandler()
{
	m_pApp->Release();
}

HRESULT CEventHandler::InitResource()
{
	// 在此添加资源初始化代码
	m_hFont=m_pApp->Font_Create(16, 0, 0, FALSE, "微软雅黑");
	m_htexGUI=m_pApp->Texture_Load("Res\\GUI.png");
	m_htexPar=m_pApp->Texture_Load("Res\\Particles.png");

	m_psprLPane1=new RUGE::CSprite(m_htexGUI, 0, 0, 168, 512);
	m_psprLPane2=new RUGE::CSprite(m_htexGUI, 336, 0, 168, 88);
	m_psprRPane1=new RUGE::CSprite(m_htexGUI, 168, 0, 168, 512);
	m_psprRPane2=new RUGE::CSprite(m_htexGUI, 336, 88, 168, 88);

	m_psprCursor=new RUGE::CSprite(m_htexGUI, 487, 181, 19, 26);
	m_psprColor=new RUGE::CSprite(m_htexGUI, 466, 208, 14, 80);
	m_psprBBox=new RUGE::CSprite(m_htexGUI, 337, 209, 128, 128);

	m_panimPar=new RUGE::CAnimation(m_htexPar, 16, 1, 0, 0, 32, 32);
	m_panimPar->SetHotSpot(16, 16);

	RUGE::PARTICLESYSTEMINFO psi;

	memset(&psi, 0, sizeof(RUGE::PARTICLESYSTEMINFO));
	psi.pSprite=m_panimPar;
	m_pParsys=new RUGE::CParticleSystem(&psi);
	m_pParsys->TrackBoundingBox(TRUE);
	m_pParsys->MoveTo(m_fPsx, m_fPsy);

	m_pGUI=new RUGE::CGUI;
	CreateGUI();

	m_bHelp=FALSE;
	m_bBBox=FALSE;
	m_bIFace=TRUE;
	m_bVSync=TRUE;
	m_nPreset=1;
	m_fPsx=400;
	m_fPsy=300;

	LoadPreset(m_nPreset);

	return S_OK;  // 返回S_OK表示资源初始化成功
}

void CEventHandler::ReleaseResource()
{
	// 在此添加资源释放代码
	// 引擎内部管理系统可以自动释放纹理、字体及声音资源
	SavePreset(m_nPreset);

	delete m_pGUI;
	delete m_pParsys;
	delete m_panimPar;
	delete m_psprBBox;
	delete m_psprColor;
	delete m_psprCursor;
	delete m_psprRPane2;
	delete m_psprRPane1;
	delete m_psprLPane2;
	delete m_psprLPane1;
}

// float fDelta: 上一帧和当前帧的时间间隔，以秒为单位
BOOL CEventHandler::Frame(float fDelta)
{
	// 在此添加游戏逻辑控制代码
	float x, y;

	m_pApp->Input_GetMousePos(&x, &y);
	if (m_pApp->Input_KeyPressed(VK_RBUTTON))
	{
		m_pGUI->SetCursor(NULL);
		m_fPsx=x;
		m_fPsy=y;
		if (m_bIFace)
		{
			if (m_fPsx<168) m_fPsx=168;
			if (m_fPsx>631) m_fPsx=631;
		}
		if (m_fPsx<0) m_fPsx=0;
		if (m_fPsx>800) m_fPsx=800;
		if (m_fPsy<0) m_fPsy=0;
		if (m_fPsy>600) m_fPsy=600;
	}
	else
	{
		m_pGUI->SetCursor(m_psprCursor);
		m_fPsx=400;
		m_fPsy=300;
	}
	if (HandleKey(m_pApp->Input_GetKey())) return TRUE;

	float psx, psy;

	m_pParsys->GetPosition(&psx, &psy);
	m_pParsys->MoveTo(psx+(m_fPsx-psx)*10*fDelta, psy+(m_fPsy-psy)*10*fDelta);
	m_pParsys->Update(fDelta);

	if (m_bIFace)
	{
		char szBuf[256];

		if (HandleCommand(m_pGUI->Update(fDelta))) return TRUE;
		sprintf(szBuf, "%d", m_pParsys->GetParticlesAlive());
		GetTextCtrl(CMD_NPARTICLES)->SetText(szBuf);
		sprintf(szBuf, "%d", m_pApp->Timer_GetFPS());
		GetTextCtrl(CMD_FPS)->SetText(szBuf);
	}

	return FALSE;  // 返回FALSE表示游戏未结束
}

void CEventHandler::Render()
{
	// 在此添加渲染代码
	m_pApp->Gfx_Clear();
	m_pParsys->Render();
	if (m_bBBox)
	{
		RUGE::CRect rect;

		m_pParsys->GetBoundingBox(&rect);
		if (!rect.IsClean()) m_psprBBox->RenderStretch(rect.x1, rect.y1, rect.x2, rect.y2);
	}
	if (m_bIFace)
	{
		m_psprLPane1->Render(0, 0);
		m_psprLPane2->Render(0, 512);
		m_psprRPane1->Render(632, 0);
		m_psprRPane2->Render(632, 512);
		m_panimPar->SetColor(m_pParsys->m_Info.colColorStart.GetColor()|0xFF000000);
		m_panimPar->Render(26, 189);
		m_psprColor->Render(642, 221);
		m_pGUI->Render();
	}
	if (m_bHelp)
	{
		static char szBuf[]="鼠标左键 - 打开粒子系统\n鼠标右键 - 使粒子系统跟随鼠标移动\n\n\
							数字键 1 到 9 - 选择Preset\nPreset将会自动读取和存储\n\nTAB - 隐藏编辑器界面\n\
							Alt+Enter - 全屏\\窗口模式切换\n\
							Alt+V - 关闭\\开启垂直同步\n\
							Esc - 退出";
		RECT rect={189, 18, 0, 0};

		m_pApp->Font_DrawText(m_hFont, szBuf, &rect, 0, DT_CALCRECT);
		m_pApp->Font_DrawText(m_hFont, szBuf, &rect);
	}
}

// int nPitch: 图像中一行像素点在缓冲区中所占空间的字节数
// void *pBits: 即将渲染到屏幕的图像数据缓冲区指针，一个像素点占4个字节，格
//              如下：0xAARRGGBB
void CEventHandler::Pretreat(int nPitch, void *pBits)
{
	// 在此添加图像预处理代码
}

// UINT uMsg: WINDOWS消息代码
// WPARAM wParam: WINDOWS消息WPARAM参数
// LPARAM lParam: WINDOWS消息LPARAM参数
void CEventHandler::WndEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 在此添加窗口消息处理代码
	switch (uMsg)
	{
	case WM_SYSKEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			m_pApp->System_SetState(RUGE::APP_WINDOWED, !m_pApp->System_GetState(RUGE::APP_WINDOWED));
			break;
		case 'V':
			m_bVSync=!m_bVSync;
			if (m_bVSync) m_pApp->System_SetState(RUGE::APP_VSYNC, VSYNC_ONE);
			else m_pApp->System_SetState(RUGE::APP_VSYNC, VSYNC_IMMEDIATE);
			break;
		}
		break;
	}
}

void CEventHandler::CreateGUI()
{
	RUGE::CButton *pBtn;
	RUGE::CSlider *pSlider;
	RUGE::CText *pText;

	// Presets & stuff
	m_pGUI->AddCtrl(new RUGE::CButton(CMD_EXIT, 718, 484, 73, 17, m_htexGUI, 336, 191));
	pBtn=new RUGE::CButton(CMD_HELP, 641, 484, 73, 17, m_htexGUI, 336, 191);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);

	pBtn=new RUGE::CButton(CMD_PRESET1, 641, 389, 16, 15, m_htexGUI, 384, 176);
	pBtn->SetMode(TRUE);
	pBtn->SetState(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pBtn=new RUGE::CButton(CMD_PRESET2, 657, 389, 16, 15, m_htexGUI, 384, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pBtn=new RUGE::CButton(CMD_PRESET3, 673, 389, 16, 15, m_htexGUI, 384, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pBtn=new RUGE::CButton(CMD_PRESET4, 689, 389, 16, 15, m_htexGUI, 384, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pBtn=new RUGE::CButton(CMD_PRESET5, 705, 389, 16, 15, m_htexGUI, 384, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pBtn=new RUGE::CButton(CMD_PRESET6, 721, 389, 16, 15, m_htexGUI, 384, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pBtn=new RUGE::CButton(CMD_PRESET7, 737, 389, 16, 15, m_htexGUI, 384, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pBtn=new RUGE::CButton(CMD_PRESET8, 753, 389, 16, 15, m_htexGUI, 384, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pBtn=new RUGE::CButton(CMD_PRESET9, 769, 389, 16, 15, m_htexGUI, 384, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);

	pBtn=new RUGE::CButton(CMD_BOUNDINGBOX, 641, 417, 8, 8, m_htexGUI, 368, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);

	// System parameters
	pSlider=new RUGE::CSlider(CMD_SYS_LIFETIME, 10, 44, 149, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 10, SLIDER_BAR);
	pSlider->SetValue(5);
	m_pGUI->AddCtrl(pSlider);
	pBtn=new RUGE::CButton(CMD_SYS_LIFECONT, 9, 55, 8, 8, m_htexGUI, 368, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);

	pSlider=new RUGE::CSlider(CMD_SYS_EMISSION, 10, 91, 149, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1000, SLIDER_BAR);
	pSlider->SetValue(500);
	m_pGUI->AddCtrl(pSlider);

	pBtn=new RUGE::CButton(CMD_SYS_PARLIFETIMELOCK, 144, 111, 16, 11, m_htexGUI, 336, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pSlider=new RUGE::CSlider(CMD_SYS_PARLIFETIMEMIN, 33, 126, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 5, SLIDER_BAR);
	pSlider->SetValue(2.5);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_SYS_PARLIFETIMEMAX, 33, 138, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 5, SLIDER_BAR);
	pSlider->SetValue(2.5);
	m_pGUI->AddCtrl(pSlider);

	pBtn=new RUGE::CButton(CMD_SYS_BLENDADDITIVE, 72, 174, 8, 8, m_htexGUI, 368, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pBtn=new RUGE::CButton(CMD_SYS_BLENDBLEND, 72, 188, 8, 8, m_htexGUI, 368, 176);
	pBtn->SetMode(TRUE);
	pBtn->SetState(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pBtn=new RUGE::CButton(CMD_SYS_TEXTURE, 10, 173, 32, 32, m_htexGUI, 336, 338);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);

	// Particle movement
	pSlider=new RUGE::CSlider(CMD_PM_DIRECTION, 9, 267, 149, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 2*M_PI, SLIDER_BAR);
	pSlider->SetValue(M_PI);
	m_pGUI->AddCtrl(pSlider);
	pBtn=new RUGE::CButton(CMD_PM_RELATIVE, 8, 278, 8, 8, m_htexGUI, 368, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);

	pSlider=new RUGE::CSlider(CMD_PM_SPREAD, 9, 314, 149, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 2*M_PI, SLIDER_BAR);
	pSlider->SetValue(M_PI);
	m_pGUI->AddCtrl(pSlider);

	pBtn=new RUGE::CButton(CMD_PM_STARTSPEEDLOCK, 143, 334, 16, 11, m_htexGUI, 336, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pSlider=new RUGE::CSlider(CMD_PM_STARTSPEEDMIN, 32, 349, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(-300, 300, SLIDER_BARRELATIVE);
	pSlider->SetValue(0);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PM_STARTSPEEDMAX, 32, 361, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(-300, 300, SLIDER_BARRELATIVE);
	pSlider->SetValue(0);
	m_pGUI->AddCtrl(pSlider);

	pBtn=new RUGE::CButton(CMD_PM_GRAVITYLOCK, 143, 381, 16, 11, m_htexGUI, 336, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pSlider=new RUGE::CSlider(CMD_PM_GRAVITYMIN, 32, 396, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(-900, 900, SLIDER_BARRELATIVE);
	pSlider->SetValue(0);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PM_GRAVITYMAX, 32, 408, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(-900, 900, SLIDER_BARRELATIVE);
	pSlider->SetValue(0);
	m_pGUI->AddCtrl(pSlider);

	pBtn=new RUGE::CButton(CMD_PM_RADIALLOCK, 143, 428, 16, 11, m_htexGUI, 336, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pSlider=new RUGE::CSlider(CMD_PM_RADIALMIN, 32, 443, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(-900, 900, SLIDER_BARRELATIVE);
	pSlider->SetValue(0);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PM_RADIALMAX, 32, 455, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(-900, 900, SLIDER_BARRELATIVE);
	pSlider->SetValue(0);
	m_pGUI->AddCtrl(pSlider);

	pBtn=new RUGE::CButton(CMD_PM_TANGENTIALLOCK, 143, 475, 16, 11, m_htexGUI, 336, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pSlider=new RUGE::CSlider(CMD_PM_TANGENTIALMIN, 32, 490, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(-900, 900, SLIDER_BARRELATIVE);
	pSlider->SetValue(0);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PM_TANGENTIALMAX, 32, 502, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(-900, 900, SLIDER_BARRELATIVE);
	pSlider->SetValue(0);
	m_pGUI->AddCtrl(pSlider);

	// Particle appearance
	pBtn=new RUGE::CButton(CMD_PA_SIZELOCK, 775, 29, 16, 11, m_htexGUI, 336, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pSlider=new RUGE::CSlider(CMD_PA_SIZESTART, 664, 44, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(1, 100, SLIDER_BAR);
	pSlider->SetValue(32);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PA_SIZEEND, 664, 56, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(1, 100, SLIDER_BAR);
	pSlider->SetValue(32);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PA_SIZEVAR, 664, 68, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1, SLIDER_BAR);
	pSlider->SetValue(0.5);
	m_pGUI->AddCtrl(pSlider);

	pBtn=new RUGE::CButton(CMD_PA_SPINLOCK, 775, 88, 16, 11, m_htexGUI, 336, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pSlider=new RUGE::CSlider(CMD_PA_SPINSTART, 664, 103, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(-50, 50, SLIDER_BARRELATIVE);
	pSlider->SetValue(0);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PA_SPINEND, 664, 115, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(-50, 50, SLIDER_BARRELATIVE);
	pSlider->SetValue(0);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PA_SPINVAR, 664, 127, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1, SLIDER_BAR);
	pSlider->SetValue(0.5);
	m_pGUI->AddCtrl(pSlider);

	pBtn=new RUGE::CButton(CMD_PA_ALPHALOCK, 775, 147, 16, 11, m_htexGUI, 336, 176);
	pBtn->SetMode(TRUE);
	m_pGUI->AddCtrl(pBtn);
	pSlider=new RUGE::CSlider(CMD_PA_ALPHASTART, 664, 162, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1, SLIDER_BAR);
	pSlider->SetValue(0.5);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PA_ALPHAEND, 664, 174, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1, SLIDER_BAR);
	pSlider->SetValue(0.5);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PA_ALPHAVAR, 664, 186, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1, SLIDER_BAR);
	pSlider->SetValue(0.5);
	m_pGUI->AddCtrl(pSlider);

	pSlider=new RUGE::CSlider(CMD_PA_RSTART, 664, 221, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1, SLIDER_BAR);
	pSlider->SetValue(0.5);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PA_GSTART, 664, 233, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1, SLIDER_BAR);
	pSlider->SetValue(0.5);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PA_BSTART, 664, 245, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1, SLIDER_BAR);
	pSlider->SetValue(0.5);
	m_pGUI->AddCtrl(pSlider);

	pSlider=new RUGE::CSlider(CMD_PA_REND, 664, 271, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1, SLIDER_BAR);
	pSlider->SetValue(0.5);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PA_GEND, 664, 283, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1, SLIDER_BAR);
	pSlider->SetValue(0.5);
	m_pGUI->AddCtrl(pSlider);
	pSlider=new RUGE::CSlider(CMD_PA_BEND, 664, 295, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1, SLIDER_BAR);
	pSlider->SetValue(0.5);
	m_pGUI->AddCtrl(pSlider);

	pSlider=new RUGE::CSlider(CMD_PA_RGBVAR, 664, 321, 126, 6, m_htexGUI, 417, 177, 6, 6);
	pSlider->SetMode(0, 1, SLIDER_BAR);
	pSlider->SetValue(0.5);
	m_pGUI->AddCtrl(pSlider);

	// Text Control
	pText=new RUGE::CText(CMD_FPS, 641, 454, 28, 16, m_hFont);
	pText->SetMode(DT_TOP|DT_RIGHT);
	pText->SetColor(0xFFD4C25A);
	m_pGUI->AddCtrl(pText);
	pText=new RUGE::CText(CMD_NPARTICLES, 641, 435, 28, 16, m_hFont);
	pText->SetMode(DT_TOP|DT_RIGHT);
	pText->SetColor(0xFFD4C25A);
	m_pGUI->AddCtrl(pText);

	pText=new RUGE::CText(CMD_SYS_TLIFETIME, 113, 26, 28, 16, m_hFont);
	pText->SetMode(DT_TOP|DT_RIGHT);
	pText->SetText("0");
	m_pGUI->AddCtrl(pText);

	pText=new RUGE::CText(CMD_SYS_TEMISSION, 103, 73, 28, 16, m_hFont);
	pText->SetMode(DT_TOP|DT_RIGHT);
	pText->SetText("0");
	m_pGUI->AddCtrl(pText);

	pText=new RUGE::CText(CMD_PM_TDIRECTION, 112, 249, 28, 16, m_hFont);
	pText->SetMode(DT_TOP|DT_RIGHT);
	pText->SetText("0");
	m_pGUI->AddCtrl(pText);

	pText=new RUGE::CText(CMD_PM_TSPREAD, 112, 296, 28, 16, m_hFont);
	pText->SetMode(DT_TOP|DT_RIGHT);
	pText->SetText("0");
	m_pGUI->AddCtrl(pText);
}

BOOL CEventHandler::HandleKey(int nVKey)
{
	switch (nVKey)
	{
	case VK_ESCAPE:
		return TRUE;
	case VK_TAB:
		m_bIFace=!m_bIFace;
		break;
	case VK_LBUTTON:
		if (m_bIFace)
		{
			float x, y;

			m_pApp->Input_GetMousePos(&x, &y);
			if (168<=x && x<=631) m_pParsys->Fire();
		}
		else m_pParsys->Fire();
		break;
	case VK_SPACE:
		m_pParsys->Fire();
		break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		ChangePreset(nVKey-'0');
		break;
	}
	return FALSE;
}

BOOL CEventHandler::HandleCommand(int nID)
{
	char szBuf[256];

	switch (nID)
	{
	// Presets & stuff
	case CMD_EXIT:
		return TRUE;
	case CMD_HELP:
		m_bHelp=ButtonGetState(CMD_HELP);
		break;
	case CMD_BOUNDINGBOX:
		m_bBBox=ButtonGetState(CMD_BOUNDINGBOX);
		break;
	case CMD_PRESET1:
	case CMD_PRESET2:
	case CMD_PRESET3:
	case CMD_PRESET4:
	case CMD_PRESET5:
	case CMD_PRESET6:
	case CMD_PRESET7:
	case CMD_PRESET8:
	case CMD_PRESET9:
		ChangePreset(nID-CMD_PRESET1+1);
		break;

	// System parameters
	case CMD_SYS_LIFETIME:
		m_pParsys->m_Info.fLifetime=SliderGetValue(CMD_SYS_LIFETIME);
		sprintf(szBuf, "%.1f", m_pParsys->m_Info.fLifetime);
		GetTextCtrl(CMD_SYS_TLIFETIME)->SetText(szBuf);
		ButtonSetState(CMD_SYS_LIFECONT, FALSE);
		m_pParsys->Stop();
		break;
	case CMD_SYS_LIFECONT:
		if(ButtonGetState(CMD_SYS_LIFECONT))
		{
			m_pParsys->m_Info.fLifetime=-1.0f;
			m_pParsys->Fire();
		}
		else
		{
			m_pParsys->m_Info.fLifetime=SliderGetValue(CMD_SYS_LIFETIME);
			m_pParsys->Stop();
		}
		break;
	case CMD_SYS_EMISSION:
		m_pParsys->m_Info.nEmission=(int)SliderGetValue(CMD_SYS_EMISSION);
		sprintf(szBuf, "%d", m_pParsys->m_Info.nEmission);
		GetTextCtrl(CMD_SYS_TEMISSION)->SetText(szBuf);
		break;
	case CMD_SYS_PARLIFETIMELOCK:
		if(ButtonGetState(CMD_SYS_PARLIFETIMELOCK))
		{
			SliderSetValue(CMD_SYS_PARLIFETIMEMAX, SliderGetValue(CMD_SYS_PARLIFETIMEMIN));
			m_pParsys->m_Info.fParticleLifeMax=m_pParsys->m_Info.fParticleLifeMin;
		}
		break;
	case CMD_SYS_PARLIFETIMEMIN:
		m_pParsys->m_Info.fParticleLifeMin=SliderGetValue(CMD_SYS_PARLIFETIMEMIN);
		if(ButtonGetState(CMD_SYS_PARLIFETIMELOCK))
		{
			SliderSetValue(CMD_SYS_PARLIFETIMEMAX, m_pParsys->m_Info.fParticleLifeMin);
			m_pParsys->m_Info.fParticleLifeMax=m_pParsys->m_Info.fParticleLifeMin;
		}
		break;
	case CMD_SYS_PARLIFETIMEMAX:
		m_pParsys->m_Info.fParticleLifeMax=SliderGetValue(CMD_SYS_PARLIFETIMEMAX);
		if(ButtonGetState(CMD_SYS_PARLIFETIMELOCK))
		{
			SliderSetValue(CMD_SYS_PARLIFETIMEMIN, m_pParsys->m_Info.fParticleLifeMax);
			m_pParsys->m_Info.fParticleLifeMin=m_pParsys->m_Info.fParticleLifeMax;
		}
		break;
	case CMD_SYS_TEXTURE:
		m_panimPar->SetFrame(m_panimPar->GetFrame()+1);
		break;
	case CMD_SYS_BLENDADDITIVE:
		ButtonSetState(CMD_SYS_BLENDADDITIVE, TRUE);
		ButtonSetState(CMD_SYS_BLENDBLEND, FALSE);
		m_pParsys->m_Info.pSprite->SetBlendMode(BLEND_COLORMUL|BLEND_ALPHAADD|BLEND_ZWRITE);
		break;
	case CMD_SYS_BLENDBLEND:
		ButtonSetState(CMD_SYS_BLENDADDITIVE, FALSE);
		ButtonSetState(CMD_SYS_BLENDBLEND, TRUE);
		m_pParsys->m_Info.pSprite->SetBlendMode(BLEND_COLORMUL|BLEND_ALPHABLEND|BLEND_ZWRITE);
		break;

	// Particle movement
	case CMD_PM_DIRECTION:
		m_pParsys->m_Info.fDirection=SliderGetValue(CMD_PM_DIRECTION);
		sprintf(szBuf, "%d", (int)(m_pParsys->m_Info.fDirection*180/M_PI));
		GetTextCtrl(CMD_PM_TDIRECTION)->SetText(szBuf);
		break;
	case CMD_PM_RELATIVE:
		m_pParsys->m_Info.bRelative=ButtonGetState(CMD_PM_RELATIVE);
		break;
	case CMD_PM_SPREAD:
		m_pParsys->m_Info.fSpread=SliderGetValue(CMD_PM_SPREAD);
		sprintf(szBuf, "%d", (int)(m_pParsys->m_Info.fSpread*180/M_PI));
		GetTextCtrl(CMD_PM_TSPREAD)->SetText(szBuf);
		break;
	case CMD_PM_STARTSPEEDLOCK:
		if(ButtonGetState(CMD_PM_STARTSPEEDLOCK))
		{
			SliderSetValue(CMD_PM_STARTSPEEDMAX, SliderGetValue(CMD_PM_STARTSPEEDMIN));
			m_pParsys->m_Info.fSpeedMax=m_pParsys->m_Info.fSpeedMin;
		}
		break;
	case CMD_PM_STARTSPEEDMIN:
		m_pParsys->m_Info.fSpeedMin=SliderGetValue(CMD_PM_STARTSPEEDMIN);
		if(ButtonGetState(CMD_PM_STARTSPEEDLOCK))
		{
			SliderSetValue(CMD_PM_STARTSPEEDMAX, m_pParsys->m_Info.fSpeedMin);
			m_pParsys->m_Info.fSpeedMax=m_pParsys->m_Info.fSpeedMin;
		}
		break;
	case CMD_PM_STARTSPEEDMAX:
		m_pParsys->m_Info.fSpeedMax=SliderGetValue(CMD_PM_STARTSPEEDMAX);
		if(ButtonGetState(CMD_PM_STARTSPEEDLOCK))
		{
			SliderSetValue(CMD_PM_STARTSPEEDMIN, m_pParsys->m_Info.fSpeedMax);
			m_pParsys->m_Info.fSpeedMin=m_pParsys->m_Info.fSpeedMax;
		}
		break;
	case CMD_PM_GRAVITYLOCK:
		if(ButtonGetState(CMD_PM_GRAVITYLOCK))
		{
			SliderSetValue(CMD_PM_GRAVITYMAX, SliderGetValue(CMD_PM_GRAVITYMIN));
			m_pParsys->m_Info.fGravityMax=m_pParsys->m_Info.fGravityMin;
		}
		break;
	case CMD_PM_GRAVITYMIN:
		m_pParsys->m_Info.fGravityMin=SliderGetValue(CMD_PM_GRAVITYMIN);
		if(ButtonGetState(CMD_PM_GRAVITYLOCK))
		{
			SliderSetValue(CMD_PM_GRAVITYMAX, m_pParsys->m_Info.fGravityMin);
			m_pParsys->m_Info.fGravityMax=m_pParsys->m_Info.fGravityMin;
		}
		break;
	case CMD_PM_GRAVITYMAX:
		m_pParsys->m_Info.fGravityMax=SliderGetValue(CMD_PM_GRAVITYMAX);
		if(ButtonGetState(CMD_PM_GRAVITYLOCK))
		{
			SliderSetValue(CMD_PM_GRAVITYMIN, m_pParsys->m_Info.fGravityMax);
			m_pParsys->m_Info.fGravityMin=m_pParsys->m_Info.fGravityMax;
		}
		break;
	case CMD_PM_RADIALLOCK:
		if(ButtonGetState(CMD_PM_RADIALLOCK))
		{
			SliderSetValue(CMD_PM_RADIALMAX, SliderGetValue(CMD_PM_RADIALMIN));
			m_pParsys->m_Info.fRadialAccelMax=m_pParsys->m_Info.fRadialAccelMin;
		}
		break;
	case CMD_PM_RADIALMIN:
		m_pParsys->m_Info.fRadialAccelMin=SliderGetValue(CMD_PM_RADIALMIN);
		if(ButtonGetState(CMD_PM_RADIALLOCK))
		{
			SliderSetValue(CMD_PM_RADIALMAX, m_pParsys->m_Info.fRadialAccelMin);
			m_pParsys->m_Info.fRadialAccelMax=m_pParsys->m_Info.fRadialAccelMin;
		}
		break;
	case CMD_PM_RADIALMAX:
		m_pParsys->m_Info.fRadialAccelMax=SliderGetValue(CMD_PM_RADIALMAX);
		if(ButtonGetState(CMD_PM_RADIALLOCK))
		{
			SliderSetValue(CMD_PM_RADIALMIN, m_pParsys->m_Info.fRadialAccelMax);
			m_pParsys->m_Info.fRadialAccelMin=m_pParsys->m_Info.fRadialAccelMax;
		}
		break;
	case CMD_PM_TANGENTIALLOCK:
		if(ButtonGetState(CMD_PM_TANGENTIALLOCK))
		{
			SliderSetValue(CMD_PM_TANGENTIALMAX, SliderGetValue(CMD_PM_TANGENTIALMIN));
			m_pParsys->m_Info.fTangentialAccelMax=m_pParsys->m_Info.fTangentialAccelMin;
		}
		break;
	case CMD_PM_TANGENTIALMIN:
		m_pParsys->m_Info.fTangentialAccelMin=SliderGetValue(CMD_PM_TANGENTIALMIN);
		if(ButtonGetState(CMD_PM_TANGENTIALLOCK))
		{
			SliderSetValue(CMD_PM_TANGENTIALMAX, m_pParsys->m_Info.fTangentialAccelMin);
			m_pParsys->m_Info.fTangentialAccelMax=m_pParsys->m_Info.fTangentialAccelMin;
		}
		break;
	case CMD_PM_TANGENTIALMAX:
		m_pParsys->m_Info.fTangentialAccelMax=SliderGetValue(CMD_PM_TANGENTIALMAX);
		if(ButtonGetState(CMD_PM_TANGENTIALLOCK))
		{
			SliderSetValue(CMD_PM_TANGENTIALMIN, m_pParsys->m_Info.fTangentialAccelMax);
			m_pParsys->m_Info.fTangentialAccelMin=m_pParsys->m_Info.fTangentialAccelMax;
		}
		break;

	// Particle appearance
	case CMD_PA_SIZELOCK:
		if(ButtonGetState(CMD_PA_SIZELOCK))
		{
			SliderSetValue(CMD_PA_SIZEEND, SliderGetValue(CMD_PA_SIZESTART));
			m_pParsys->m_Info.fSizeEnd=m_pParsys->m_Info.fSizeStart;
		}
		break;
	case CMD_PA_SIZESTART:
		m_pParsys->m_Info.fSizeStart=SliderGetValue(CMD_PA_SIZESTART)/PARTICLE_SIZE;
		if(ButtonGetState(CMD_PA_SIZELOCK))
		{
			SliderSetValue(CMD_PA_SIZEEND, m_pParsys->m_Info.fSizeStart*PARTICLE_SIZE);
			m_pParsys->m_Info.fSizeEnd=m_pParsys->m_Info.fSizeStart;
		}
		break;
	case CMD_PA_SIZEEND:
		m_pParsys->m_Info.fSizeEnd=SliderGetValue(CMD_PA_SIZEEND)/PARTICLE_SIZE;
		if(ButtonGetState(CMD_PA_SIZELOCK))
		{
			SliderSetValue(CMD_PA_SIZESTART, m_pParsys->m_Info.fSizeEnd*PARTICLE_SIZE);
			m_pParsys->m_Info.fSizeStart=m_pParsys->m_Info.fSizeEnd;
		}
		break;
	case CMD_PA_SIZEVAR:
		m_pParsys->m_Info.fSizeVar=SliderGetValue(CMD_PA_SIZEVAR);
		break;
	case CMD_PA_SPINLOCK:
		if(ButtonGetState(CMD_PA_SPINLOCK))
		{
			SliderSetValue(CMD_PA_SPINEND, SliderGetValue(CMD_PA_SPINSTART));
			m_pParsys->m_Info.fSpinEnd=m_pParsys->m_Info.fSpinStart;
		}
		break;
	case CMD_PA_SPINSTART:
		m_pParsys->m_Info.fSpinStart=SliderGetValue(CMD_PA_SPINSTART);
		if(ButtonGetState(CMD_PA_SPINLOCK))
		{
			SliderSetValue(CMD_PA_SPINEND, m_pParsys->m_Info.fSpinStart);
			m_pParsys->m_Info.fSpinEnd=m_pParsys->m_Info.fSpinStart;
		}
		break;
	case CMD_PA_SPINEND:
		m_pParsys->m_Info.fSpinEnd=SliderGetValue(CMD_PA_SPINEND);
		if(ButtonGetState(CMD_PA_SPINLOCK))
		{
			SliderSetValue(CMD_PA_SPINSTART, m_pParsys->m_Info.fSpinEnd);
			m_pParsys->m_Info.fSpinStart=m_pParsys->m_Info.fSpinEnd;
		}
		break;
	case CMD_PA_SPINVAR:
		m_pParsys->m_Info.fSpinVar=SliderGetValue(CMD_PA_SPINVAR);
		break;
	case CMD_PA_ALPHALOCK:
		if(ButtonGetState(CMD_PA_ALPHALOCK))
		{
			SliderSetValue(CMD_PA_ALPHAEND, SliderGetValue(CMD_PA_ALPHASTART));
			m_pParsys->m_Info.colColorEnd.a=m_pParsys->m_Info.colColorStart.a;
		}
		break;
	case CMD_PA_ALPHASTART:
		m_pParsys->m_Info.colColorStart.a=SliderGetValue(CMD_PA_ALPHASTART);
		if(ButtonGetState(CMD_PA_ALPHALOCK))
		{
			SliderSetValue(CMD_PA_ALPHAEND, m_pParsys->m_Info.colColorStart.a);
			m_pParsys->m_Info.colColorEnd.a=m_pParsys->m_Info.colColorStart.a;
		}
		break;
	case CMD_PA_ALPHAEND:
		m_pParsys->m_Info.colColorEnd.a=SliderGetValue(CMD_PA_ALPHAEND);
		if(ButtonGetState(CMD_PA_ALPHALOCK))
		{
			SliderSetValue(CMD_PA_ALPHASTART, m_pParsys->m_Info.colColorEnd.a);
			m_pParsys->m_Info.colColorStart.a=m_pParsys->m_Info.colColorEnd.a;
		}
		break;
	case CMD_PA_ALPHAVAR:
		m_pParsys->m_Info.fAlphaVar=SliderGetValue(CMD_PA_ALPHAVAR);
		break;
	case CMD_PA_RSTART:
	case CMD_PA_GSTART:
	case CMD_PA_BSTART:
	case CMD_PA_REND:
	case CMD_PA_GEND:
	case CMD_PA_BEND:
		ChangeColor(nID);
		break;
	case CMD_PA_RGBVAR:
		m_pParsys->m_Info.fColorVar=SliderGetValue(CMD_PA_RGBVAR);
		break;

	}
	return FALSE;
}

void CEventHandler::ChangePreset(int n)
{
	m_pParsys->Stop();
	ButtonSetState(CMD_PRESET1-1+m_nPreset, FALSE);
	ButtonSetState(CMD_PRESET1-1+n, TRUE);
	SavePreset(m_nPreset);
	LoadPreset(n);
	m_nPreset=n;
}

void CEventHandler::SavePreset(int n)
{
	FILE *pOut=NULL;
	char szPath[MAX_PATH];

	sprintf(szPath, "Particle%d.psi", n);
	pOut=fopen(szPath, "w");
	if (pOut==NULL) return;
	m_pParsys->m_Info.pSprite=(RUGE::CSprite*)(DWORD_PTR)(m_panimPar->GetFrame()|m_panimPar->GetBlendMode()<<16);
	fwrite(&m_pParsys->m_Info, 1, sizeof(RUGE::PARTICLESYSTEMINFO), pOut);
	fclose(pOut);
	m_pParsys->m_Info.pSprite=m_panimPar;
}

void CEventHandler::LoadPreset(int n)
{
	FILE *pIn=NULL;
	char szPath[MAX_PATH];

	sprintf(szPath, "Particle%d.psi", n);
	pIn=fopen(szPath, "r");
	if (pIn==NULL) return;
	fread(&m_pParsys->m_Info, 1, sizeof(RUGE::PARTICLESYSTEMINFO), pIn);
	fclose(pIn);
	m_panimPar->SetFrame((DWORD)(DWORD_PTR)m_pParsys->m_Info.pSprite&0xFFFF);
	m_panimPar->SetBlendMode((DWORD)(DWORD_PTR)m_pParsys->m_Info.pSprite>>16);
	m_pParsys->m_Info.pSprite=m_panimPar;

	DWORD col1=m_pParsys->m_Info.colColorStart.GetColor()|0xFF000000, col2=m_pParsys->m_Info.colColorEnd.GetColor()|0xFF000000;

	m_psprColor->SetColor(col1, 0);
	m_psprColor->SetColor(col1, 1);
	m_psprColor->SetColor(col2, 2);
	m_psprColor->SetColor(col2, 3);

	char szBuf[256];

	// System parameters
	if(m_pParsys->m_Info.fLifetime==-1.0f)
	{
		SliderSetValue(CMD_SYS_LIFETIME, 5.0f);
		ButtonSetState(CMD_SYS_LIFECONT, TRUE);
		sprintf(szBuf, "%.1f", 5.0f);
		GetTextCtrl(CMD_SYS_TLIFETIME)->SetText(szBuf);
		m_pParsys->Fire();
	}
	else
	{
		SliderSetValue(CMD_SYS_LIFETIME, m_pParsys->m_Info.fLifetime);
		ButtonSetState(CMD_SYS_LIFECONT, FALSE);
		sprintf(szBuf, "%.1f", m_pParsys->m_Info.fLifetime);
		GetTextCtrl(CMD_SYS_TLIFETIME)->SetText(szBuf);
	}

	SliderSetValue(CMD_SYS_EMISSION, (float)m_pParsys->m_Info.nEmission);
	sprintf(szBuf, "%d", m_pParsys->m_Info.nEmission);
	GetTextCtrl(CMD_SYS_TEMISSION)->SetText(szBuf);

	SliderSetValue(CMD_SYS_PARLIFETIMEMIN, m_pParsys->m_Info.fParticleLifeMin);
	SliderSetValue(CMD_SYS_PARLIFETIMEMAX, m_pParsys->m_Info.fParticleLifeMax);
	ButtonSetState(CMD_SYS_PARLIFETIMELOCK, FALSE);

	if(m_panimPar->GetBlendMode()&BLEND_ALPHABLEND)
	{
		ButtonSetState(CMD_SYS_BLENDADDITIVE, FALSE);
		ButtonSetState(CMD_SYS_BLENDBLEND, TRUE);
	}
	else
	{
		ButtonSetState(CMD_SYS_BLENDADDITIVE, TRUE);
		ButtonSetState(CMD_SYS_BLENDBLEND, FALSE);
	}

	// Particle movement
	SliderSetValue(CMD_PM_DIRECTION, m_pParsys->m_Info.fDirection);
	sprintf(szBuf, "%d", (int)(m_pParsys->m_Info.fDirection*180/M_PI));
	GetTextCtrl(CMD_PM_TDIRECTION)->SetText(szBuf);
	ButtonSetState(CMD_PM_RELATIVE, m_pParsys->m_Info.bRelative);

	SliderSetValue(CMD_PM_SPREAD, m_pParsys->m_Info.fSpread);
	sprintf(szBuf, "%d", (int)(m_pParsys->m_Info.fSpread*180/M_PI));
	GetTextCtrl(CMD_PM_TSPREAD)->SetText(szBuf);

	SliderSetValue(CMD_PM_STARTSPEEDMIN, m_pParsys->m_Info.fSpeedMin);
	SliderSetValue(CMD_PM_STARTSPEEDMAX, m_pParsys->m_Info.fSpeedMax);
	ButtonSetState(CMD_PM_STARTSPEEDLOCK, FALSE);

	SliderSetValue(CMD_PM_GRAVITYMIN, m_pParsys->m_Info.fGravityMin);
	SliderSetValue(CMD_PM_GRAVITYMAX, m_pParsys->m_Info.fGravityMax);
	ButtonSetState(CMD_PM_GRAVITYLOCK, FALSE);

	SliderSetValue(CMD_PM_RADIALMIN, m_pParsys->m_Info.fRadialAccelMin);
	SliderSetValue(CMD_PM_RADIALMAX, m_pParsys->m_Info.fRadialAccelMax);
	ButtonSetState(CMD_PM_RADIALLOCK, FALSE);

	SliderSetValue(CMD_PM_TANGENTIALMIN, m_pParsys->m_Info.fTangentialAccelMin);
	SliderSetValue(CMD_PM_TANGENTIALMAX, m_pParsys->m_Info.fTangentialAccelMax);
	ButtonSetState(CMD_PM_TANGENTIALLOCK, FALSE);

	// Particle appearance
	SliderSetValue(CMD_PA_SIZESTART, m_pParsys->m_Info.fSizeStart*PARTICLE_SIZE);
	SliderSetValue(CMD_PA_SIZEEND, m_pParsys->m_Info.fSizeEnd*PARTICLE_SIZE);
	SliderSetValue(CMD_PA_SIZEVAR, m_pParsys->m_Info.fSizeVar);
	ButtonSetState(CMD_PA_SIZELOCK, FALSE);

	SliderSetValue(CMD_PA_SPINSTART, m_pParsys->m_Info.fSpinStart);
	SliderSetValue(CMD_PA_SPINEND, m_pParsys->m_Info.fSpinEnd);
	SliderSetValue(CMD_PA_SPINVAR, m_pParsys->m_Info.fSpinVar);
	ButtonSetState(CMD_PA_SPINLOCK, FALSE);

	SliderSetValue(CMD_PA_ALPHASTART, m_pParsys->m_Info.colColorStart.a);
	SliderSetValue(CMD_PA_ALPHAEND, m_pParsys->m_Info.colColorEnd.a);
	SliderSetValue(CMD_PA_ALPHAVAR, m_pParsys->m_Info.fAlphaVar);
	ButtonSetState(CMD_PA_ALPHALOCK, FALSE);

	SliderSetValue(CMD_PA_RSTART, m_pParsys->m_Info.colColorStart.r);
	SliderSetValue(CMD_PA_GSTART, m_pParsys->m_Info.colColorStart.g);
	SliderSetValue(CMD_PA_BSTART, m_pParsys->m_Info.colColorStart.b);
	SliderSetValue(CMD_PA_REND, m_pParsys->m_Info.colColorEnd.r);
	SliderSetValue(CMD_PA_GEND, m_pParsys->m_Info.colColorEnd.g);
	SliderSetValue(CMD_PA_BEND, m_pParsys->m_Info.colColorEnd.b);
	SliderSetValue(CMD_PA_RGBVAR, m_pParsys->m_Info.fColorVar);
}

void CEventHandler::ChangeColor(int nID)
{
	float fVal=SliderGetValue(nID);

	switch(nID)
	{
	case CMD_PA_RSTART:
		m_pParsys->m_Info.colColorStart.r=fVal;
		break;
	case CMD_PA_GSTART:
		m_pParsys->m_Info.colColorStart.g=fVal;
		break;
	case CMD_PA_BSTART:
		m_pParsys->m_Info.colColorStart.b=fVal;
		break;
	case CMD_PA_REND:
		m_pParsys->m_Info.colColorEnd.r=fVal;
		break;
	case CMD_PA_GEND:
		m_pParsys->m_Info.colColorEnd.g=fVal;
		break;
	case CMD_PA_BEND:
		m_pParsys->m_Info.colColorEnd.b=fVal;
		break;
	}

	DWORD dwCol1, dwCol2;

	dwCol1=m_pParsys->m_Info.colColorStart.GetColor()|0xFF000000;
	dwCol2=m_pParsys->m_Info.colColorEnd.GetColor()|0xFF000000;
	m_psprColor->SetColor(dwCol1, 0);
	m_psprColor->SetColor(dwCol1, 1);
	m_psprColor->SetColor(dwCol2, 2);
	m_psprColor->SetColor(dwCol2, 3);
}