#include "StdAfx.h"
#include "InputImpl.h"

#define WM_MOUSEWHEEL	0x020A
#define WHEEL_DELTA		120

LPCSTR CInputImpl::m_lpcszKeyNames[256]={
	"?", "Left Mouse Button", "Right Mouse Button", "?", "Middle Mouse Button",
	"?", "?", "?", "Backspace", "Tab", "?", "?", "?", "Enter", "?", "?",
	"Shift", "Ctrl", "Alt", "Pause", "Caps Lock", "?", "?", "?", "?", "?", "?",
	"Escape", "?", "?", "?", "?",
	"Space", "Page Up", "Page Down", "End", "Home",
	"Left Arrow", "Up Arrow", "Right Arrow", "Down Arrow",
	"?", "?", "?", "?", "Insert", "Delete", "?",
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
	"?", "?", "?", "?", "?", "?", "?",
	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
	"Left Win", "Right Win", "Application", "?", "?",
	"NumPad 0", "NumPad 1", "NumPad 2", "NumPad 3", "NumPad 4",
	"NumPad 5", "NumPad 6", "NumPad 7", "NumPad 8", "NumPad 9",
	"Multiply", "Add", "?", "Subtract", "Decimal", "Divide",
	"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"Num Lock", "Scroll Lock",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"Semicolon", "Equals", "Comma", "Minus", "Period", "Slash", "Grave",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?",
	"Left bracket", "Backslash", "Right bracket", "Apostrophe",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
	"?", "?", "?"};

CInputImpl::CInputImpl()
	: m_uRefCount(0)
	, m_fPosX(0)
	, m_fPosY(0)
	, m_nPosZ(0)
	, m_nVKLast(0)
	, m_chLast(0)
{
	memset(m_nOldKeyStates, 0, sizeof(m_nOldKeyStates));
	g_uDllLockCount++;
}

CInputImpl::~CInputImpl()
{
	g_uDllLockCount--;
}

STDMETHODIMP_(ULONG) CInputImpl::AddRef()
{
	return ++m_uRefCount;
}

STDMETHODIMP_(ULONG) CInputImpl::Release()
{
	ULONG uRet=--m_uRefCount;

	if (m_uRefCount==0) delete this;
	return uRet;
}

STDMETHODIMP CInputImpl::QueryInterface(REFIID riid, void** ppv)
{
	HRESULT hr=S_OK;

	if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
	*ppv=NULL;
	if (InlineIsEqualGUID(riid, IID_IUnknown )) *ppv=(IUnknown*)this;
	else if (InlineIsEqualGUID(riid, __uuidof(IInput))) *ppv=(IInput*)this;
	else hr=E_NOINTERFACE;
	if (hr==S_OK) ((IUnknown*)*ppv)->AddRef();
	return hr;
}

STDMETHODIMP_(BOOL) CInputImpl::KeyDown(int nVKey)
{
	int nKeyState=m_nOldKeyStates[nVKey];

	m_nOldKeyStates[nVKey]=GetKeyState(nVKey);
	return m_nOldKeyStates[nVKey]<0 && nKeyState>=0;
}

STDMETHODIMP_(BOOL) CInputImpl::KeyPress(int nVKey)
{
	m_nOldKeyStates[nVKey]=GetKeyState(nVKey);
	return m_nOldKeyStates[nVKey]<0;
}

STDMETHODIMP_(BOOL) CInputImpl::KeyUp(int nVKey)
{
	int nKeyState=m_nOldKeyStates[nVKey];

	m_nOldKeyStates[nVKey]=GetKeyState(nVKey);
	return m_nOldKeyStates[nVKey]>=0 && nKeyState<0;
}

STDMETHODIMP_(int) CInputImpl::GetKey()
{
	int nRet=m_nVKLast;

	m_nVKLast=0;
	return nRet;
}

STDMETHODIMP_(char) CInputImpl::GetChar()
{
	char chRet=m_chLast;

	m_chLast=0;
	return chRet;
}

STDMETHODIMP_(LPCSTR) CInputImpl::GetKeyName(int nVKey)
{
	return m_lpcszKeyNames[nVKey];
}

STDMETHODIMP CInputImpl::GetMousePos(float *x, float *y)
{
	*x=m_fPosX;
	*y=m_fPosY;
	return S_OK;
}

STDMETHODIMP_(SHORT) CInputImpl::GetMouseWheel()
{
	return m_nPosZ;
}

STDMETHODIMP CInputImpl::OnWndEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		m_nVKLast=(int)wParam;
		break;
	case WM_CHAR:
		m_chLast=(char)wParam;
		break;
	case WM_MOUSEMOVE:
		m_fPosX=LOWORD(lParam);
		m_fPosY=HIWORD(lParam);
		break;
	case WM_MOUSEWHEEL:
		m_nPosZ+=(short)HIWORD(wParam)/WHEEL_DELTA;
		break;
	default:
		break;
	}
	return S_OK;
}
