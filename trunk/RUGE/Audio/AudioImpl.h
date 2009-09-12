#pragma once

#ifndef _AUDIOIMPL_H_
#define _AUDIOIMPL_H_

#include "Audio.h"

typedef struct SOUNDLIST
{
	FMOD::Sound *pSound;
	SOUNDLIST *pNext;
} *PSOUNDLIST;

class CAudioImpl : public IAudio
{
public:
	CAudioImpl();
	virtual ~CAudioImpl();

	// IUnknown
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

	// IAudio
	STDMETHOD(Initialize)(int nMaxChannels=32);
	STDMETHOD(Shutdown)();
	STDMETHOD(Update)();

	STDMETHOD_(HAUDIO, Effect_Load)(LPCSTR lpcszPath);
	STDMETHOD_(HCHANNEL, Effect_Play)(HAUDIO hAudio, int nVolume=100, int nPan=0, float fPitch=1.0f, BOOL bLoop=FALSE);

	STDMETHOD_(HAUDIO, Music_Load)(LPCSTR lpcszPath);
	STDMETHOD_(HCHANNEL, Music_Play)(HAUDIO hAudio, int nVolume=100, float fStart=0.0f, BOOL bLoop=TRUE);

	STDMETHOD_(float, Audio_GetLength)(HAUDIO hAudio);
	STDMETHOD(Audio_Free)(HAUDIO hAudio);

	STDMETHOD(Channel_Pause)(HCHANNEL hChannel);
	STDMETHOD(Channel_Resume)(HCHANNEL hChannel);
	STDMETHOD(Channel_Stop)(HCHANNEL hChannel);
	STDMETHOD_(BOOL, Channel_IsPlaying)(HCHANNEL hChannel);

	STDMETHOD(Channel_SetVolume)(HCHANNEL hChannel, int nVolume);
	STDMETHOD(Channel_SetPan)(HCHANNEL hChannel, int nPan);
	STDMETHOD(Channel_SetPitch)(HCHANNEL hChannel, float fPitch);
	STDMETHOD(Channel_SetPosition)(HCHANNEL hChannel, float fPos);

	STDMETHOD_(int, Channel_GetVolume)(HCHANNEL hChannel);
	STDMETHOD_(int, Channel_GetPan)(HCHANNEL hChannel);
	STDMETHOD_(float, Channel_GetPosition)(HCHANNEL hChannel);

protected:
	void Append(FMOD::Sound *pSound);
	void Remove(FMOD::Sound *pSound);
	void RemoveAll();

protected:
	ULONG m_uRefCount;
	FMOD::System *m_pFmod;
	PSOUNDLIST m_pSndList;
};

#endif  // _AUDIOIMPL_H_