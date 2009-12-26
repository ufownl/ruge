require "Common Const";

function Construct(this)
	LastID=0;
	Tex=NULL;
	Sound=NULL;
	Font=NULL;
	GUI=NULL;
	Spr=NULL;
end

function Deconstruct(this)
end

function Enter(this, Param)
	Tex=Texture_Load("cursor.png");
	Sound=Effect_Load("menu.wav");
	Font=Font_Create(40, 0, 0, false, "Î¢ÈíÑÅºÚ");

	Spr=Sprite_Create(Tex, 0, 0, 32, 32);

	GUI=GUI_Create();
	GUI_AddCtrl(GUI, Control_Create(1, "Menu Item.lua", {Font=Font, Sound=Sound, x=400, y=225, Delay=0.1, Title="Start"}));
	GUI_AddCtrl(GUI, Control_Create(2, "Menu Item.lua", {Font=Font, Sound=Sound, x=400, y=275, Delay=0.2, Title="Resume"}));
	GUI_AddCtrl(GUI, Control_Create(3, "Menu Item.lua", {Font=Font, Sound=Sound, x=400, y=325, Delay=0.3, Title="Exit"}));
	GUI_SetNavMode(GUI, Bit_or(NAV_UPDOWN, NAV_CYCLED));
	GUI_SetCursor(GUI, Spr);
	GUI_SetFocus(GUI, 1);
	GUI_Enter(GUI);

	LastID=0;

	return true;
end

function Exit(this)
	GUI_Free(GUI);
	Sprite_Free(Spr);
	Font_Free(Font);
	Audio_Free(Sound);
	Texture_Free(Tex);
end

function Update(this, Delta)
	if Input_GetKey()==VK_ESCAPE then
		LastID=3;
		GUI_Exit(GUI);
	end

	local ID=GUI_Update(GUI, Delta);

	if ID==-1 then
		if LastID==1 then
			SceneManager_Switch(Scene_GetManager(this), SCENE_STARS, {Mode=ENTER_START});
			return false;
		elseif LastID==2 then
			SceneManager_Switch(Scene_GetManager(this), SCENE_STARS, {Mode=ENTER_RESUME});
			return false;
		elseif LastID==3 then return true; end
	elseif ID>0 then
		LastID=ID;
		GUI_Exit(GUI);
	end

	return false;
end

function Render(this)
	GUI_Render(GUI);
end
