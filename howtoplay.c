#include "cprocessing.h"
#include <stdio.h>
#include "mainmenu.h"

#define FONT_SIZE 35
#define FONT_SIZE2 50
#define FONT_SIZE1 33
#define FONT_SIZE3 25

int displayWidth = 1280;
int displayHeight = 720;
int abc;

void howtoplay_init(void)
{


	CP_System_SetWindowSize(displayWidth, displayHeight);
	abc = 0;

}

void howtoplay_update(void)
{
	CP_Font font1 = CP_Font_Load("./Assets/retro_computer.ttf");
	CP_Font_Set(font1);
	CP_Image bg = CP_Image_Load("./Assets/bg.png");
	CP_Image_Draw(bg, (float)displayWidth / 2, (float)displayHeight / 2, (float)displayWidth, (float)displayHeight, 125);

	CP_Settings_TextSize(FONT_SIZE);
	CP_Color back = CP_Color_Create(255, 255, 255, 255);
	CP_Settings_Fill(back);
	/*CP_Graphics_DrawRect(10, 10, 1200, 550);
	CP_Graphics_DrawRect(400, 600, 475, 55);
	char *text = "HOW TO PLAY\n\
	------------\n\
	There will be 3 rows of enemies approaching you. \n\
	Move your player up and down using the upand down arrow keys to target the enemy you wish to attack\n\
	Type out the word given at the top of the enemy on the row you are standing\n\
	Press the enter key in order to attack the typed out word\n\
	Kill a certain amount of enemies to move on to the next level\n\
	If you make 3 consecutive typing errors, the enemy will speed up.\n\
	To go back to the original speed, you will need to type 2 consecutive correct answers";
	CP_Color front = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_Fill(front);
	CP_Font_DrawTextBox(text, 15, 50, 1200);*/

	CP_Font_DrawText("Press SPACE to go back", 410, 645);
	if (abc == 0)
	{
		CP_Graphics_DrawRect(70, 50, 1140, 600);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(FONT_SIZE2);
		CP_Font_DrawText("Controls", 120, 100);
		CP_Image arrowkeys = CP_Image_Load("./Assets/arrowkeys.png");
		CP_Image backspace = CP_Image_Load("./Assets/backspace.png");
		CP_Image enter = CP_Image_Load("./Assets/enter.png");
		CP_Image keyboard = CP_Image_Load("./Assets/keyboard.png");
		CP_Image_Draw(arrowkeys, 150, 250, 200, 180, 255);
		CP_Image_Draw(backspace, 230, 450, 300, 230, 255);
		CP_Image_Draw(enter, 770, 220, 300, 230, 255);
		CP_Image_Draw(keyboard, 780, 480 , 300, 230, 255);
		CP_Settings_TextSize(FONT_SIZE1);
		CP_Font_DrawTextBox("Use UP and DOWN arrow keys to move player", 220, 220, 250);
		CP_Font_DrawTextBox("Press ENTER to submit the word that was typed", 950, 200, 250);
		CP_Font_DrawTextBox("Use BACKSPACE to delete characters typed wrongly", 380, 400, 250);
		CP_Font_DrawTextBox("Type out the words given on your keyboard", 950, 450, 250);
		CP_Settings_TextSize(FONT_SIZE3);
		CP_Font_DrawTextBox("Press ESC anytime to return", 100, 620, 600);
		CP_Font_DrawTextBox("Right arrow key >>>", 900, 620, 600);
	}
	if (abc == 1)
	{
		CP_Graphics_DrawRect(70, 50, 1140, 600);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(FONT_SIZE2);
		CP_Font_DrawText("Enemies", 120, 100);
		CP_Image enemy1 = CP_Image_Load("./Assets/Enemy1.png");
		CP_Image enemy2 = CP_Image_Load("./Assets/Enemy2.png");
		CP_Image enemy3 = CP_Image_Load("./Assets/Enemy3.png");
		CP_Image enemy4 = CP_Image_Load("./Assets/Boss.png");
		CP_Image_Draw(enemy1, 250, 250, 200, 180, 255);
		CP_Image_Draw(enemy2, 500, 250, 200, 180, 255);
		CP_Image_Draw(enemy3, 750, 250, 200, 180, 255);
		CP_Image_Draw(enemy4, 1000, 250, 200, 180, 255);
		CP_Settings_TextSize(FONT_SIZE1);
		CP_Font_DrawTextBox("Basic enemy in level 1, regular words", 170, 400, 200);
		CP_Font_DrawTextBox("Fast moving enemy in level 2, one character", 420, 400, 210);
		CP_Font_DrawTextBox("Enemy in level 3, words with special characters", 670, 400, 225);
		CP_Font_DrawTextBox("Boss in level 4, full length sentences", 920, 400, 200);
		CP_Settings_TextSize(FONT_SIZE3);
		CP_Font_DrawTextBox("<<< Left arrow key to go back", 100, 620, 600);
		CP_Font_DrawTextBox("Next >>>", 1050, 620, 600);

		
	}
	if (abc == 2)
	{
		CP_Graphics_DrawRect(70, 50, 1140, 600);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(FONT_SIZE2);
		CP_Font_DrawText("Level 1", 120, 100);
		CP_Settings_TextSize(FONT_SIZE1);
		CP_Font_DrawTextBox("Number of enemies: 15", 170, 150, 1000);
		CP_Font_DrawTextBox("Level description: Speed of enemy increases if player enters word wrongly/enemy reaches player 2 times in a row, enter 2 words correctly in a row to reset speed", 170, 200, 1000);

		CP_Settings_TextSize(FONT_SIZE2);
		CP_Font_DrawText("Level 2", 120, 400);
		CP_Settings_TextSize(FONT_SIZE1);
		CP_Font_DrawTextBox("Number of enemies: 25", 170, 450, 1000);
		CP_Font_DrawTextBox("Level description: Faster enemies, no increase in speed if mistakes are made", 170, 500, 1000);
		CP_Settings_TextSize(FONT_SIZE3);
		CP_Font_DrawTextBox("<<< Back", 100, 620, 600);
		CP_Font_DrawTextBox("Next >>>", 1050, 620, 600);
	}
	if (abc == 3)
	{
		CP_Graphics_DrawRect(70, 50, 1140, 600);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(FONT_SIZE2);
		CP_Font_DrawText("Level 3", 120, 140);
		CP_Settings_TextSize(FONT_SIZE1);
		CP_Font_DrawTextBox("Number of enemies: 25", 170, 190, 1000);
		CP_Font_DrawTextBox("Level description: Special characters enemy, no increase in speed if mistakes are made", 170, 240, 1000);

		CP_Settings_TextSize(FONT_SIZE2);
		CP_Font_DrawText("Level 4", 120, 400);
		CP_Settings_TextSize(FONT_SIZE1);
		CP_Font_DrawTextBox("Number of enemies: 1", 170, 450, 1000);
		CP_Font_DrawTextBox("Level description: Boss, increase in speed if sentences entered are incorrect, enter a sentence correctly to reset speed", 170, 500, 1000);
		CP_Settings_TextSize(FONT_SIZE3);
		CP_Font_DrawTextBox("<<< Back", 100, 620, 600);
		CP_Font_DrawTextBox("Next >>>", 1050, 620, 600);
	}
	if (abc == 4)
	{
		CP_Graphics_DrawRect(70, 50, 1140, 600);
		CP_Image gameplay = CP_Image_Load("./Assets/gameplay.png");
		CP_Image_Draw(gameplay, 450, 400, 700, 700, 255);
	}

	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
	}
	if (CP_Input_KeyTriggered(KEY_RIGHT))
	{
		if (abc < 4)
		{
			abc++;
		}
	}
	if (CP_Input_KeyTriggered(KEY_LEFT))
	{
		if (abc > 0)
		{
			abc--;
		}
	}
}

void howtoplay_exit(void)
{

}