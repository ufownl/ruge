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

#define RUGE_VERSION 0x00020002

#ifndef RUGE_EXPORT
#define RUGE_EXPORT _declspec(dllimport)
#endif  // RUGE_EXPORT

RUGE_EXPORT PAPPLICATION GetRUGE(DWORD dwVer);

#endif  // _RUGE_H_