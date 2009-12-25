PARTICLE_SIZE=32;

CMD_EXIT=1;
CMD_HELP=2;
CMD_PRESET1=3;
CMD_PRESET2=4;
CMD_PRESET3=5;
CMD_PRESET4=6;
CMD_PRESET5=7;
CMD_PRESET6=8;
CMD_PRESET7=9;
CMD_PRESET8=10;
CMD_PRESET9=11;
CMD_BOUNDINGBOX=12;
CMD_NPARTICLES=13;
CMD_FPS=14;

CMD_SYS_LIFETIME=15;
CMD_SYS_TLIFETIME=16;
CMD_SYS_LIFECONT=17;
CMD_SYS_EMISSION=18;
CMD_SYS_TEMISSION=19;
CMD_SYS_PARLIFETIMEMIN=20;
CMD_SYS_PARLIFETIMEMAX=21;
CMD_SYS_PARLIFETIMELOCK=22;
CMD_SYS_BLENDADDITIVE=23;
CMD_SYS_BLENDBLEND=24;
CMD_SYS_TEXTURE=25;

CMD_PM_DIRECTION=26;
CMD_PM_TDIRECTION=27;
CMD_PM_RELATIVE=28;
CMD_PM_SPREAD=29;
CMD_PM_TSPREAD=30;

CMD_PM_STARTSPEEDMIN=31;
CMD_PM_STARTSPEEDMAX=32;
CMD_PM_STARTSPEEDLOCK=33;

CMD_PM_GRAVITYMIN=34;
CMD_PM_GRAVITYMAX=35;
CMD_PM_GRAVITYLOCK=36;

CMD_PM_RADIALMIN=37;
CMD_PM_RADIALMAX=38;
CMD_PM_RADIALLOCK=39;

CMD_PM_TANGENTIALMIN=40;
CMD_PM_TANGENTIALMAX=41;
CMD_PM_TANGENTIALLOCK=42;

CMD_PA_SIZESTART=43;
CMD_PA_SIZEEND=44;
CMD_PA_SIZEVAR=45;
CMD_PA_SIZELOCK=46;

CMD_PA_SPINSTART=47;
CMD_PA_SPINEND=48;
CMD_PA_SPINVAR=49;
CMD_PA_SPINLOCK=50;

CMD_PA_ALPHASTART=51;
CMD_PA_ALPHAEND=52;
CMD_PA_ALPHAVAR=53;
CMD_PA_ALPHALOCK=54;

CMD_PA_RSTART=55;
CMD_PA_GSTART=56;
CMD_PA_BSTART=57;
CMD_PA_REND=58;
CMD_PA_GEND=59;
CMD_PA_BEND=60;
CMD_PA_RGBVAR=61;

