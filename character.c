#include "cprocessing.h"
#include <stdio.h>
#include "character.h"

void Drawenemy(char* ptr,float eposx, float eposy, float width, float height)
{

	CP_Font_DrawText(ptr, (eposx - 1) * width, (eposy - 1) * height);
	CP_Image enemy = CP_Image_Load("./Assets/Enemy1.png");
	CP_Image_Draw(enemy, eposx * width, eposy * height, 2 * width, 2 * height, 255);
	//CP_Graphics_DrawRect(posx * gridwidth, posy * gridheight, gridwidth, gridheight);
}

void Drawplayer(float pposx, float pposy, float width, float height)
{

	CP_Image player = CP_Image_Load("./Assets/Player.png");
	CP_Image_Draw(player, pposx * width, pposy * height, 2 * width, 2 * height, 255);
	//CP_Graphics_DrawRect(posx * gridwidth, posy * gridheight, gridwidth, gridheight);
}