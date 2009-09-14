#pragma once

#ifndef _RUGE_H_
#define _RUGE_H_

#ifndef _RUGE_IMPL_
#include <Timer.h>
#include <Random.h>
#include <Renderer.h>
#include <Audio.h>
#include <Input.h>
#include <Application.h>
#endif  // _RUGE_IMPL_

#define RUGE_VERSION 0x00020001

#ifndef RUGE_EXPORT
#define RUGE_EXPORT _declspec(dllimport)
#endif  // RUGE_EXPORT

RUGE_EXPORT PAPPLICATION GetRUGE(DWORD dwVer);

#endif  // _RUGE_H_