function CreateGUI()
	--Presets & Stuff
	GUI_AddCtrl(GUI, Button_Create(CMD_EXIT, 718, 484, 73, 17, texGUI, 336, 191));
	local Btn=Button_Create(CMD_HELP, 641, 484, 73, 17, texGUI, 336, 191);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);

	Btn=Button_Create(CMD_PRESET1, 641, 389, 16, 15, texGUI, 384, 176);
	Button_SetMode(Btn, true);
	Button_SetState(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Btn=Button_Create(CMD_PRESET2, 657, 389, 16, 15, texGUI, 384, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Btn=Button_Create(CMD_PRESET3, 673, 389, 16, 15, texGUI, 384, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Btn=Button_Create(CMD_PRESET4, 689, 389, 16, 15, texGUI, 384, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Btn=Button_Create(CMD_PRESET5, 705, 389, 16, 15, texGUI, 384, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Btn=Button_Create(CMD_PRESET6, 721, 389, 16, 15, texGUI, 384, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Btn=Button_Create(CMD_PRESET7, 737, 389, 16, 15, texGUI, 384, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Btn=Button_Create(CMD_PRESET8, 753, 389, 16, 15, texGUI, 384, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Btn=Button_Create(CMD_PRESET9, 769, 389, 16, 15, texGUI, 384, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);

	Btn=Button_Create(CMD_BOUNDINGBOX, 641, 417, 8, 8, texGUI, 368, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);

	--System parameters
	local Slider=Slider_Create(CMD_SYS_LIFETIME, 10, 44, 149, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 10, SLIDER_BAR);
	Slider_SetValue(Slider, 5);
	GUI_AddCtrl(GUI, Slider);
	Btn=Button_Create(CMD_SYS_LIFECONT, 9, 55, 8, 8, texGUI, 368, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);

	Slider=Slider_Create(CMD_SYS_EMISSION, 10, 91, 149, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1000, SLIDER_BAR);
	Slider_SetValue(Slider, 500);
	GUI_AddCtrl(GUI, Slider);

	Btn=Button_Create(CMD_SYS_PARLIFETIMELOCK, 144, 111, 16, 11, texGUI, 336, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Slider=Slider_Create(CMD_SYS_PARLIFETIMEMIN, 33, 126, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 5, SLIDER_BAR);
	Slider_SetValue(Slider, 2.5);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_SYS_PARLIFETIMEMAX, 33, 138, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 5, SLIDER_BAR);
	Slider_SetValue(Slider, 2.5);
	GUI_AddCtrl(GUI, Slider);

	Btn=Button_Create(CMD_SYS_BLENDADDITIVE, 72, 174, 8, 8, texGUI, 368, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Btn=Button_Create(CMD_SYS_BLENDBLEND, 72, 188, 8, 8, texGUI, 368, 176);
	Button_SetMode(Btn, true);
	Button_SetState(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Btn=Button_Create(CMD_SYS_TEXTURE, 10, 173, 32, 32, texGUI, 336, 338);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);

	--Particle movement
	Slider=Slider_Create(CMD_PM_DIRECTION, 9, 267, 149, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 2*M_PI, SLIDER_BAR);
	Slider_SetValue(Slider, M_PI);
	GUI_AddCtrl(GUI, Slider);
	Btn=Button_Create(CMD_PM_RELATIVE, 8, 278, 8, 8, texGUI, 368, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);

	Slider=Slider_Create(CMD_PM_SPREAD, 9, 314, 149, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 2*M_PI, SLIDER_BAR);
	Slider_SetValue(Slider, M_PI);
	GUI_AddCtrl(GUI, Slider);

	Btn=Button_Create(CMD_PM_STARTSPEEDLOCK, 143, 334, 16, 11, texGUI, 336, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Slider=Slider_Create(CMD_PM_STARTSPEEDMIN, 32, 349, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, -300, 300, SLIDER_BARRELATIVE);
	Slider_SetValue(Slider, 0);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PM_STARTSPEEDMAX, 32, 361, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, -300, 300, SLIDER_BARRELATIVE);
	Slider_SetValue(Slider, 0);
	GUI_AddCtrl(GUI, Slider);

	Btn=Button_Create(CMD_PM_GRAVITYLOCK, 143, 381, 16, 11, texGUI, 336, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Slider=Slider_Create(CMD_PM_GRAVITYMIN, 32, 396, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, -900, 900, SLIDER_BARRELATIVE);
	Slider_SetValue(Slider, 0);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PM_GRAVITYMAX, 32, 408, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, -900, 900, SLIDER_BARRELATIVE);
	Slider_SetValue(Slider, 0);
	GUI_AddCtrl(GUI, Slider);

	Btn=Button_Create(CMD_PM_RADIALLOCK, 143, 428, 16, 11, texGUI, 336, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Slider=Slider_Create(CMD_PM_RADIALMIN, 32, 443, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, -900, 900, SLIDER_BARRELATIVE);
	Slider_SetValue(Slider, 0);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PM_RADIALMAX, 32, 455, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, -900, 900, SLIDER_BARRELATIVE);
	Slider_SetValue(Slider, 0);
	GUI_AddCtrl(GUI, Slider);

	Btn=Button_Create(CMD_PM_TANGENTIALLOCK, 143, 475, 16, 11, texGUI, 336, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Slider=Slider_Create(CMD_PM_TANGENTIALMIN, 32, 490, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, -900, 900, SLIDER_BARRELATIVE);
	Slider_SetValue(Slider, 0);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PM_TANGENTIALMAX, 32, 502, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, -900, 900, SLIDER_BARRELATIVE);
	Slider_SetValue(Slider, 0);
	GUI_AddCtrl(GUI, Slider);

	--Particle appearance
	Btn=Button_Create(CMD_PA_SIZELOCK, 775, 29, 16, 11, texGUI, 336, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Slider=Slider_Create(CMD_PA_SIZESTART, 664, 44, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 1, 100, SLIDER_BAR);
	Slider_SetValue(Slider, 32);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PA_SIZEEND, 664, 56, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 1, 100, SLIDER_BAR);
	Slider_SetValue(Slider, 32);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PA_SIZEVAR, 664, 68, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1, SLIDER_BAR);
	Slider_SetValue(Slider, 0.5);
	GUI_AddCtrl(GUI, Slider);

	Btn=Button_Create(CMD_PA_SPINLOCK, 775, 88, 16, 11, texGUI, 336, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Slider=Slider_Create(CMD_PA_SPINSTART, 664, 103, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, -50, 50, SLIDER_BARRELATIVE);
	Slider_SetValue(Slider, 0);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PA_SPINEND, 664, 115, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, -50, 50, SLIDER_BARRELATIVE);
	Slider_SetValue(Slider, 0);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PA_SPINVAR, 664, 127, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1, SLIDER_BAR);
	Slider_SetValue(Slider, 0.5);
	GUI_AddCtrl(GUI, Slider);

	Btn=Button_Create(CMD_PA_ALPHALOCK, 775, 147, 16, 11, texGUI, 336, 176);
	Button_SetMode(Btn, true);
	GUI_AddCtrl(GUI, Btn);
	Slider=Slider_Create(CMD_PA_ALPHASTART, 664, 162, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1, SLIDER_BAR);
	Slider_SetValue(Slider, 0.5);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PA_ALPHAEND, 664, 174, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1, SLIDER_BAR);
	Slider_SetValue(Slider, 0.5);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PA_ALPHAVAR, 664, 186, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1, SLIDER_BAR);
	Slider_SetValue(Slider, 0.5);
	GUI_AddCtrl(GUI, Slider);

	Slider=Slider_Create(CMD_PA_RSTART, 664, 221, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1, SLIDER_BAR);
	Slider_SetValue(Slider, 0.5);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PA_GSTART, 664, 233, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1, SLIDER_BAR);
	Slider_SetValue(Slider, 0.5);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PA_BSTART, 664, 245, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1, SLIDER_BAR);
	Slider_SetValue(Slider, 0.5);
	GUI_AddCtrl(GUI, Slider);

	Slider=Slider_Create(CMD_PA_REND, 664, 271, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1, SLIDER_BAR);
	Slider_SetValue(Slider, 0.5);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PA_GEND, 664, 283, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1, SLIDER_BAR);
	Slider_SetValue(Slider, 0.5);
	GUI_AddCtrl(GUI, Slider);
	Slider=Slider_Create(CMD_PA_BEND, 664, 295, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1, SLIDER_BAR);
	Slider_SetValue(Slider, 0.5);
	GUI_AddCtrl(GUI, Slider);

	Slider=Slider_Create(CMD_PA_RGBVAR, 664, 321, 126, 6, texGUI, 417, 177, 6, 6);
	Slider_SetMode(Slider, 0, 1, SLIDER_BAR);
	Slider_SetValue(Slider, 0.5);
	GUI_AddCtrl(GUI, Slider);

	--Text control
	local Text=Text_Create(CMD_FPS, 641, 454, 28, 16, Font);
	Text_SetMode(Text, Bit_or(DT_TOP, DT_RIGHT));
	Text_SetColor(Text, 0xFFD4C25A);
	GUI_AddCtrl(GUI, Text);
	Text=Text_Create(CMD_NPARTICLES, 641, 435, 28, 16, Font);
	Text_SetMode(Text, Bit_or(DT_TOP, DT_RIGHT));
	Text_SetColor(Text, 0xFFD4C25A);
	GUI_AddCtrl(GUI, Text);

	Text=Text_Create(CMD_SYS_TLIFETIME, 113, 26, 28, 16, Font);
	Text_SetMode(Text, Bit_or(DT_TOP, DT_RIGHT));
	Text_SetText(Text, "0");
	GUI_AddCtrl(GUI, Text);

	Text=Text_Create(CMD_SYS_TEMISSION, 103, 73, 28, 16, Font);
	Text_SetMode(Text, Bit_or(DT_TOP, DT_RIGHT));
	Text_SetText(Text, "0");
	GUI_AddCtrl(GUI, Text);

	Text=Text_Create(CMD_PM_TDIRECTION, 112, 249, 28, 16, Font);
	Text_SetMode(Text, Bit_or(DT_TOP, DT_RIGHT));
	Text_SetText(Text, "0");
	GUI_AddCtrl(GUI, Text);

	Text=Text_Create(CMD_PM_TSPREAD, 112, 296, 28, 16, Font);
	Text_SetMode(Text, Bit_or(DT_TOP, DT_RIGHT));
	Text_SetText(Text, "0");
	GUI_AddCtrl(GUI, Text);
end

function HandleKey(VKey)
	if VKey==VK_ESCAPE then return true;
	elseif VKey==VK_TAB then bIFace=not bIFace;
	elseif VKey==VK_LBUTTON then
		if bIFace then
			local x, y=Input_GetMousePos();

			if 168<=x and x<=631 then ParticleSystem_Fire(Par); end
		else ParticleSystem_Fire(Par); end
	elseif VKey==VK_SPACE then ParticleSystem_Fire(Par);
	elseif string.byte('1')<=VKey and VKey<=string.byte('9') then ChangePreset(VKey-string.byte('0')); end
	return false;
end

function HandleCommand(ID)
	if ID==CMD_EXIT then return true;
	elseif ID==CMD_HELP then bHelp=Button_GetState(GUI_GetCtrl(GUI, CMD_HELP));
	elseif ID==CMD_BOUNDINGBOX then bBBox=Button_GetState(GUI_GetCtrl(GUI, CMD_BOUNDINGBOX));
	elseif CMD_PRESET1<=ID and ID<=CMD_PRESET9 then ChangePreset(ID-CMD_PRESET1+1);
	elseif ID==CMD_SYS_LIFETIME then
		local Info={Lifetime=Slider_GetValue(GUI_GetCtrl(GUI, CMD_SYS_LIFETIME))};
		ParticleSystem_SetInfo(Par, Info);
		Text_SetText(GUI_GetCtrl(GUI, CMD_SYS_TLIFETIME), string.format("%.1f", Info.Lifetime));
		Button_SetState(GUI_GetCtrl(GUI, CMD_SYS_LIFECONT), false);
		ParticleSystem_Stop(Par);
	elseif ID==CMD_SYS_LIFECONT then
		if Button_GetState(GUI_GetCtrl(GUI, CMD_SYS_LIFECONT)) then
			local Info={Lifetime=-1};
			ParticleSystem_SetInfo(Par, Info);
			ParticleSystem_Fire(Par);
		else
			local Info={Lifetime=Slider_GetValue(GUI_GetCtrl(GUI, CMD_SYS_LIFETIME))};
			ParticleSystem_SetInfo(Par, Info);
			ParticleSystem_Stop(Par);
		end
	elseif ID==CMD_SYS_EMISSION then
		local Info={Emission=math.floor(Slider_GetValue(GUI_GetCtrl(GUI, CMD_SYS_EMISSION)))};
		ParticleSystem_SetInfo(Par, Info);
		Text_SetText(GUI_GetCtrl(GUI, CMD_SYS_TEMISSION), string.format("%d", Info.Emission));
	elseif ID==CMD_SYS_PARLIFETIMELOCK then
		if Button_GetState(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMELOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMEMAX), Slider_GetValue(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMEMIN)));
			local Info={ParticleLifeMax=Slider_GetValue(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMEMIN))};
			ParticleSystem_SetInfo(Par, Info);
		end
	elseif ID==CMD_SYS_PARLIFETIMEMIN then
		local Info={ParticleLifeMin=Slider_GetValue(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMEMIN))};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMELOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMEMAX), Info.ParticleLifeMin);
			Info.ParticleLifeMax=Info.ParticleLifeMin;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_SYS_PARLIFETIMEMAX then
		local Info={ParticleLifeMax=Slider_GetValue(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMEMAX))};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMELOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMEMIN), Info.ParticleLifeMax);
			Info.ParticleLifeMin=Info.ParticleLifeMax;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_SYS_TEXTURE then Animation_SetFrame(animPar, Animation_GetFrame(animPar)+1);
	elseif ID==CMD_SYS_BLENDADDITIVE then
		Button_SetState(GUI_GetCtrl(GUI, CMD_SYS_BLENDADDITIVE), true);
		Button_SetState(GUI_GetCtrl(GUI, CMD_SYS_BLENDBLEND), false);
		Animation_SetBlendMode(animPar, Bit_or(BLEND_COLORMUL, BLEND_ALPHAADD, BLEND_ZWRITE));
	elseif ID==CMD_SYS_BLENDBLEND then
		Button_SetState(GUI_GetCtrl(GUI, CMD_SYS_BLENDADDITIVE), false);
		Button_SetState(GUI_GetCtrl(GUI, CMD_SYS_BLENDBLEND), true);
		Animation_SetBlendMode(animPar, Bit_or(BLEND_COLORMUL, BLEND_ALPHABLEND, BLEND_ZWRITE));
	elseif ID==CMD_PM_DIRECTION then
		local Info={Direction=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_DIRECTION))};
		ParticleSystem_SetInfo(Par, Info);
		Text_SetText(GUI_GetCtrl(GUI, CMD_PM_TDIRECTION), string.format("%d", math.floor(Info.Direction*180/M_PI)));
	elseif ID==CMD_PM_RELATIVE then
		local Info={Relative=Button_GetState(GUI_GetCtrl(GUI, CMD_PM_RELATIVE))};
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PM_SPREAD then
		local Info={Spread=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_SPREAD))};
		ParticleSystem_SetInfo(Par, Info);
		Text_SetText(GUI_GetCtrl(GUI, CMD_PM_TSPREAD), string.format("%d", math.floor(Info.Spread*180/M_PI)));
	elseif ID==CMD_PM_STARTSPEEDLOCK then
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDMAX), Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDMIN)));
			local Info={SpeedMax=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDMIN))};
			ParticleSystem_SetInfo(Par, Info);
		end
	elseif ID==CMD_PM_STARTSPEEDMIN then
		local Info={SpeedMin=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDMIN))};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDMAX), Info.SpeedMin);
			Info.SpeedMax=Info.SpeedMin;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PM_STARTSPEEDMAX then
		local Info={SpeedMax=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDMAX))};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDMIN), Info.SpeedMax);
			Info.SpeedMin=Info.SpeedMax;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PM_GRAVITYLOCK then
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PM_GRAVITYLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_GRAVITYMAX), Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_GRAVITYMIN)));
			local Info={GravityMax=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_GRAVITYMIN))};
			ParticleSystem_SetInfo(Par, Info);
		end
	elseif ID==CMD_PM_GRAVITYMIN then
		local Info={GravityMin=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_GRAVITYMIN))};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PM_GRAVITYLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_GRAVITYMAX), Info.GravityMin);
			Info.GravityMax=Info.GravityMin;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PM_GRAVITYMAX then
		local Info={GravityMax=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_GRAVITYMAX))};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PM_GRAVITYLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_GRAVITYMIN), Info.GravityMax);
			Info.GravityMin=Info.GravityMax;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PM_RADIALLOCK then
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PM_RADIALLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_RADIALMAX), Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_RADIALMIN)));
			local Info={GravityMax=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_RADIALMIN))};
			ParticleSystem_SetInfo(Par, Info);
		end
	elseif ID==CMD_PM_RADIALMIN then
		local Info={RadialAccelMin=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_RADIALMIN))};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PM_RADIALLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_RADIALMAX), Info.RadialAccelMin);
			Info.RadialAccelMax=Info.RadialAccelMin;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PM_RADIALMAX then
		local Info={RadialAccelMax=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_RADIALMAX))};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PM_RADIALLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_RADIALMIN), Info.RadialAccelMax);
			Info.RadialAccelMin=Info.RadialAccelMax;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PM_TANGENTIALLOCK then
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALMAX), Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALMIN)));
			local Info={TangentialAccelMax=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALMIN))};
			ParticleSystem_SetInfo(Par, Info);
		end
	elseif ID==CMD_PM_TANGENTIALMIN then
		local Info={TangentialAccelMin=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALMIN))};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALMAX), Info.TangentialAccelMin);
			Info.TangentialAccelMax=Info.TangentialAccelMin;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PM_TANGENTIALMAX then
		local Info={TangentialAccelMax=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALMAX))};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALMIN), Info.TangentialAccelMax);
			Info.TangentialAccelMin=Info.TangentialAccelMax;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_SIZELOCK then
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PA_SIZELOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_SIZEEND), Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_SIZESTART)));
			local Info={SizeEnd=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_SIZESTART))/PARTICLE_SIZE};
			ParticleSystem_SetInfo(Par, Info);
		end
	elseif ID==CMD_PA_SIZESTART then
		local Info={SizeStart=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_SIZESTART))/PARTICLE_SIZE};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PA_SIZELOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_SIZEEND), Info.SizeStart*PARTICLE_SIZE);
			Info.SizeEnd=Info.SizeStart;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_SIZEEND then
		local Info={SizeEnd=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_SIZEEND))/PARTICLE_SIZE};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PA_SIZELOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_SIZESTART), Info.SizeEnd*PARTICLE_SIZE);
			Info.SizeStart=Info.SizeEnd;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_SIZEVAR then
		local Info={SizeVar=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_SIZEVAR))};
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_SPINLOCK then
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PA_SPINLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_SPINEND), Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_SPINSTART)));
			local Info={SpinEnd=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_SPINSTART))};
			ParticleSystem_SetInfo(Par, Info);
		end
	elseif ID==CMD_PA_SPINSTART then
		local Info={SpinStart=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_SPINSTART))};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PA_SPINLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_SPINEND), Info.SpinStart);
			Info.SpinEnd=Info.SpinStart;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_SPINEND then
		local Info={SpinEnd=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_SPINEND))};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PA_SPINLOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_SPINSTART), Info.SpinEnd);
			Info.SpinStart=Info.SpinEnd;
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_SPINVAR then
		local Info={SpinVar=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_SPINVAR))};
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_ALPHALOCK then
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PA_ALPHALOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_ALPHAEND), Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_ALPHASTART)));
			local Info={ColorEnd={a=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_ALPHASTART))}};
			ParticleSystem_SetInfo(Par, Info);
		end
	elseif ID==CMD_PA_ALPHASTART then
		local Info={ColorStart={a=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_ALPHASTART))}};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PA_ALPHALOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_ALPHAEND), Info.ColorStart.a);
			Info.ColorEnd={a=Info.ColorStart.a};
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_ALPHAEND then
		local Info={ColorEnd={a=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_ALPHAEND))}};
		if Button_GetState(GUI_GetCtrl(GUI, CMD_PA_ALPHALOCK)) then
			Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_ALPHASTART), Info.ColorEnd.a);
			Info.ColorStart={a=Info.ColorEnd.a};
		end
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_ALPHAVAR then
		local Info={AlphaVar=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_ALPHAVAR))};
		ParticleSystem_SetInfo(Par, Info);
	elseif CMD_PA_RSTART<=ID and ID<=CMD_PA_BEND then ChangeColor(ID);
	elseif ID==CMD_PA_RGBVAR then
		local Info={ColorVar=Slider_GetValue(GUI_GetCtrl(GUI, CMD_PA_RGBVAR))};
		ParticleSystem_SetInfo(Par, Info);
	end
	return false;
