require "Common Const";

function InitEngine()  -- RUGE Callback Function
	System_SetState(APP_CAPTION, "Crazy Stars");
	System_SetState(APP_VSYNC, VSYNC_ONE);
	System_SetState(APP_HIDECURSOR, true);
end

function InitResource()  -- RUGE Callback Function
	Font=Font_Create(20, 0, 0, false, "Fixedsys");
	Tex=Texture_Load("bg2.png");

	Spr=Sprite_Create(Tex, 0, 0, 800, 600);

	Manager=SceneManager_Create();
	SceneManager_AddScene(Manager, Scene_Create(SCENE_MENU, "Menu Scene.lua"));
	SceneManager_AddScene(Manager, Scene_Create(SCENE_STARS, "Stars Scene.lua"));
	SceneManager_Switch(Manager, SCENE_MENU);

	return true;
end

function ReleaseResource()  -- RUGE Callback Function
	SceneManager_Free(Manager);
	Sprite_Free(Spr);
	Texture_Free(Tex);
	Font_Free(Font);
end

function Frame(Delta)  -- RUGE Callback Function
	Sprite_SetTextureRect(Spr, 50*math.sin(Timer_GetTime()), 50*math.cos(Timer_GetTime()), 800, 600);
	return SceneManager_Update(Manager, Delta);
end

function Render()  -- RUGE Callback Function
	Gfx_Clear();
	Sprite_Render(Spr, 0, 0);
	SceneManager_Render(Manager);

	local n=0;
	local Rect=
	{
		Left=0,
		Top=0,
		Right=0,
		Bottom=0
	};
	local Str=string.format("FPS: %d", Timer_GetFPS());

	n, Rect=Font_DrawText(Font, Str, Rect, 0, DT_CALCRECT);
	Font_DrawText(Font, Str, Rect);
end
