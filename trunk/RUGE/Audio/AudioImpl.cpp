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

#include "StdAfx.h"
#include "AudioImpl.h"

CAudioImpl::CAudioImpl()
	: m_uRefCount(0)
	, m_pFmod(NULL)
	, m_pSndList(NULL)
{
	g_uDllLockCount++;
}

CAudioImpl::~CAudioImpl()
{
	Shutdown();
	g_uDllLockCount--;
}

STDMETHODIMP_(ULONG) CAudioImpl::AddRef()
{
	return ++m_uRefCount;
}

STDMETHODIMP_(ULONG) CAudioImpl::Release()
{
	ULONG uRet=--m_uRefCount;

	if (m_uRefCount==0) delete this;
	return uRet;
}

STDMETHODIMP CAudioImpl::QueryInterface(REFIID riid, void** ppv)
{
	HRESULT hr=S_OK;

	if (IsBadWritePtr(ppv, sizeof(void*))) return E_POINTER;
	*ppv=NULL;
	if (InlineIsEqualGUID(riid, IID_IUnknown )) *ppv=(IUnknown*)this;
	else if (InlineIsEqualGUID(riid, __uuidof(IAudio))) *ppv=(IAudio*)this;
	else hr=E_NOINTERFACE;
	if (hr==S_OK) ((IUnknown*)*ppv)->AddRef();
	return hr;
}

STDMETHODIMP CAudioImpl::Initialize(int nMaxChannels/* =32 */)
{
	assert(m_pFmod==NULL);

	FMOD_RESULT fr=System_Create(&m_pFmod);

	if (fr!=FMOD_OK) return -fr;
	return -m_pFmod->init(nMaxChannels, FMOD_INIT_NORMAL, NULL);
}

STDMETHODIMP CAudioImpl::Shutdown()
{
	RemoveAll();
	if (m_pFmod!=NULL)
	{
		m_pFmod->release();
		m_pFmod=NULL;
	}
	return S_OK;
}

STDMETHODIMP CAudioImpl::Update()
{
	return -m_pFmod->update();
}

STDMETHODIMP_(HAUDIO) CAudioImpl::Effect_Load(LPCSTR lpcszPath)
{
	assert(m_pFmod!=NULL);

	FMOD::Sound *pSound=NULL;

	if (m_pFmod->createSound(lpcszPath, FMOD_LOOP_NORMAL|FMOD_2D|FMOD_SOFTWARE, NULL, &pSound)!=FMOD_OK) return NULL;
	Append(pSound);
	return (HAUDIO)pSound;
}

STDMETHODIMP_(HCHANNEL) CAudioImpl::Effect_Play(HAUDIO hAudio, int nVolume/* =100 */, int nPan/* =0 */,
												float fPitch/* =1.0f */, BOOL bLoop/* =FALSE */)
{
	assert(m_pFmod!=NULL);

	FMOD::Channel *pChannel=NULL;

	float fFreq;

	((FMOD::Sound*)hAudio)->getDefaults(&fFreq, NULL, NULL, NULL);
	if (m_pFmod->playSound(FMOD_CHANNEL_FREE, (FMOD::Sound*)hAudio, true, &pChannel)!=FMOD_OK) return NULL;
	pChannel->setVolume(nVolume*0.01f);
	pChannel->setPan(nPan*0.01f);
	pChannel->setFrequency(fFreq*fPitch);
	pChannel->setLoopCount(bLoop ? -1 : 0);
	pChannel->setPaused(false);
	return (HCHANNEL)pChannel;
}

STDMETHODIMP_(HAUDIO) CAudioImpl::Music_Load(LPCSTR lpcszPath)
{
	assert(m_pFmod!=NULL);

	FMOD::Sound *pSound=NULL;

	if (m_pFmod->createStream(lpcszPath, FMOD_LOOP_NORMAL|FMOD_2D|FMOD_SOFTWARE, NULL, &pSound)!=FMOD_OK) return NULL;
	Append(pSound);
	return (HAUDIO)pSound;
}

STDMETHODIMP_(HCHANNEL) CAudioImpl::Music_Play(HAUDIO hAudio, int nVolume/* =100 */, float fStart/* =0.0f */, BOOL bLoop/* =TRUE */)
{
	assert(m_pFmod!=NULL);

	FMOD::Channel *pChannel=NULL;

	if (m_pFmod->playSound(FMOD_CHANNEL_FREE, (FMOD::Sound*)hAudio, true, &pChannel)!=FMOD_OK) return NULL;
	pChannel->setVolume(nVolume*0.01f);
	pChannel->setPosition((unsigned)(fStart*1000), FMOD_TIMEUNIT_MS);
	pChannel->setLoopCount(bLoop ? -1 : 0);
	pChannel->setPaused(false);
	return (HCHANNEL)pChannel;
}

