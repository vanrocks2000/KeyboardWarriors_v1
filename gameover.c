#include "cprocessing.h"
#include "MainMenu.h"
#include "game.h"
#include "gameover.h"
#include <stdio.h>
#include <stdlib.h>
#define FONT_SIZE 50 
#define TIME 10
#define SCORE 10
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
void gameover_init(void)
{

	b1.width = 400;
	b1.height = 150;
	b1.x = 420;
	b1.y = 55;

	b2.width = 400;
	b2.height = 150;
	b2.x = 420;
	b2.y = 250;

	b3.width = 400;
	b3.height = 150;
	b3.x = 420;
	b3.y = 450;

	CP_Settings_Background(CP_Color_Create(135, 245, 157, 255));;

	CP_Color rectColour = CP_Color_Create(215, 196, 130, 255);
	CP_Settings_Fill(rectColour);
	CP_Graphics_DrawRect(b1.x, b1.y, b1.width, b1.height);
	CP_Graphics_DrawRect(b2.x, b2.y, b2.width, b2.height);
	CP_Graphics_DrawRect(b3.x, b3.y, b3.width, b3.height);


	CP_Color fontColour = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_Fill(fontColour);

	CP_Settings_TextSize(FONT_SIZE);
	CP_Font_DrawText("Main Menu", 540, 125);
	CP_Font_DrawText("Replay", 540, 325);
	CP_Font_DrawText("Exit Game", 540, 525);

	totaltimesurvived = GetFinalTime();
	_itoa_s((int)totaltimesurvived, finaltimebuffer, TIME, 10);
	CP_Font_DrawText(finaltimebuffer, 130, 350);
	CP_Font_DrawText("Seconds Survived:", 50, 300);

	totalscore = GetFinalScore();
	_itoa_s((int)totalscore, finalscorebuffer, SCORE, 10);
	CP_Font_DrawText(finalscorebuffer, 960, 350);
	CP_Font_DrawText("Final Score:", 900, 300);


}


void gameover_update(void)
{
	

	float mouseX = CP_Input_GetMouseX(), mouseY = CP_Input_GetMouseY();

	

	gameover_init();
	if (mouseX > b1.x && mouseX < (b1.x + b1.width))
	{
		if (mouseY > b1.y && mouseY < (b1.y + b1.height))
		{

			CP_Color rectColour = CP_Color_Create(124, 126, 40, 255);
			CP_Settings_Fill(rectColour);
			CP_Graphics_DrawRect(b1.x, b1.y, b1.width, b1.height);
			CP_Color fontColour = CP_Color_Create(0, 0, 0, 255);
			CP_Settings_Fill(fontColour);

			CP_Settings_TextSize(FONT_SIZE);
			CP_Font_DrawText("Main Menu", 540, 125);
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

			CP_Color rectColour = CP_Color_Create(124, 126, 40, 255);
			CP_Settings_Fill(rectColour);
			CP_Graphics_DrawRect(b2.x, b2.y, b2.width, b2.height);
			CP_Color fontColour = CP_Color_Create(0, 0, 0, 255);
			CP_Settings_Fill(fontColour);

			CP_Settings_TextSize(FONT_SIZE);
			CP_Font_DrawText("Replay", 540, 325);

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

			CP_Color rectColour = CP_Color_Create(124, 126, 40, 255);
			CP_Settings_Fill(rectColour);
			CP_Graphics_DrawRect(b3.x, b3.y, b3.width, b3.height);
			CP_Color fontColour = CP_Color_Create(0, 0, 0, 255);
			CP_Settings_Fill(fontColour);

			CP_Settings_TextSize(FONT_SIZE);
			CP_Font_DrawText("Exit Game", 540, 525);
			if (CP_Input_MouseClicked())
			{
				CP_Engine_Terminate();
			}

		}
	}

}

void gameover_exit(void)
{

}