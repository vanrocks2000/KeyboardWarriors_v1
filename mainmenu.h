//---------------------------------------------------------
// file:	mainmenu.h
// author:	Vanessa Luo
// email:	vanessa.l@digipen.edu
//
// brief:	done by Vanessa Luo
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once

struct Button
{
	const char* text;
	float x;
	float y;
	float width;
	float height;
	CP_Color colourfont;
	CP_Color colourDefault;
	CP_Color colourHover;
};

void mainmenu_init(void);
void mainmenu_update(void);
void mainmenu_exit(void);