STDMETHODIMP_(float) CAudioImpl::Audio_GetLength(HAUDIO hAudio)
{
	if (hAudio==NULL) return 0.0f;

	unsigned uLen;

	((FMOD::Sound*)hAudio)->getLength(&uLen, FMOD_TIMEUNIT_MS);
	return (float)uLen/1000;
}

STDMETHODIMP CAudioImpl::Audio_Free(HAUDIO hAudio)
{
	if (hAudio==NULL) return E_HANDLE;
	Remove((FMOD::Sound*)hAudio);
	return S_OK;
}

STDMETHODIMP CAudioImpl::Channel_Pause(HCHANNEL hChannel)
{
	if (hChannel==NULL) return E_HANDLE;
	return -((FMOD::Channel*)hChannel)->setPaused(true);
}

STDMETHODIMP CAudioImpl::Channel_Resume(HCHANNEL hChannel)
{
	if (hChannel==NULL) return E_HANDLE;
	return -((FMOD::Channel*)hChannel)->setPaused(false);
}

STDMETHODIMP CAudioImpl::Channel_Stop(HCHANNEL hChannel)
{
	if (hChannel==NULL) return E_HANDLE;
	return -((FMOD::Channel*)hChannel)->stop();
}

STDMETHODIMP_(BOOL) CAudioImpl::Channel_IsPlaying(HCHANNEL hChannel)
{
	if (hChannel==NULL) return E_HANDLE;

	bool bPlayed;

	((FMOD::Channel*)hChannel)->isPlaying(&bPlayed);
	return (BOOL)bPlayed;
}

STDMETHODIMP CAudioImpl::Channel_SetVolume(HCHANNEL hChannel, int nVolume)
{
	if (hChannel==NULL) return E_HANDLE;
	return -((FMOD::Channel*)hChannel)->setVolume(nVolume*0.01f);
}

STDMETHODIMP CAudioImpl::Channel_SetPan(HCHANNEL hChannel, int nPan)
{
	if (hChannel==NULL) return E_HANDLE;
	return -((FMOD::Channel*)hChannel)->setPan(nPan*0.01f);
}

STDMETHODIMP CAudioImpl::Channel_SetPitch(HCHANNEL hChannel, float fPitch)
{
	if (hChannel==NULL) return E_HANDLE;

	float fFreq;

	((FMOD::Channel*)hChannel)->getFrequency(&fFreq);
	return -((FMOD::Channel*)hChannel)->setFrequency(fFreq*fPitch);
}

STDMETHODIMP CAudioImpl::Channel_SetPosition(HCHANNEL hChannel, float fPos)
{
	if (hChannel==NULL) return E_HANDLE;
	return -((FMOD::Channel*)hChannel)->setPosition((unsigned)(fPos*1000), FMOD_TIMEUNIT_MS);
}

STDMETHODIMP_(int) CAudioImpl::Channel_GetVolume(HCHANNEL hChannel)
{
	if (hChannel==NULL) return E_HANDLE;

	float fVolume;

	((FMOD::Channel*)hChannel)->getVolume(&fVolume);
	return (int)(fVolume*100);
}

STDMETHODIMP_(int) CAudioImpl::Channel_GetPan(HCHANNEL hChannel)
{
	if (hChannel==NULL) return E_HANDLE;

	float fPan;

	((FMOD::Channel*)hChannel)->getPan(&fPan);
	return (int)(fPan*100);
}

STDMETHODIMP_(float) CAudioImpl::Channel_GetPosition(HCHANNEL hChannel)
{
	if (hChannel==NULL) return 0.0f;

	unsigned uPos;

	((FMOD::Channel*)hChannel)->getPosition(&uPos, FMOD_TIMEUNIT_MS);
	return (float)uPos/1000;
}

void CAudioImpl::Append(FMOD::Sound *pSound)
{
	PSOUNDLIST pNode=new SOUNDLIST;

	pNode->pSound=pSound;
	pNode->pNext=m_pSndList;
	m_pSndList=pNode;
}

void CAudioImpl::Remove(FMOD::Sound *pSound)
{
	assert(m_pSndList!=NULL);
	if (m_pSndList->pSound==pSound)
	{
		PSOUNDLIST pNode=m_pSndList;

		m_pSndList=m_pSndList->pNext;
		pSound->release();
		delete pNode;
	}
	else
	{
		for (PSOUNDLIST p=m_pSndList; p->pNext!=NULL; p=p->pNext)
		{
			if (p->pNext->pSound==pSound)
			{
				PSOUNDLIST pNode=p->pNext;

				p->pNext=pNode->pNext;
				pSound->release();
				delete pNode;
				break;
			}
		}
	}
}

void CAudioImpl::RemoveAll()
{
	while (m_pSndList!=NULL)
	{
		PSOUNDLIST pNode=m_pSndList;

		m_pSndList=m_pSndList->pNext;
		pNode->pSound->release();
		delete pNode;
	}
}
