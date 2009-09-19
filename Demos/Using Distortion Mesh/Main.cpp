#include <RUGE.h>
#pragma comment(lib, "RUGE.lib")

#include <DistortionMesh.h>
#ifdef _DEBUG
#pragma comment(lib, "Helper_Debug.lib")
#else
#pragma comment(lib, "Helper.lib")
#endif  // _DEBUG

#include <math.h>

PAPPLICATION g_pApp;  // ����RUGE Application�ӿ�ָ��

HFONTX g_hFont;
HTEXTURE g_hTex;

CDistortionMesh *g_pDis;

const int g_cnRows=16, g_cnCols=16;
const float g_cfCellW=512.0f/(g_cnCols-1), g_cfCellH=512.0f/(g_cnRows-1), g_cfDisX=144, g_cfDisY=44;

class CEventHandler : public IApplicationEventHandler  // ʵ��RUGE Application�¼�����ӿ�
{
public:
	virtual HRESULT InitResource();
	virtual void ReleaseResource();
	virtual BOOL Frame(float fDelta);
	virtual void Render();
	virtual void Pretreat(int nPitch, void *pBits);
	virtual void WndEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

HRESULT CEventHandler::InitResource()
{
	// �ڴ������Դ��ʼ������
	g_hFont=g_pApp->Font_Create(20, 0, 0, FALSE, "΢���ź�");
	g_hTex=g_pApp->Texture_Load("texture.jpg");

	g_pDis=new CDistortionMesh(g_cnRows, g_cnCols);
	g_pDis->SetTexture(g_hTex);
	g_pDis->SetTextureRect(0, 0, 512, 512);
	g_pDis->SetBlendMode(BLEND_COLORADD|BLEND_ALPHABLEND|BLEND_ZWRITE);
	g_pDis->Clear(0xFF000000);

	return S_OK;  // ����S_OK��ʾ��Դ��ʼ���ɹ�
}

void CEventHandler::ReleaseResource()
{
	// �ڴ������Դ�ͷŴ���
	// �����ڲ�����ϵͳ�����Զ��ͷ��������弰������Դ
	delete g_pDis;
}

// float fDelta: ��һ֡�͵�ǰ֡��ʱ����������Ϊ��λ
BOOL CEventHandler::Frame(float fDelta)
{
	// �ڴ������Ϸ�߼����ƴ���
	static float fTime=0;
	static int nTrans=0;
	
	fTime+=fDelta;

	switch (g_pApp->Input_GetKey())
	{
	case VK_ESCAPE:
		return TRUE;
	case VK_SPACE:
		nTrans=(nTrans+1)%3;
		g_pDis->Clear(0xFF000000);
		break;
	default:
		break;
	}

	switch (nTrans)
	{
	case 0:
		for (int i=1; i<g_cnRows-1; i++)
		{
			for (int j=1; j<g_cnCols-1; j++)
			{
				g_pDis->SetDisplacement(i, j, cosf(fTime*10+(i+j)/2)*5, sinf(fTime*10+(i+j)/2)*5, DISP_NODE);
			}
		}
		break;
	case 1:
		for (int i=0; i<g_cnRows; i++)
		{
			for (int j=1; j<g_cnCols-1; j++)
			{
				DWORD dwColor=(DWORD)((cosf(fTime*5+(i+j)/2)+1)*35);

				g_pDis->SetDisplacement(i, j, cosf(fTime*5+j/2)*15, 0, DISP_NODE);
				g_pDis->SetColor(i, j, 0xFF<<24|dwColor<<16|dwColor<<8|dwColor);
			}
		}
		break;
	case 2:
		for(int i=0; i<g_cnRows; i++)
		{
			for(int j=0; j<g_cnCols; j++)
			{
				float fr=sqrtf(powf(j-(float)g_cnCols/2, 2)+powf(i-(float)g_cnRows/2, 2)), fa=fr*cosf(fTime*2)*0.1f,
					fdx=sinf(fa)*(i*g_cfCellH-256)+cosf(fa)*(j*g_cfCellW-256), fdy=cosf(fa)*(i*g_cfCellH-256)-sinf(fa)*(j*g_cfCellW-256);
				DWORD dwColor=(DWORD)((cosf(fr+fTime*4)+1)*40);

				g_pDis->SetDisplacement(i, j, fdx, fdy, DISP_CENTER);
				g_pDis->SetColor(i, j, 0xFF<<24|dwColor<<16|(dwColor/2)<<8);
			}
		}
		break;
	}
	return FALSE;  // ����FALSE��ʾ��Ϸδ����
}

void CEventHandler::Render()
{
	// �ڴ������Ⱦ����
	g_pApp->Gfx_Clear();
	g_pDis->Render(g_cfDisX, g_cfDisY);

	static RECT Rect={0, 0, 100, 20};
	char szBuf[256];

	sprintf(szBuf, "FPS: %d", g_pApp->System_GetState(RUGE_FPS));
	g_pApp->Font_DrawText(g_hFont, szBuf, &Rect);
}

// int nPitch: ͼ����һ�����ص��ڻ���������ռ�ռ���ֽ���
// void *pBits: ������Ⱦ����Ļ��ͼ�����ݻ�����ָ�룬һ�����ص�ռ4���ֽڣ���
//              ���£�0xAARRGGBB
void CEventHandler::Pretreat(int nPitch, void *pBits)
{
	// �ڴ����ͼ��Ԥ�������
}

// UINT uMsg: WINDOWS��Ϣ����
// WPARAM wParam: WINDOWS��ϢWPARAM����
// LPARAM lParam: WINDOWS��ϢLPARAM����
void CEventHandler::WndEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �ڴ���Ӵ�����Ϣ�������
}

int main(int argc, char *argv[])
{
	HRESULT hr=0;  // ���򷵻�ֵ

	CoInitialize(NULL);  // ��ʼ��COM��
	g_pApp=GetRUGE(RUGE_VERSION);  // ��ȡRUGE Application����
	if (g_pApp==NULL)
	{
		puts("Error: RUGE Application�����ȡʧ��");
		system("Pause");
		return -1;
	}
	g_pApp->System_SetState(RUGE_EVENTHANDLER, &CEventHandler());  // �����¼��������
	g_pApp->System_SetState(RUGE_CAPTION, "Using Distortion Mesh");  // ���ô��ڱ���
	g_pApp->System_SetState(RUGE_VSYNC, VSYNC_ONE);  // ������ֱͬ��
	hr=g_pApp->System_Initialize();  // ��ʼ��RUGE Application����
	if (SUCCEEDED(hr)) hr=g_pApp->System_Run();  // ������ѭ��
	else
	{
		printf("Error: RUGE Application�����ʼ��ʧ��\nError Code: %d\n", hr);
		system("Pause");
	}
	g_pApp->Release();  // �ͷ�RUGE Application����
	CoUninitialize();  // �ͷ�COM��
	return hr;
}