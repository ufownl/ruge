function InitEngine()  -- RUGE Callback Function
	System_SetState(APP_CAPTION, "Creating Menus");
	System_SetState(APP_VSYNC, VSYNC_ONE);
	System_SetState(APP_HIDECURSOR, true);
end

function InitResource()  -- RUGE Callback Function
	Quad=
	{
		v=
		{
			{x=0, y=0, z=0.5, Color=0xFFFFFFFF, tu=0, tv=0},
			{x=800, y=0, z=0.5, Color=0xFFFFFFFF, tu=0, tv=0},
			{x=800, y=600, z=0.5, Color=0xFFFFFFFF, tu=0, tv=0},
			{x=0, y=600, z=0.5, Color=0xFFFFFFFF, tu=0, tv=0}
		},
		Tex=Texture_Load("bg.png"),
		Blend=BLEND_DEFAULT
	}

	Tex=Texture_Load("cursor.png");
	Sound=Effect_Load("menu.wav");
	Font=Font_Create(40, 0, 0, false, "Î¢ÈíÑÅºÚ");

	Spr=Sprite_Create(Tex, 0, 0, 32, 32);

	GUI=GUI_Create();
	GUI_AddCtrl(GUI, Control_Create(1, "Menu Item.lua", {Font=Font, Sound=Sound, x=400, y=175, Delay=0, Title="Play"}));
	GUI_AddCtrl(GUI, Control_Create(2, "Menu Item.lua", {Font=Font, Sound=Sound, x=400, y=225, Delay=0.1, Title="Options"}));
	GUI_AddCtrl(GUI, Control_Create(3, "Menu Item.lua", {Font=Font, Sound=Sound, x=400, y=275, Delay=0.2, Title="Instructions"}));
	GUI_AddCtrl(GUI, Control_Create(4, "Menu Item.lua", {Font=Font, Sound=Sound, x=400, y=325, Delay=0.3, Title="Credits"}));
	GUI_AddCtrl(GUI, Control_Create(5, "Menu Item.lua", {Font=Font, Sound=Sound, x=400, y=375, Delay=0.4, Title="Exit"}));
	GUI_SetNavMode(GUI, Bit_or(NAV_UPDOWN, NAV_CYCLED));
	GUI_SetCursor(GUI, Spr);
	GUI_SetFocus(GUI, 1);
	GUI_Enter(GUI);

	LastID=0;

	return true;
end

function ReleaseResource()  -- RUGE Callback Function
	GUI_Free(GUI);
	Sprite_Free(Spr);
	Font_Free(Font);
	Audio_Free(Sound);
	Texture_Free(Tex);
	Texture_Free(Quad.Tex);
end

function Frame(Delta)  -- RUGE Callback Function
	if Input_KeyPressed(VK_ESCAPE) then
		LastID=5;
		GUI_Exit(GUI);
	end

	local ID=GUI_Update(GUI, Delta);

	if ID==-1 then
		if LastID==5 then return true;
		else
			GUI_SetFocus(GUI, 1);
			GUI_Enter(GUI);
		end
	elseif ID>0 then
		LastID=ID;
		GUI_Exit(GUI);
	end

	local t=Timer_GetTime();
	local tu=50*math.cos(t/60);
	local tv=50*math.sin(t/60);

	Quad.v[1].tu=tu;
	Quad.v[1].tv=tv;
	Quad.v[2].tu=tu+800/64;
	Quad.v[2].tv=tv;
	Quad.v[3].tu=tu+800/64;
	Quad.v[3].tv=tv+600/64;
	Quad.v[4].tu=tu;
	Quad.v[4].tv=tv+600/64;

	return false;
end

function Render()  -- RUGE Callback Function
	Gfx_Clear();
	Gfx_RenderQuad(Quad);
	GUI_Render(GUI);

	local Str=string.format("FPS: %d", Timer_GetFPS());
	local n=0;
	local Rect=
	{
		Left=0,
		Top=0,
		Right=0,
		Bottom=0
	};

	n, Rect=Font_DrawText(Font, Str, Rect, 0, DT_CALCRECT);
	Font_DrawText(Font, Str, Rect);
end
