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