end

function ChangePreset(n)
	ParticleSystem_Stop(Par);
	Button_SetState(GUI_GetCtrl(GUI, CMD_PRESET1-1+Preset), false);
	Button_SetState(GUI_GetCtrl(GUI, CMD_PRESET1-1+n), true);
	SavePreset(Preset);
	LoadPreset(n);
	Preset=n;
end

function SavePreset(n)
	ParticleSystem_SerializeInfo(Par, string.format("Particle%d.psi", n), true, Animation_GetBlendMode(animPar), Animation_GetFrame(animPar));
end

function LoadPreset(n)
	local Hi, Lo=ParticleSystem_SerializeInfo(Par, string.format("Particle%d.psi", n));
	local Info=ParticleSystem_GetInfo(Par);

	Animation_SetFrame(animPar, Lo);
	Animation_SetBlendMode(animPar, Hi);
	Info.Sprite=animPar;
	ParticleSystem_SetInfo(Par, Info);

	local col1=Bit_or(Color_GetColor(Info.ColorStart), 0xFF000000);
	local col2=Bit_or(Color_GetColor(Info.ColorEnd), 0xFF000000);

	Sprite_SetColor(sprColor, col1, 0);
	Sprite_SetColor(sprColor, col1, 1);
	Sprite_SetColor(sprColor, col2, 2);
	Sprite_SetColor(sprColor, col2, 3);

	--System parameters
	if Info.Lifetime==-1 then
		Slider_SetValue(GUI_GetCtrl(GUI, CMD_SYS_LIFETIME), 5);
		Button_SetState(GUI_GetCtrl(GUI, CMD_SYS_LIFECONT), true);
		Text_SetText(GUI_GetCtrl(GUI, CMD_SYS_TLIFETIME), string.format("%.1f", 5));
		ParticleSystem_Fire(Par);
	else
		Slider_SetValue(GUI_GetCtrl(GUI, CMD_SYS_LIFETIME), Info.Lifetime);
		Button_SetState(GUI_GetCtrl(GUI, CMD_SYS_LIFECONT), false);
		Text_SetText(GUI_GetCtrl(GUI, CMD_SYS_TLIFETIME), string.format("%.1f", Info.Lifetime));
	end

	Slider_SetValue(GUI_GetCtrl(GUI, CMD_SYS_EMISSION), Info.Emission);
	Text_SetText(GUI_GetCtrl(GUI, CMD_SYS_TEMISSION), string.format("%d", Info.Emission));

	Slider_SetValue(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMEMIN), Info.ParticleLifeMin);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMEMAX), Info.ParticleLifeMax);
	Button_SetState(GUI_GetCtrl(GUI, CMD_SYS_PARLIFETIMELOCK), false);

	if Bit_and(Animation_GetBlendMode(animPar), BLEND_ALPHABLEND)~=0 then
		Button_SetState(GUI_GetCtrl(GUI, CMD_SYS_BLENDADDITIVE), false);
		Button_SetState(GUI_GetCtrl(GUI, CMD_SYS_BLENDBLEND), true);
	else
		Button_SetState(GUI_GetCtrl(GUI, CMD_SYS_BLENDADDITIVE), true);
		Button_SetState(GUI_GetCtrl(GUI, CMD_SYS_BLENDBLEND), false);
	end

	--Particle movement
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_DIRECTION), Info.Direction);
	Text_SetText(GUI_GetCtrl(GUI, CMD_PM_TDIRECTION), string.format("%d", math.floor(Info.Direction*180/M_PI)));
	Button_SetState(GUI_GetCtrl(GUI, CMD_PM_RELATIVE), Info.Relative);

	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_SPREAD), Info.Spread);
	Text_SetText(GUI_GetCtrl(GUI, CMD_PM_TSPREAD), string.format("%d", math.floor(Info.Spread*180/M_PI)));

	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDMIN), Info.SpeedMin);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDMAX), Info.SpeedMax);
	Button_SetState(GUI_GetCtrl(GUI, CMD_PM_STARTSPEEDLOCK), false);

	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_GRAVITYMIN), Info.GravityMin);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_GRAVITYMAX), Info.GravityMax);
	Button_SetState(GUI_GetCtrl(GUI, CMD_PM_GRAVITYLOCK), false);

	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_RADIALMIN), Info.RadialAccelMin);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_RADIALMAX), Info.RadialAccelMax);
	Button_SetState(GUI_GetCtrl(GUI, CMD_PM_RADIALLOCK), false);

	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALMIN), Info.TangentialAccelMin);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALMAX), Info.TangentialAccelMax);
	Button_SetState(GUI_GetCtrl(GUI, CMD_PM_TANGENTIALLOCK), false);

	--Particle appearance
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_SIZESTART), Info.SizeStart*PARTICLE_SIZE);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_SIZEEND), Info.SizeEnd*PARTICLE_SIZE);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_SIZEVAR), Info.SizeVar);
	Button_SetState(GUI_GetCtrl(GUI, CMD_PA_SIZELOCK), false);

	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_SPINSTART), Info.SpinStart);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_SPINEND), Info.SpinEnd);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_SPINVAR), Info.SpinVar);
	Button_SetState(GUI_GetCtrl(GUI, CMD_PA_SPINLOCK), false);

	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_ALPHASTART), Info.ColorStart.a);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_ALPHAEND), Info.ColorEnd.a);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_ALPHAVAR), Info.AlphaVar);
	Button_SetState(GUI_GetCtrl(GUI, CMD_PA_ALPHALOCK), false);

	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_RSTART), Info.ColorStart.r);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_GSTART), Info.ColorStart.g);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_BSTART), Info.ColorStart.b);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_REND), Info.ColorEnd.r);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_GEND), Info.ColorEnd.g);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_BEND), Info.ColorEnd.b);
	Slider_SetValue(GUI_GetCtrl(GUI, CMD_PA_RGBVAR), Info.ColorVar);
