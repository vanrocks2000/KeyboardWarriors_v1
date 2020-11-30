#include "cprocessing.h"
#include "MainMenu.h"
#include "game.h"
#include "gameover.h"
#include <stdio.h>
#include <stdlib.h>
#include "bosslvl.h"
#define FONT_SIZE 45 
#define FONT_SIZE2 100
#define TIME 100
#define SCORE 100
float totaltimesurvived;
char finaltimebuffer[TIME];
int totalscore;
char finalscorebuffer[SCORE];

struct Buttons
{
	float width;
	float height;
	float x;
	float y;
} b1, b2, b3;

void youwin_init(void)
{

	b1.width = 400;
	b1.height = 150;
	b1.x = 800;
	b1.y = 55;

	b2.width = 400;
	b2.height = 150;
	b2.x = 800;
	b2.y = 250;

	b3.width = 400;
	b3.height = 150;
	b3.x = 800;
	b3.y = 450;

	//set background
	CP_Image levelbg = CP_Image_Load("./Assets/Bg2.png");
	CP_Image_Draw(levelbg, 1280 / 2, 720 / 2, (float)CP_Image_GetWidth(levelbg), (float)CP_Image_GetHeight(levelbg), 255);

	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));

	CP_Color rectColour = CP_Color_Create(215, 196, 130, 255);
	CP_Settings_Fill(rectColour);
	CP_Graphics_DrawRect(b1.x, b1.y, b1.width, b1.height);
	CP_Graphics_DrawRect(b2.x, b2.y, b2.width, b2.height);
	CP_Graphics_DrawRect(b3.x, b3.y, b3.width, b3.height);

	CP_Image mainmenu = CP_Image_Load("./Assets/MainMenu.png");
	CP_Image_Draw(mainmenu, b1.x + 200, b1.y + 70, b1.width, b1.height, 255);

	CP_Image replay = CP_Image_Load("./Assets/Replay.png");
	CP_Image_Draw(replay, b1.x + 200, b1.y + 270, b1.width, b1.height, 255);

	CP_Image exit = CP_Image_Load("./Assets/Exit.png");
	CP_Image_Draw(exit, b1.x + 200, b1.y + 470, b1.width, b1.height, 255);



	CP_Color fontColour = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_Fill(fontColour);
	CP_Settings_TextSize(FONT_SIZE2);
	CP_Font_DrawText("YOU WIN!!!!", 50, 100);

	CP_Settings_TextSize(FONT_SIZE);
	//CP_Font_DrawText("Main Menu", 540, 125);
	//CP_Font_DrawText("Replay", 540, 325);
	//CP_Font_DrawText("Exit Game", 540, 525);



	totaltimesurvived = GetFinalTime();
	//_itoa_s((int)totaltimesurvived, finaltimebuffer, TIME, 10);
	//CP_Font_DrawText(finaltimebuffer, 650, 300);
	//CP_Font_DrawText("Seconds Survived:", 50, 300);
	snprintf(finaltimebuffer, TIME, "Time Survived : %d seconds", (int)totaltimesurvived);
	CP_Font_DrawText(finaltimebuffer, 50, 300);

	totalscore = GetFinalScore();
	//_itoa_s((int)totalscore, finalscorebuffer, SCORE, 10);
	//CP_Font_DrawText(finalscorebuffer, 650, 500);
	//CP_Font_DrawText("Final Score:", 50, 500);
	snprintf(finalscorebuffer, SCORE, "Final Score : %d", totalscore);
	CP_Font_DrawText(finalscorebuffer, 50, 500);


}


void youwin_update(void)
{


	float mouseX = CP_Input_GetMouseX(), mouseY = CP_Input_GetMouseY();



	gameover_init();
	if (mouseX > b1.x && mouseX < (b1.x + b1.width))
	{
		if (mouseY > b1.y && mouseY < (b1.y + b1.height))
		{
			CP_Image mainmenu2 = CP_Image_Load("./Assets/MainMenu2.png");
			CP_Image_Draw(mainmenu2, b1.x + 200, b1.y + 70, b1.width, b1.height, 255);

			/*
			CP_Color rectColour = CP_Color_Create(124, 126, 40, 255);
			CP_Settings_Fill(rectColour);
			CP_Graphics_DrawRect(b1.x, b1.y, b1.width, b1.height);
			CP_Color fontColour = CP_Color_Create(0, 0, 0, 255);
			CP_Settings_Fill(fontColour);

			CP_Settings_TextSize(FONT_SIZE);
			CP_Font_DrawText("Main Menu", 540, 125);
			*/

			if (CP_Input_MouseClicked())
			{
				CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
			}

		}
	}
	if (mouseX > b2.x && mouseX < (b2.x + b2.width))
	{
		if (mouseY > b2.y && mouseY < (b2.y + b2.height))
		{
			CP_Image replay2 = CP_Image_Load("./Assets/Replay2.png");
			CP_Image_Draw(replay2, b1.x + 200, b1.y + 270, b1.width, b1.height, 255);

			/*
			CP_Color rectColour = CP_Color_Create(124, 126, 40, 255);
			CP_Settings_Fill(rectColour);
			CP_Graphics_DrawRect(b2.x, b2.y, b2.width, b2.height);
			CP_Color fontColour = CP_Color_Create(0, 0, 0, 255);
			CP_Settings_Fill(fontColour);

			CP_Settings_TextSize(FONT_SIZE);
			CP_Font_DrawText("Replay", 540, 325);
			*/

			if (CP_Input_MouseClicked())
			{
				CP_Engine_SetNextGameState(game_init, game_update, game_exit);
			}

		}
	}
	if (mouseX > b3.x && mouseX < (b3.x + b3.width))
	{
		if (mouseY > b3.y && mouseY < (b3.y + b3.height))
		{
			CP_Image exit2 = CP_Image_Load("./Assets/Exit2.png");
			CP_Image_Draw(exit2, b1.x + 200, b1.y + 470, b1.width, b1.height, 255);

			/*
			CP_Color rectColour = CP_Color_Create(124, 126, 40, 255);
			CP_Settings_Fill(rectColour);
			CP_Graphics_DrawRect(b3.x, b3.y, b3.width, b3.height);
			CP_Color fontColour = CP_Color_Create(0, 0, 0, 255);
			CP_Settings_Fill(fontColour);

			CP_Settings_TextSize(FONT_SIZE);
			CP_Font_DrawText("Exit Game", 540, 525);
			*/

			if (CP_Input_MouseClicked())
			{
				CP_Engine_Terminate();
			}

		}
	}

}

void youwin_exit(void)
{

}