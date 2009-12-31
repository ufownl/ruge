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

#ifndef _RUGE_AUDIO_H_
#define _RUGE_AUDIO_H_

#ifndef _RUGE_IMPL_
#include <windows.h>
#include <comdef.h>
#endif  // _RUGE_IMPL_
#include "AudioComDef.h"

namespace RUGE
{

	typedef HANDLE HAUDIO;
	typedef HANDLE HCHANNEL;

	enum AudioIntState
	{
		AUDIO_MAXCHANNELS
	};

	typedef struct IAudio : public IUnknown
	{
		STDMETHOD(SetState)(AudioIntState State, int nVal) PURE;

		STDMETHOD_(int, GetState)(AudioIntState State) PURE;

		STDMETHOD(Initialize)() PURE;
		STDMETHOD(Shutdown)() PURE;
		STDMETHOD(Update)() PURE;

		STDMETHOD_(HAUDIO, Effect_Load)(LPCSTR lpcszPath) PURE;
		STDMETHOD_(HCHANNEL, Effect_Play)(HAUDIO hAudio, int nVolume=100, int nPan=0, float fPitch=1.0f, BOOL bLoop=FALSE) PURE;

		STDMETHOD_(HAUDIO, Music_Load)(LPCSTR lpcszPath) PURE;
		STDMETHOD_(HCHANNEL, Music_Play)(HAUDIO hAudio, int nVolume=100, float fStart=0.0f, BOOL bLoop=TRUE) PURE;

		STDMETHOD_(float, Audio_GetLength)(HAUDIO hAudio) PURE;
		STDMETHOD(Audio_Free)(HAUDIO hAudio) PURE;

		STDMETHOD(Channel_Pause)(HCHANNEL hChannel) PURE;
		STDMETHOD(Channel_Resume)(HCHANNEL hChannel) PURE;
		STDMETHOD(Channel_Stop)(HCHANNEL hChannel) PURE;
		STDMETHOD_(BOOL, Channel_IsPlaying)(HCHANNEL hChannel) PURE;

		STDMETHOD(Channel_SetVolume)(HCHANNEL hChannel, int nVolume) PURE;
		STDMETHOD(Channel_SetPan)(HCHANNEL hChannel, int nPan) PURE;
		STDMETHOD(Channel_SetPitch)(HCHANNEL hChannel, float fPitch) PURE;
		STDMETHOD(Channel_SetPosition)(HCHANNEL hChannel, float fPos) PURE;

		STDMETHOD_(int, Channel_GetVolume)(HCHANNEL hChannel) PURE;
		STDMETHOD_(int, Channel_GetPan)(HCHANNEL hChannel) PURE;
		STDMETHOD_(float, Channel_GetPosition)(HCHANNEL hChannel) PURE;
	} *PAUDIO;

	_COM_SMARTPTR_TYPEDEF(IAudio, __uuidof(IAudio));

}

#endif  // _RUGE_AUDIO_H_