end

function ChangeColor(ID)
	local Val=Slider_GetValue(GUI_GetCtrl(GUI, ID));

	if ID==CMD_PA_RSTART then
		local Info={ColorStart={r=Val}};
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_GSTART then
		local Info={ColorStart={g=Val}};
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_BSTART then
		local Info={ColorStart={b=Val}};
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_REND then
		local Info={ColorEnd={r=Val}};
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_GEND then
		local Info={ColorEnd={g=Val}};
		ParticleSystem_SetInfo(Par, Info);
	elseif ID==CMD_PA_BEND then
		local Info={ColorEnd={b=Val}};
		ParticleSystem_SetInfo(Par, Info);
	end

	local Info=ParticleSystem_GetInfo(Par);
	local col1=Bit_or(Color_GetColor(Info.ColorStart), 0xFF000000);
	local col2=Bit_or(Color_GetColor(Info.ColorEnd), 0xFF000000);

	Sprite_SetColor(sprColor, col1, 0);
	Sprite_SetColor(sprColor, col1, 1);
	Sprite_SetColor(sprColor, col2, 2);
	Sprite_SetColor(sprColor, col2, 3);
end

function InitEngine()  -- RUGE Callback Function
	System_SetState(APP_CAPTION, "RUGE Particle System Editor");
	System_SetState(APP_VSYNC, VSYNC_ONE);
	System_SetState(APP_HIDECURSOR, true);
	System_SetState(APP_MAGFILTER, TEXF_LINEAR);
	System_SetState(APP_MINFILTER, TEXF_LINEAR);
