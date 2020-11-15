#include "cprocessing.h"
#include <stdio.h>
#include "mainmenu.h"

#define FONT_SIZE 45

int displayWidth = 1280;
int displayHeight = 720;

void howtoplay_init(void)
{


	CP_System_SetWindowSize(displayWidth, displayHeight);


}

void howtoplay_update(void)
{

	CP_Image bg = CP_Image_Load("./Assets/bg.png");
	CP_Image_Draw(bg, (float)displayWidth / 2, (float)displayHeight / 2, (float)displayWidth, (float)displayHeight, 125);

	CP_Settings_TextSize(FONT_SIZE);
	CP_Color back = CP_Color_Create(255, 255, 255, 255);
	CP_Settings_Fill(back);
	CP_Graphics_DrawRect(10, 10, 1200, 550);
	CP_Graphics_DrawRect(425, 600, 450, 55);
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
	CP_Font_DrawTextBox(text, 15, 50, 1200);

	CP_Font_DrawText("Press SPACE to go back", 450, 645);

	if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
	}
}

void howtoplay_exit(void)
{

}