require "Common Const"

function Construct(this)
	bGameOver=true;
	Res=0;
	Font=NULL;
	Tex=NULL;
	Music=NULL;
	Sound=NULL;
	Channel=NULL;
	Spr=NULL;
	Spt=NULL;
	sprStar=NULL;
	Par=NULL;
	x=400;
	y=300;
	dx=0;
	dy=0;
	Speed=200;

	StarInfo={};
	for i=1, STARCNT do
		StarInfo[i]=
		{
			x=0,
			y=0,
			dx=0,
			dy=0,
			Rot=0
		};
	end
end

function Enter(this, Param)
	Random_Seed(os.time());

	Font=Font_Create(100, 0, 0, false, "Î¢ÈíÑÅºÚ");
	Tex=Texture_Load("particles.png");
	Music=Music_Load("Background.mid");
	Sound=Effect_Load("Lost.wav");

	Spr=Sprite_Create(Tex, 96, 64, 32, 32);
	Sprite_SetColor(Spr, 0xFFFFF000);
	Sprite_SetHotSpot(Spr, 16, 16);

	Spt=Sprite_Create(Tex, 96, 64, 32, 32);
	Sprite_SetBlendMode(Spt, Bit_or(BLEND_COLORMUL, BLEND_ALPHAADD, BLEND_NOZWRITE));
	Sprite_SetHotSpot(Spt, 16, 16);

	Par=ParticleSystem_Create("trail.psi", Spt);
	ParticleSystem_Fire(Par);

	sprStar=Sprite_Create(Tex, 32, 32, 32, 32);
	Sprite_SetColor(sprStar, 0xFFFFA000);
	Sprite_SetHotSpot(sprStar, 16, 16);

	if Param.Mode==ENTER_START or bGameOver then
		bGameOver=false;
		Res=0;
		x=400;
		y=300;
		for i=1, STARCNT-3, 4 do
			StarInfo[i].x=Random_Float(0, 800);
			StarInfo[i].y=Random_Float(-128, -16);

			StarInfo[i+1].x=Random_Float(0, 800);
			StarInfo[i+1].y=Random_Float(616, 728);

			StarInfo[i+2].x=Random_Float(-128, -16);
			StarInfo[i+2].y=Random_Float(0, 600);

			StarInfo[i+3].x=Random_Float(816, 928);
			StarInfo[i+3].y=Random_Float(0, 600);
		end
	end

	Channel=Music_Play(Music);

	return true;
end

function Exit(this)
	Sprite_Free(sprStar);
	ParticleSystem_Free(Par);
	Sprite_Free(Spt);
	Sprite_Free(Spr);
	Audio_Free(Sound);
	Audio_Free(Music);
	Texture_Free(Tex);
	Font_Free(Font);
end

function Update(this, Delta)
	if Input_KeyPressed(VK_ESCAPE) then
		SceneManager_Switch(Scene_GetManager(this), SCENE_MENU);
		return false;
	end

	if bGameOver then
		if Input_KeyPressed(VK_RETURN) then
			SceneManager_Switch(Scene_GetManager(this), SCENE_MENU);
			return false;
		end
	else
		Res=Res+Delta;

		dx, dy=0, 0;

		if Input_KeyPressed(VK_LEFT) then dx=-Speed*Delta; end
		if Input_KeyPressed(VK_RIGHT) then dx=Speed*Delta; end
		if Input_KeyPressed(VK_UP) then dy=-Speed*Delta; end
		if Input_KeyPressed(VK_DOWN) then dy=Speed*Delta; end

		x=x+dx;
		if x<16 then x=16; end
		if x>784 then x=784; end

		y=y+dy;
		if y<16 then y=16; end
		if y>584 then y=584; end

		if dx~=0 or dy~=0 then
			local Info={Emission=50};
			ParticleSystem_SetInfo(Par, Info);
		else
			local Info={Emission=0};
			ParticleSystem_SetInfo(Par, Info);
		end
		ParticleSystem_MoveTo(Par, x, y);
		ParticleSystem_Update(Par, Delta);

		for i=1, STARCNT do
			if StarInfo[i].x<=-16 or StarInfo[i].x>=816 or StarInfo[i].y<=-16 or StarInfo[i].y>=616 then
				local Rate=Random_Float(Speed*0.5, Speed*1.5)/math.sqrt((x-StarInfo[i].x)^2+(y-StarInfo[i].y)^2);

				StarInfo[i].dx=(x-StarInfo[i].x)*Rate;
				StarInfo[i].dy=(y-StarInfo[i].y)*Rate;
			end

			StarInfo[i].x=StarInfo[i].x+StarInfo[i].dx*Delta;
			StarInfo[i].y=StarInfo[i].y+StarInfo[i].dy*Delta;

			StarInfo[i].Rot=StarInfo[i].Rot+Delta*5;

			if (x-StarInfo[i].x)^2+(y-StarInfo[i].y)^2<=16^2 then
				bGameOver=true;
				Effect_Play(Sound);
				Channel_Stop(Channel);
				break;
			end
		end
	end

	return false;
end

function Render(this)
	Sprite_Render(Spr, x, y);
	ParticleSystem_Render(Par);
	for i=1, STARCNT do
		Sprite_RenderEx(sprStar, StarInfo[i].x, StarInfo[i].y, StarInfo[i].Rot);
	end

	if bGameOver then
		local Rect=
		{
			Left=0,
			Top=0,
			Right=800,
			Bottom=600
		};
		local Str=string.format("ÓÎÏ·½áÊø\nÄúµÄ³É¼¨: %f", Res);

		Font_DrawText(Font, Str, Rect, 0, Bit_or(DT_CENTER, DT_VCENTER));
	end
end