end

function InitResource()  -- RUGE Callback Function
	bHelp=false;
	bBBox=false;
	bIFace=true;
	bVSync=true;
	Preset=1;
	psx=400;
	psy=300;

	Font=Font_Create(16, 0, 0, false, "微软雅黑");
	texGUI=Texture_Load("GUI.png");
	texPar=Texture_Load("Particles.png");

	sprLPane1=Sprite_Create(texGUI, 0, 0, 168, 512);
	sprLPane2=Sprite_Create(texGUI, 336, 0, 168, 88);
	sprRPane1=Sprite_Create(texGUI, 168, 0, 168, 512);
	sprRPane2=Sprite_Create(texGUI, 336, 88, 168, 88);

	sprCursor=Sprite_Create(texGUI, 487, 181, 19, 26);
	sprColor=Sprite_Create(texGUI, 466, 208, 14, 80);
	sprBBox=Sprite_Create(texGUI, 337, 209, 128, 128);

	animPar=Animation_Create(texPar, 16, 1, 0, 0, 32, 32);
	Animation_SetHotSpot(animPar, 16, 16);

	psi={Sprite=animPar};
	Par=ParticleSystem_Create(psi);
	ParticleSystem_TrackBoundingBox(Par, true);
	ParticleSystem_MoveTo(Par, psx, psy);

	GUI=GUI_Create();
	CreateGUI();
	LoadPreset(Preset);

	return true;
