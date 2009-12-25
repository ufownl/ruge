SCREEN_WIDTH=800;
SCREEN_HEIGHT=600;
NUM_STARS=100;
SEA_SUBDIVISION=16;

SKY_HEIGHT=SCREEN_HEIGHT*0.6;
STARS_HEIGHT=SKY_HEIGHT*0.9;
ORBITS_RADIUS=SCREEN_WIDTH*0.43;

SkyTopColors={0xFF15092A, 0xFF6C6480, 0xFF89B9D0};
SkyBtmColors={0xFF303E57, 0xFFAC7963, 0xFFCAD7DB};
SeaTopColors={0xFF3D546B, 0xFF927E76, 0xFF86A2AD};
SeaBtmColors={0xFF1E394C, 0xFF2F4E64, 0xFF2F4E64};

Seq={1, 1, 2, 3, 3, 3, 2, 1, 1};

function InitEngine()  -- RUGE Callback Function
	System_SetState(APP_CAPTION, "The Big Calm");
	System_SetState(APP_VSYNC, VSYNC_ONE);
	System_SetState(APP_MAGFILTER, TEXF_LINEAR);
	System_SetState(APP_MINFILTER, TEXF_LINEAR);
end

function InitResource()  -- RUGE Callback Function
	Font=Font_Create(20, 0, 0, false, "Fixedsys");
	Tex=Texture_Load("objects.png");

	sprSky=Sprite_Create(nil, 0, 0, SCREEN_WIDTH, SKY_HEIGHT);
	disSea=DistortionMesh_Create(SEA_SUBDIVISION, SEA_SUBDIVISION);
	DistortionMesh_SetTextureRect(disSea, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT-SKY_HEIGHT);

	sprSun=Sprite_Create(Tex, 81, 0, 114, 114);
	Sprite_SetHotSpot(sprSun, 57, 57);
	sprMoon=Sprite_Create(Tex, 0, 0, 81, 81);
	Sprite_SetHotSpot(sprMoon, 40, 40);
	sprStar=Sprite_Create(Tex, 72, 81, 9, 9);
	Sprite_SetHotSpot(sprStar, 5, 5);

	sprGlow=Sprite_Create(Tex, 128, 128, 128, 128);
	Sprite_SetHotSpot(sprGlow, 64, 64);
	Sprite_SetBlendMode(sprGlow, Bit_or(BLEND_COLORADD, BLEND_ALPHABLEND, BLEND_NOZWRITE));
	sprSeaGlow=Sprite_Create(Tex, 128, 224, 128, 32);
	Sprite_SetHotSpot(sprSeaGlow, 64, 0);
	Sprite_SetBlendMode(sprSeaGlow, Bit_or(BLEND_COLORADD, BLEND_ALPHAADD, BLEND_NOZWRITE));

	colWhite=Color_SetColor(0xFFFFFFFF);
	Time=os.time()%86400/3600+8;
	SpeedMode=-1;
	Speed=0;

	StarX={};
	StarY={};
	StarS={};
	for i=1, NUM_STARS do
		StarX[i]=Random_Float(0, SCREEN_WIDTH);
		StarY[i]=Random_Float(0, STARS_HEIGHT);
		StarS[i]=Random_Float(0.1, 0.7);
	end

	SeaP={};

	for i=1, SEA_SUBDIVISION do
		SeaP[i]=i+Random_Float(-15.0, 15.0);
	end

	return true;
end

function ReleaseResource()  -- RUGE Callback Function
	Sprite_Free(sprSeaGlow);
	Sprite_Free(sprGlow);
	Sprite_Free(sprStar);
	Sprite_Free(sprMoon);
	Sprite_Free(sprSun);
	Sprite_Free(sprSky);
	DistortionMesh_Free(disSea);
	Texture_Free(Tex);
	Font_Free(Font);
end

