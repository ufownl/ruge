function InitEngine()  -- RUGE Callback Function
	System_SetState(APP_CAPTION, "Using Distortion Mesh");
	System_SetState(APP_VSYNC, VSYNC_ONE);
end

function InitResource()  -- RUGE Callback Function
	Rows, Cols=16, 16;
	CellW, CellH=512/(Cols-1), 512/(Rows-1);
	DisX, DisY=144, 44;

	Time=0;
	Trans=0;

	Font=Font_Create(20, 0, 0, false, "Î¢ÈíÑÅºÚ");
	Tex=Texture_Load("texture.jpg");

	Dis=DistortionMesh_Create(Rows, Cols);
	DistortionMesh_SetTexture(Dis, Tex);
	DistortionMesh_SetTextureRect(Dis, 0, 0, 512, 512);
	DistortionMesh_SetBlendMode(Dis, Bit_or(BLEND_COLORADD, BLEND_ALPHABLEND, BLEND_NOZWRITE));
	DistortionMesh_Clear(Dis, XRGB(0, 0, 0));

	return true;
end

function ReleaseResource()  -- RUGE Callback Function
	DistortionMesh_Free(Dis);
	Texture_Free(Tex);
	Font_Free(Font);
end

function Frame(Delta)  -- RUGE Callback Function
	Time=Time+Delta;

	if Input_GetKey()==VK_ESCAPE then return true;
	elseif Input_GetKey()==VK_SPACE then
		Trans=(Trans+1)%3;
		DistortionMesh_Clear(Dis, XRGB(0, 0, 0));
	end

	if Trans==0 then
		for i=1, Rows-2 do
			for j=1, Cols-2 do
				DistortionMesh_SetDisplacement(Dis, i, j, math.cos(Time*10+(i+j)/2)*5, math.sin(Time*10+(i+j)/2)*5, DISP_NODE);
			end
		end
	elseif Trans==1 then
		for i=0, Rows-1 do
			for j=1, Cols-2 do
				local Color=math.floor((math.cos(Time*5+(i+j)/2)+1)*35);

				DistortionMesh_SetDisplacement(Dis, i, j, math.cos(Time*5+j/2)*15, 0, DISP_NODE);
				DistortionMesh_SetColor(Dis, i, j, Bit_or(Bit_lsh(255, 24), Bit_lsh(Color, 16), Bit_lsh(Color, 8), Color));
			end
		end
	elseif Trans==2 then
		for i=0, Rows-1 do
			for j=0, Cols-1 do
				local fr=math.sqrt((j-Cols/2)^2+(i-Rows/2)^2);
				local fa=fr*math.cos(Time*2)*0.1;
				local fdx=math.sin(fa)*(i*CellH-256)+math.cos(fa)*(j*CellW-256);
				local fdy=math.cos(fa)*(i*CellH-256)-math.sin(fa)*(j*CellW-256);
				local Color=(math.cos(fr+Time*4)+1)*40;

				DistortionMesh_SetDisplacement(Dis, i, j, fdx, fdy, DISP_CENTER);
				DistortionMesh_SetColor(Dis, i, j, Bit_or(Bit_lsh(255, 24), Bit_lsh(Color, 16), Bit_lsh(Color/2, 8), 0));
			end
		end
	end

	return false;
end

function Render()  -- RUGE Callback Function
	Gfx_Clear();
	DistortionMesh_Render(Dis, DisX, DisY);

	local Rect=
	{
		Left=0,
		Top=0,
		Right=100,
		Bottom=20,
	};

	Font_DrawText(Font, string.format("FPS: %d", Timer_GetFPS()), Rect);
end
