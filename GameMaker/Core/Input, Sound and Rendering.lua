function Boom()
	local Pan=math.floor((x-400)/4);
	local Pitch=(dx^2+dy^2)*0.0005+0.2;

	Effect_Play(Audio, 100, Pan, Pitch);
end

function InitEngine()  -- RUGE Callback Function
	System_SetState(APP_CAPTION, "Input, Sound and Rendering");
	System_SetState(APP_VSYNC, VSYNC_ONE);
end

function InitResource()  -- RUGE Callback Function
	x, y=100, 100;
	dx, dy=0, 0;
	Acceleration, Friction=90, 0.98;
	Font=Font_Create(20, 0, 0, false, "Î¢ÈíÑÅºÚ");
	Audio=Effect_Load("menu.wav");
	Quad=
	{
		v=
		{
			{x=100, y=100, z=0.5, Color=0xFFFFA000, tu=96/128, tv=64/128},
			{x=100, y=100, z=0.5, Color=0xFFFFA000, tu=128/128, tv=64/128},
			{x=100, y=100, z=0.5, Color=0xFFFFA000, tu=128/128, tv=96/128},
			{x=100, y=100, z=0.5, Color=0xFFFFA000, tu=96/128, tv=96/128}
		},
		Tex=Texture_Load("particles.png"),
		Blend=BLEND_DEFAULT
	}
	return true;
end

function ReleaseResource()  -- RUGE Callback Function
	Texture_Free(Quad.Tex);
	Audio_Free(Audio);
	Font_Free(Font);
end

function Frame(Delta)  -- RUGE Callback Function
	if Input_KeyPressed(VK_ESCAPE) then return true; end
	if Input_KeyPressed(VK_LEFT) then dx=dx-Acceleration*Delta; end
	if Input_KeyPressed(VK_RIGHT) then dx=dx+Acceleration*Delta; end
	if Input_KeyPressed(VK_UP) then dy=dy-Acceleration*Delta; end
	if Input_KeyPressed(VK_DOWN) then dy=dy+Acceleration*Delta; end

	dx=dx*Friction;
	dy=dy*Friction;
	x=x+dx;
	y=y+dy;

	if x>784 then
		x=784-(x-784);
		dx=-dx;
		Boom();
	end
	if x<16 then
		x=16+16-x;
		dx=-dx;
		Boom();
	end
	if y>584 then
		y=584-(y-584);
		dy=-dy;
		Boom();
	end
	if y<16 then
		y=16+16-y;
		dy=-dy;
		Boom();
	end

	Quad.v[1].x=x-16;
	Quad.v[1].y=y-16;

	Quad.v[2].x=x+16;
	Quad.v[2].y=y-16;

	Quad.v[3].x=x+16;
	Quad.v[3].y=y+16;

	Quad.v[4].x=x-16;
	Quad.v[4].y=y+16;

	return false;
end

function Render()  -- RUGE Callback Function
	Gfx_Clear();
	Gfx_RenderQuad(Quad);

	local Rect=
	{
		Left=0,
		Top=0,
		Right=100,
		Bottom=20,
	};

	Font_DrawText(Font, string.format("FPS: %d", Timer_GetFPS()), Rect);
end