function Frame(Delta)  -- RUGE Callback Function
	local VKey=Input_GetKey();

	if VKey>0 then
		if VKey==VK_ESCAPE then return true;
		elseif VKey==VK_UP then
			if SpeedMode<8 then SpeedMode=SpeedMode+1; end
		elseif VKey==VK_DOWN then
			if SpeedMode>-1 then SpeedMode=SpeedMode-1; end
		elseif VKey==VK_RETURN then
			SpeedMode=-1;
		end
		if SpeedMode==-1 then Speed=0;
		else Speed=2^SpeedMode/10; end
	end

	if Speed==0 then Time=os.time()%86400/3600+8;
	else
		Time=Time+Delta*Speed;
		if Time>=24 then Time=Time-24; end
	end

	SeqID=math.floor(Time/3);
	SeqResidue=Time/3-SeqID;

	local col1={};
	local col2={};

	col1=Color_SetColor(SkyTopColors[Seq[SeqID+1]]);
	col2=Color_SetColor(SkyTopColors[Seq[SeqID+2]]);
	colSkyTop=Color_Add(Color_Mul(col2, SeqResidue), Color_Mul(col1, 1-SeqResidue));

	col1=Color_SetColor(SkyBtmColors[Seq[SeqID+1]]);
	col2=Color_SetColor(SkyBtmColors[Seq[SeqID+2]]);
	colSkyBtm=Color_Add(Color_Mul(col2, SeqResidue), Color_Mul(col1, 1-SeqResidue));

	col1=Color_SetColor(SeaTopColors[Seq[SeqID+1]]);
	col2=Color_SetColor(SeaTopColors[Seq[SeqID+2]]);
	colSeaTop=Color_Add(Color_Mul(col2, SeqResidue), Color_Mul(col1, 1-SeqResidue));

	col1=Color_SetColor(SeaBtmColors[Seq[SeqID+1]]);
	col2=Color_SetColor(SeaBtmColors[Seq[SeqID+2]]);
	colSeaBtm=Color_Add(Color_Mul(col2, SeqResidue), Color_Mul(col1, 1-SeqResidue));

	local a=0;
	StarA={};

	if SeqID>=6 or SeqID<2 then
		for i=1, NUM_STARS do
			a=1-StarY[i]/STARS_HEIGHT;
			a=a*Random_Float(0.6, 1.0);
			if SeqID>=6 then a=a*math.sin((Time-18)/6*M_PI_2);
			else a=a*math.sin((1-Time/6)*M_PI_2); end
			StarA[i]=a;
		end
	end

	if SeqID==2 then a=math.sin(SeqResidue*M_PI_2);
	elseif SeqID==5 then a=math.cos(SeqResidue*M_PI_2);
	elseif SeqID>2 and SeqID<5 then a=1;
	else a=0; end

	colSun=Color_SetColor(0xFFEAE1BE);
	colSun=Color_Add(Color_Mul(colSun, 1-a), Color_Mul(colWhite, a));

	colSunGlow={};

	a=(math.cos(Time/6*M_PI)+1)/2;
	if SeqID>=2 and SeqID<=6 then
		colSunGlow=Color_Mul(colWhite, a);
		colSunGlow.a=1;
	else colSunGlow=Color_SetColor(0xFF000000); end

	local Zenith=-(Time/12*M_PI-M_PI_2);

	SunX=SCREEN_WIDTH*0.5+math.cos(Zenith)*ORBITS_RADIUS;
	SunY=SKY_HEIGHT*1.2+math.sin(Zenith)*ORBITS_RADIUS;
	SunS=1-0.3*math.sin((Time-6)/12*M_PI);
	SunGlowS=3*(1-a)+3;

	if SeqID>=6 then a=math.sin((Time-18)/6*M_PI_2);
	else a=math.sin((1-Time/6)*M_PI_2); end

	colMoon=Color_SetColor(0x20FFFFFF);
	colMoon=Color_Add(Color_Mul(colMoon, 1-a), Color_Mul(colWhite, a));

	colMoonGlow=
	{
		a=0.5*a,
		r=colWhite.r,
		g=colWhite.g,
		b=colWhite.b
	};

	MoonX=SCREEN_WIDTH*0.5+math.cos(Zenith-M_PI)*ORBITS_RADIUS;
	MoonY=SKY_HEIGHT*1.2+math.sin(Zenith-M_PI)*ORBITS_RADIUS;
	MoonS=1-0.3*math.sin((Time+6)/12*M_PI);
	MoonGlowS=a*0.4+0.5;

	colSeaGlow={};

	if Time>19 or Time<4.5 then
		a=0.2;

		if Time>19 and Time<20 then a=a*(Time-19);
		elseif Time>3.5 and Time<4.5 then a=a*(1.0-(Time-3.5)); end

		colSeaGlow=
		{
			a=a,
			r=colMoonGlow.r,
			g=colMoonGlow.g,
			b=colMoonGlow.b
		};
		SeaGlowX=MoonX;
		SeaGlowSX=MoonGlowS*3;
		SeaGlowSY=MoonGlowS*2;
	elseif Time>6.5 and Time<19 then
		a=0.3;
		if Time<7.5 then a=a*(Time-6.5);
		elseif Time>18 then a=a*(1-(Time-18)); end

		colSeaGlow=
		{
			a=a,
			r=colSunGlow.r,
			g=colSunGlow.g,
			b=colSunGlow.b
		};
		SeaGlowX=SunX;
		SeaGlowSX=SunGlowS;
		SeaGlowSY=SunGlowS*0.6;
	else colSeaGlow.a=0; end

	local Color1, Color2=0, 0;

	for i=1, SEA_SUBDIVISION-2 do
		a=i/(SEA_SUBDIVISION-1);
		col1=Color_Add(Color_Mul(colSeaTop, 1-a), Color_Mul(colSeaBtm, a));
		Color1=Color_GetColor(col1);
		a=a*20;

		local t=2*Timer_GetTime();

		for j=0, SEA_SUBDIVISION-1 do
			local dy=a*math.sin(SeaP[i+1]+(j/(SEA_SUBDIVISION-1)-0.5)*M_PI*16-t);

			DistortionMesh_SetColor(disSea, i, j, Color1);
			DistortionMesh_SetDisplacement(disSea, i, j, 0, dy, DISP_NODE);
		end
	end

	Color1=Color_GetColor(colSeaTop);
	Color2=Color_GetColor(colSeaBtm);

	for j=0, SEA_SUBDIVISION-1 do
		DistortionMesh_SetColor(disSea, 0, j, Color1);
		DistortionMesh_SetColor(disSea, SEA_SUBDIVISION-1, j, Color2);
	end

	local PosX=0;

	if Time>19 or Time<5 then
		a=0.12;
		if Time>19 and Time<20 then a=a*(Time-19);
		elseif Time>4 and Time<5 then a=a*(1-(Time-4)); end
		PosX=MoonX;
	elseif Time>7 and Time<17 then
		a=0.14;
		if Time<8 then a=a*(Time-7);
		elseif Time>16 then a=a*(1-(Time-16)); end
		PosX=SunX;
	else a=0; end

	local CellW=SCREEN_WIDTH/(SEA_SUBDIVISION-1);

	if a~=0 then
		local k=math.floor(PosX/CellW);
		local s1=1-(PosX-k*CellW)/CellW;
		local s2=1-((k+1)*CellW-PosX)/CellW;

		if s1>0.7 then s1=0.7 end
		if s2>0.7 then s2=0.7 end

		s1=s1*a;
		s2=s2*a;

		for i=0, SEA_SUBDIVISION-1, 2 do
			a=math.sin(i/(SEA_SUBDIVISION-1)*M_PI_2);

			col1=Color_SetColor(DistortionMesh_GetColor(disSea, i, k));
			col1=Color_Add(col1, Color_Mul(Color_Mul(colSun, s1), 1-a));
			col1=Color_Clamp(col1);
			DistortionMesh_SetColor(disSea, i, k, Color_GetColor(col1));

			col1=Color_SetColor(DistortionMesh_GetColor(disSea, i, k+1));
			col1=Color_Add(col1, Color_Mul(Color_Mul(colSun, s2), 1-a));
			col1=Color_Clamp(col1);
			DistortionMesh_SetColor(disSea, i, k+1, Color_GetColor(col1));
		end
	end

	return false;
