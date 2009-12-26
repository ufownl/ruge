function Construct(this)
	OffsetSrc=0;
	OffsetDelta=0;
	Offset=0;
	Time=-1;
	Time2=-1;

	colColor=Color_SetColor(0xFFFFE060);
	colShadow=Color_SetColor(0x30000000);

	Control_SetStatic(this, false);
	Control_SetVisible(this, true);
	Control_SetEnabled(this, true);

	local n=0;
	local Rect=
	{
		Left=0,
		Top=0,
		Right=0,
		Bottom=0
	};

	n, Rect=Font_DrawText(Attribute.Font, Attribute.Title, Rect, 0, DT_CALCRECT);
	Rect.Left=Attribute.x-Rect.Right/2;
	Rect.Top=Attribute.y;
	Rect.Right=Attribute.x+Rect.Right/2;
	Rect.Bottom=Attribute.y+Rect.Bottom;
	Control_SetRect(this, Rect);
end

function Deconstruct(this)
end

function SetColor(this, Color)
end

function Render(this)
	local n=0;
	local mRect=Control_GetRect(this);
	local Rect=
	{
		Left=math.floor(mRect.Left+Offset+3),
		Top=math.floor(mRect.Top+3),
		Right=0,
		Bottom=0
	};

	n, Rect=Font_DrawText(Attribute.Font, Attribute.Title, Rect, 0, DT_CALCRECT);
	Font_DrawText(Attribute.Font, Attribute.Title, Rect, 0, Bit_or(DT_TOP, DT_LEFT), Color_GetColor(colShadow));
	Rect.Left=math.floor(mRect.Left-Offset);
	Rect.Top=math.floor(mRect.Top-Offset);
	n, Rect=Font_DrawText(Attribute.Font, Attribute.Title, Rect, 0, DT_CALCRECT);
	Font_DrawText(Attribute.Font, Attribute.Title, Rect, 0, Bit_or(DT_TOP, DT_LEFT), Color_GetColor(colColor));
end

function Update(this, Delta)
	if Time2~=-1 then
		Time2=Time2+Delta;
		if Time2>=Attribute.Delay+0.1 then
			colColor=Color_Add(colSrc2, colDelta2);
			colShadow=Color_Add(colShadowSrc, colShadowDelta);
			Offset=0;
			Time2=-1;
		else
			if Time2<Attribute.Delay then
				colColor=
				{
					a=colSrc2.a,
					r=colSrc2.r,
					g=colSrc2.g,
					b=colSrc2.b
				};
				colShadow=
				{
					a=colShadowSrc.a,
					r=colShadowSrc.r,
					g=colShadowSrc.g,
					b=colShadowSrc.b
				};
			else
				colColor=Color_Add(colSrc2, Color_Mul(colDelta2, (Time2-Attribute.Delay)*10));
				colShadow=Color_Add(colShadowSrc, Color_Mul(colShadowDelta, (Time2-Attribute.Delay)*10));
			end
		end
	elseif Time~=-1 then
		Time=Time+Delta;
		if Time>0.2 then
			colColor=Color_Add(colSrc, colDelta);
			Offset=OffsetSrc+OffsetDelta;
			Time=-1;
		else
			colColor=Color_Add(colSrc, Color_Mul(colDelta, Time*5));
			Offset=OffsetSrc+OffsetDelta*Time*5;
		end
	end
end

function Enter(this)
	colSrc2=Color_SetColor(0x00FFE060);
	local col=Color_SetColor(0xFFFFE060);
	colDelta2=Color_Sub(col, colSrc2);
	colShadowSrc=Color_SetColor(0);
	col=Color_SetColor(0x30000000);
	colShadowDelta=Color_Sub(col, colShadowSrc);
	Time2=0;
end

function Exit(this)
	colSrc2=Color_SetColor(0xFFFFE060);
	local col=Color_SetColor(0x00FFE060);
	colDelta2=Color_Sub(col, colSrc2);
	colShadowSrc=Color_SetColor(0x30000000);
	col=Color_SetColor(0);
	colShadowDelta=Color_Sub(col, colShadowSrc);
	Time2=0;
end

function Reset(this)
end

function IsDone(this)
	if Time2==-1 then return true;
	else return false; end
end

function Focus(this, bFocused)
	local col;

	if bFocused then
		Effect_Play(Attribute.Sound);
		colSrc=Color_SetColor(0xFFFFE060)
		col=Color_SetColor(0xFFFFFFFF);
		OffsetSrc=0;
		OffsetDelta=4;
	else
		colSrc=Color_SetColor(0xFFFFFFFF)
		col=Color_SetColor(0xFFFFE060);
		OffsetSrc=4;
		OffsetDelta=-4;
	end
	colDelta=Color_Sub(col, colSrc);
	Time=0;
end

function MouseOver(this, bOver)
	if bOver then GUI_SetFocus(Control_GetGUI(this), Control_GetID(this)); end
end

function MouseMove(this, x, y)
	return false;
end

function MouseLBtn(this, bDown, x, y)
	if bDown then
		Effect_Play(Attribute.Sound);
		Offset=0;
		return false;
	else
		Offset=4;
		return true;
	end
end

function MouseRBtn(this, bDown, x, y)
	return false;
end

function MouseWheel(this, Wheel)
	return false;
end

function KeyClick(this, VKey, Char)
	if VKey==VK_RETURN then
		MouseLBtn(this, true, 0, 0)
		return MouseLBtn(this, false, 0, 0);
	end
	return false;
end
