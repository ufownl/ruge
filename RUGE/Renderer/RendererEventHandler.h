#pragma once

#ifndef _RENDEREREVENTHANDLER_H_
#define _RENDEREREVENTHANDLER_H_

typedef struct IRendererEventHandler
{
	virtual void Render()=0;
	virtual void Pretreat(int nPitch, void *pBits)=0;
} *PRENDEREREVENTHANDLER;

#endif  // _RENDEREREVENTHANDLER_H_