end

function Render()  -- RUGE Callback Function
	Gfx_Clear();

	Sprite_SetColor(sprSky, Color_GetColor(colSkyTop), 0);
	Sprite_SetColor(sprSky, Color_GetColor(colSkyTop), 1);
	Sprite_SetColor(sprSky, Color_GetColor(colSkyBtm), 2);
	Sprite_SetColor(sprSky, Color_GetColor(colSkyBtm), 3);
	Sprite_Render(sprSky, 0, 0);

	if SeqID>=6 or SeqID<2 then
		for i=0, NUM_STARS-1 do
			Sprite_SetColor(sprStar, Bit_or(Bit_lsh(StarA[i+1]*255, 24), 0xFFFFFF));
			Sprite_RenderEx(sprStar, StarX[i+1], StarY[i+1], 0, StarS[i+1]);
		end
	end

	Sprite_SetColor(sprGlow, Color_GetColor(colSunGlow));
	Sprite_RenderEx(sprGlow, SunX, SunY, 0, SunGlowS);
	Sprite_SetColor(sprSun, Color_GetColor(colSun));
	Sprite_RenderEx(sprSun, SunX, SunY, 0, SunS);

	Sprite_SetColor(sprGlow, Color_GetColor(colMoonGlow));
	Sprite_RenderEx(sprGlow, MoonX, MoonY, 0, MoonGlowS);
	Sprite_SetColor(sprMoon, Color_GetColor(colMoon));
	Sprite_RenderEx(sprMoon, MoonX, MoonY, 0, MoonS);

	DistortionMesh_Render(disSea, 0, SKY_HEIGHT);
	Sprite_SetColor(sprSeaGlow, Color_GetColor(colSeaGlow));
	Sprite_RenderEx(sprSeaGlow, SeaGlowX, SKY_HEIGHT, 0, SeaGlowSX, SeaGlowSY);

	local Hrs=math.floor(Time);
	local Temp=(Time-Hrs)*60;
	local Mins=math.floor(Temp);
	local Secs=math.floor((Temp-Mins)*60);
	local Rect=
	{
		Left=0,
		Top=0,
		Right=SCREEN_WIDTH,
		Bottom=SCREEN_HEIGHT
	};

	Font_DrawText(Font, string.format("%02d:%02d:%02d\nSpeed: %d\nFPS: %d",
		Hrs, Mins, Secs, SpeedMode+1, Timer_GetFPS()), Rect);
end