end

function ReleaseResource()  -- RUGE Callback Function
	SavePreset(Preset);
	GUI_Free(GUI);
	ParticleSystem_Free(Par);
	Animation_Free(animPar);
	Sprite_Free(sprBBox);
	Sprite_Free(sprColor);
	Sprite_Free(sprCursor);
	Sprite_Free(sprRPane2);
	Sprite_Free(sprRPane1);
	Sprite_Free(sprLPane2);
	Sprite_Free(sprLPane1);
	Texture_Free(texPar);
	Texture_Free(texGUI);
	Font_Free(Font);
end

function Frame(Delta)  -- RUGE Callback Function
	local x, y=Input_GetMousePos();
	if Input_KeyPressed(VK_MENU) and Input_KeyDown(string.byte('V')) then
		bVSync=not bVSync;
		if bVSync then System_SetState(APP_VSYNC, VSYNC_ONE);
		else System_SetState(APP_VSYNC, VSYNC_IMMEDIATE); end
	end
	if Input_KeyPressed(VK_RBUTTON) then
		GUI_SetCursor(GUI, NULL);
		psx=x;
		psy=y;
		if bIFace then
			if psx<168 then psx=168; end
			if psx>631 then psx=631; end
		end
		if psx<0 then psx=0; end
		if psx>800 then psx=800; end
		if psy<0 then psy=0; end
		if psy>600 then psy=600; end
	else
		GUI_SetCursor(GUI, sprCursor);
		psx=400;
		psy=300;
	end

	if HandleKey(Input_GetKey()) then return true; end

	local tx, ty=ParticleSystem_GetPosition(Par);
	ParticleSystem_MoveTo(Par, tx+(psx-tx)*10*Delta, ty+(psy-ty)*10*Delta);
	ParticleSystem_Update(Par, Delta);

	if bIFace then
		if HandleCommand(GUI_Update(GUI, Delta)) then return true; end
		Text_SetText(GUI_GetCtrl(GUI, CMD_NPARTICLES), string.format("%d", ParticleSystem_GetParticlesAlive(Par)));
		Text_SetText(GUI_GetCtrl(GUI, CMD_FPS), string.format("%d", Timer_GetFPS()));
	end

	return false;
