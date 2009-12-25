/*
RUGE GameMaker Copyright (C) 2009 ”Œœ¿UFO

This file is part of RUGE GameMaker.

RUGE GameMaker is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RUGE GameMaker is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RUGE GameMaker.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "StdAfx.h"
#include "RugeLuaText.h"
#include <Text.h>

HTEXT Text_Create(int nID, float x, float y, float w, float h, RUGE::HFONT hFont)
{
	return new RUGE::CText(nID, x, y, w, h, hFont);
}

void Text_Free(HTEXT hText)
{
	delete (RUGE::CText*)hText;
}

void Text_SetColor(HTEXT hText, int nColor)
{
	((RUGE::CText*)hText)->SetColor(nColor);
}

void Text_SetMode(HTEXT hText, int nMode)
{
	((RUGE::CText*)hText)->SetMode(nMode);
}

void Text_SetText(HTEXT hText, LPCSTR lpcszText)
{
	((RUGE::CText*)hText)->SetText(lpcszText);
}