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

void Drawenemy1(char* ptr, float eposx, float eposy, float width, float height)
{
	CP_Font_DrawText(ptr, (eposx - 1) * width, (eposy - 1) * height);
	CP_Image enemy1 = CP_Image_Load("./Assets/Enemy1frame1.png");
	CP_Image_Draw(enemy1, eposx * width, eposy * height, 2 * width, 2 * height, 255);
	//CP_Graphics_DrawRect(posx * gridwidth, posy * gridheight, gridwidth, gridheight);
}

void Drawenemy2(char* ptr, float eposx, float eposy, float width, float height)
{
	CP_Font_DrawText(ptr, (eposx - 1) * width, (eposy - 1) * height);
	CP_Image enemy2 = CP_Image_Load("./Assets/Enemy1frame2.png");
	CP_Image_Draw(enemy2, eposx * width, eposy * height, 2 * width, 2 * height, 255);
	//CP_Graphics_DrawRect(posx * gridwidth, posy * gridheight, gridwidth, gridheight);
}

void Drawenemy3(char* ptr, float eposx, float eposy, float width, float height)
{
	CP_Font_DrawText(ptr, (eposx - 1) * width, (eposy - 1) * height);
	CP_Image enemy3 = CP_Image_Load("./Assets/Enemy1frame3.png");
	CP_Image_Draw(enemy3, eposx * width, eposy * height, 2 * width, 2 * height, 255);
	//CP_Graphics_DrawRect(posx * gridwidth, posy * gridheight, gridwidth, gridheight);
}

void Drawenemy4(char* ptr, float eposx, float eposy, float width, float height)
{
	CP_Font_DrawText(ptr, (eposx - 1) * width, (eposy - 1) * height);
	CP_Image enemy4 = CP_Image_Load("./Assets/Enemy1frame4.png");
	CP_Image_Draw(enemy4, eposx * width, eposy * height, 2 * width, 2 * height, 255);
	//CP_Graphics_DrawRect(posx * gridwidth, posy * gridheight, gridwidth, gridheight);
}

void Drawenemy5(char* ptr, float eposx, float eposy, float width, float height)
{
	CP_Font_DrawText(ptr, (eposx - 1) * width, (eposy - 1) * height);
	CP_Image enemy5 = CP_Image_Load("./Assets/Enemy1frame5.png");
	CP_Image_Draw(enemy5, eposx * width, eposy * height, 2 * width, 2 * height, 255);
	//CP_Graphics_DrawRect(posx * gridwidth, posy * gridheight, gridwidth, gridheight);
}

void Drawenemy6(char* ptr, float eposx, float eposy, float width, float height)
{
	CP_Font_DrawText(ptr, (eposx - 1) * width, (eposy - 1) * height);
	CP_Image enemy6 = CP_Image_Load("./Assets/Enemy1frame6.png");
	CP_Image_Draw(enemy6, eposx * width, eposy * height, 2 * width, 2 * height, 255);
	//CP_Graphics_DrawRect(posx * gridwidth, posy * gridheight, gridwidth, gridheight);
}

void Drawenemy7(char* ptr, float eposx, float eposy, float width, float height)
{
	CP_Font_DrawText(ptr, (eposx - 1) * width, (eposy - 1) * height);
	CP_Image enemy7 = CP_Image_Load("./Assets/Enemy1frame7.png");
	CP_Image_Draw(enemy7, eposx * width, eposy * height, 2 * width, 2 * height, 255);
	//CP_Graphics_DrawRect(posx * gridwidth, posy * gridheight, gridwidth, gridheight);
}

void Drawplayer(float pposx, float pposy, float width, float height)
{

	CP_Image player = CP_Image_Load("./Assets/Player.png");
	CP_Image_Draw(player, pposx * width, pposy * height, 2 * width, 2 * height, 255);
	//CP_Graphics_DrawRect(posx * gridwidth, posy * gridheight, gridwidth, gridheight);
}