function Boom()
	local Pan=math.floor((x-400)/4);
	local Pitch=(dx^2+dy^2)*0.0005+0.2;

	Effect_Play(Audio, 100, Pan, Pitch);
end

function InitEngine()  -- RUGE Callback Function
	System_SetState(APP_CAPTION, "Rendering to Texture");
	System_SetState(APP_VSYNC, VSYNC_ONE);
end

function InitResource()  -- RUGE Callback Function
	x, y=100, 100;
	dx, dy=0, 0;
	Acceleration, Friction=90, 0.98;

	Targ=Target_Create(800, 600);
	Font=Font_Create(20, 0, 0, false, "Î¢ÈíÑÅºÚ");
	Audio=Effect_Load("menu.wav");
	Tex=Texture_Load("particles.png");

	sprTarg=Sprite_Create(Target_GetTexture(Targ), 0, 0, 800, 600);

	Spr=Sprite_Create(Tex, 96, 64, 32, 32);
	Sprite_SetColor(Spr, 0xFFFFA000);
	Sprite_SetHotSpot(Spr, 16, 16);

	Spt=Sprite_Create(Tex, 96, 64, 32, 32);
	Sprite_SetBlendMode(Spt, Bit_or(BLEND_COLORMUL, BLEND_ALPHAADD, BLEND_NOZWRITE));
	Sprite_SetHotSpot(Spt, 16, 16);

	Par=ParticleSystem_Create("trail.psi", Spt);
	ParticleSystem_Fire(Par);

	return true;
end

function ReleaseResource()  -- RUGE Callback Function
	ParticleSystem_Free(Par);
	Sprite_Free(Spt);
	Sprite_Free(Spr);
	Sprite_Free(sprTarg);
	Texture_Free(Tex);
	Audio_Free(Audio);
	Font_Free(Font);
	Target_Free(Targ);
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

	Info=ParticleSystem_GetInfo(Par);
	Info.Emission=math.floor(dx^2+dy^2)*2;
	ParticleSystem_SetInfo(Par, Info);
	ParticleSystem_MoveTo(Par, x, y);
	ParticleSystem_Update(Par, Delta);

	Sprite_SetTexture(sprTarg, Target_GetTexture(Targ));

	return false;
end

function Render()  -- RUGE Callback Function
	Gfx_BeginTarget(Targ);
	Gfx_Clear();
	Sprite_Render(Spr, x, y);
	ParticleSystem_Render(Par);

	local Rect=
	{
		Left=0,
		Top=0,
		Right=100,
		Bottom=20,
	};

	Font_DrawText(Font, string.format("FPS: %d", Timer_GetFPS()), Rect);
	Gfx_EndTarget();

	Gfx_Clear();
	Sprite_Render(sprTarg, 0, 0);
	Sprite_RenderEx(sprTarg, 600, 0, 0, 0.25);
end
