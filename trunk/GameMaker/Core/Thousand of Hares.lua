SCREEN_WIDTH=800;
SCREEN_HEIGHT=600;

MIN_OBJCNT=100;
MAX_OBJCNT=2000;

BlendMode=0;

Blend=
{
	Bit_or(BLEND_COLORMUL, BLEND_ALPHABLEND, BLEND_NOZWRITE),
	Bit_or(BLEND_COLORADD, BLEND_ALPHABLEND, BLEND_NOZWRITE),
	Bit_or(BLEND_COLORMUL, BLEND_ALPHABLEND, BLEND_NOZWRITE),
	Bit_or(BLEND_COLORMUL, BLEND_ALPHAADD, BLEND_NOZWRITE),
	Bit_or(BLEND_COLORMUL, BLEND_ALPHABLEND, BLEND_NOZWRITE)
};

Color=
{
	{0xFFFFFFFF, 0xFFFFE080, 0xFF80A0FF, 0xFFA0FF80, 0xFFFF80A0},
	{0xFF000000, 0xFF303000, 0xFF000060, 0xFF006000, 0xFF600000},
	{0x80FFFFFF, 0x80FFE080, 0x8080A0FF, 0x80A0FF80, 0x80FF80A0},
	{0x80FFFFFF, 0x80FFE080, 0x8080A0FF, 0x80A0FF80, 0x80FF80A0},
	{0x40202020, 0x40302010, 0x40102030, 0x40203010, 0x40102030}
};

FontColor={0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF};

function SetBlend(Mode)
	Mode=Mode%5;
	Sprite_SetBlendMode(Spr, Blend[Mode+1]);
	for i=1, MAX_OBJCNT do
		Objs[i].Color=Color[Mode+1][Random_Int(1, 5)];
	end
	return Mode;
end;

function InitEngine()  -- RUGE Callback Function
	System_SetState(APP_CAPTION, "Thousand of Hares");
	System_SetState(APP_VSYNC, VSYNC_IMMEDIATE);
end

function InitResource()  -- RUGE Callback Function
	Font=Font_Create(20, 0, 0, false, "Fixedsys");
	Tex=Texture_Load("zazaka.png");
	TexBg=Texture_Load("bg2.png");

	Spr=Sprite_Create(Tex, 0, 0, 64, 64);
	Sprite_SetHotSpot(Spr, 32, 32);

	SprBg=Sprite_Create(TexBg, 0, 0, 800, 600);
	Sprite_SetBlendMode(SprBg, Bit_or(BLEND_COLORADD, BLEND_ALPHABLEND, BLEND_NOZWRITE));
	Sprite_SetColor(SprBg, 0xFF000000, 0);
	Sprite_SetColor(SprBg, 0xFF000000, 1);
	Sprite_SetColor(SprBg, 0xFF000040, 2);
	Sprite_SetColor(SprBg, 0xFF000040, 3);

	Objs={};
	ObjCnt=1000;

	for i=1, MAX_OBJCNT do
		Objs[i]=
		{
			x=Random_Float(0, SCREEN_WIDTH),
			y=Random_Float(0, SCREEN_HEIGHT),
			dx=Random_Float(-200, 200),
			dy=Random_Float(-200, 200),
			Scale=Random_Float(0.5, 2.0),
			dScale=Random_Float(-1.0, 1.0),
			Rot=Random_Float(0, math.pi*2),
			dRot=Random_Float(-1.0, 1.0)
		};
	end

	SetBlend(BlendMode)

	return true;
end

function ReleaseResource()  -- RUGE Callback Function
	Sprite_Free(SprBg);
	Sprite_Free(Spr);
	Texture_Free(TexBg);
	Texture_Free(Tex);
	Font_Free(Font);
end

function Frame(Delta)  -- RUGE Callback Function
	if Input_GetKey()==VK_ESCAPE then return true;
	elseif Input_GetKey()==VK_UP then
		if ObjCnt<MAX_OBJCNT then ObjCnt=ObjCnt+100; end
	elseif Input_GetKey()==VK_DOWN then
		if ObjCnt>MIN_OBJCNT then ObjCnt=ObjCnt-100; end
	elseif Input_GetKey()==VK_SPACE then
		BlendMode=SetBlend(BlendMode+1);
	end

	for i=1, ObjCnt do
		Objs[i].x=Objs[i].x+Objs[i].dx*Delta;
		if Objs[i].x<0 or Objs[i].x>SCREEN_WIDTH then Objs[i].dx=-Objs[i].dx; end
		Objs[i].y=Objs[i].y+Objs[i].dy*Delta;
		if Objs[i].y<0 or Objs[i].y>SCREEN_HEIGHT then Objs[i].dy=-Objs[i].dy; end
		Objs[i].Scale=Objs[i].Scale+Objs[i].dScale*Delta;
		if Objs[i].x<0.5 or Objs[i].x>2 then Objs[i].dScale=-Objs[i].dScale; end
		Objs[i].Rot=Objs[i].Rot+Objs[i].dRot*Delta;
	end

	return false;
end

function Render()  -- RUGE Callback Function
	Gfx_Clear();
	Sprite_Render(SprBg, 0, 0);
	for i=1, ObjCnt do
		Sprite_SetColor(Spr, Objs[i].Color);
		Sprite_RenderEx(Spr, Objs[i].x, Objs[i].y, Objs[i].Rot, Objs[i].Scale);
	end

	local Rect=
	{
		Left=0,
		Top=0,
		Right=800,
		Bottom=600,
	};

	Font_DrawText(Font,
		string.format("UP and DOWN to adjust number of hares: %d\nSPACE to change blending mode: %d\nFPS: %d",
		ObjCnt, BlendMode, Timer_GetFPS()), Rect, 0, Bit_or(DT_LEFT, DT_TOP),
		FontColor[BlendMode+1]);
end
