#pragma once

#ifndef _APPLICATIONEVENTHANDLER_H_
#define _APPLICATIONEVENTHANDLER_H_

typedef struct IApplicationEventHandler : public IRendererEventHandler
{
	virtual HRESULT InitResource()=0;
	virtual void ReleaseResource()=0;
	virtual BOOL Frame(float fDelta)=0;
	virtual void WndEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)=0;
} *PAPPLICATIONEVENTHANDLER;

#endif  // _APPLICATIONEVENTHANDLER_H_