end

function Render()  -- RUGE Callback Function
	Gfx_Clear();
	ParticleSystem_Render(Par);
	if bBBox then
		local Rect=ParticleSystem_GetBoundingBox(Par);
		Sprite_RenderStretch(sprBBox, Rect.Left, Rect.Top, Rect.Right, Rect.Bottom);
	end
	if bIFace then
		Sprite_Render(sprLPane1, 0, 0);
		Sprite_Render(sprLPane2, 0, 512);
		Sprite_Render(sprRPane1, 632, 0);
		Sprite_Render(sprRPane2, 632, 512);
		local Info=ParticleSystem_GetInfo(Par);
		Animation_SetColor(animPar, Bit_or(Color_GetColor(Info.ColorStart), 0xFF000000));
		Animation_Render(animPar, 26, 189);
		Sprite_Render(sprColor, 642, 221);
		GUI_Render(GUI);
	end
	if bHelp then
		local Str="鼠标左键 - 打开粒子系统\n鼠标右键 - 使粒子系统跟随鼠标移动\n\n\
					数字键 1 到 9 - 选择Preset\nPreset将会自动读取和存储\n\nTAB - 隐藏编辑器界面\n\
					Alt+Enter - 全屏\\窗口模式切换\n\
					Alt+V - 关闭\\开启垂直同步\n\
					Esc - 退出";
		local n=0;
		local Rect=
		{
			Left=189,
			Top=18,
			Right=0,
			Bottom=0
		};

		n, Rect=Font_DrawText(Font, Str, Rect, 0, DT_CALCRECT);
		Font_DrawText(Font, Str, Rect);
	end
end
