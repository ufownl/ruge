#pragma once

#ifndef _AUDIO_H_
#define _AUDIO_H_

#ifndef _RUGE_IMPL_
#include <windows.h>
#include <comdef.h>
#endif  // _RUGE_IMPL_
#include "AudioComDef.h"

typedef HANDLE HAUDIO;
typedef HANDLE HCHANNEL;

typedef struct IAudio : public IUnknown
{
	STDMETHOD(Initialize)(int nMaxChannels=32) PURE;
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

#endif  // _AUDIO_H_