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