#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include "mainmenu.h"

#define FONT_SIZE 100

void mainmenu_init(void)
{
	int displayHeight = CP_System_GetDisplayHeight();
	int displayWidth = CP_System_GetDisplayWidth();

	CP_System_SetWindowSize(displayWidth, displayHeight);

	//Loads digipen logo
	CP_Image DPlogo = CP_Image_Load("./Assets/DigiPen_BLACK.png");
	CP_Image GameLogo = CP_Image_Load("./Assets/KWlogo.png");
	CP_Image bg = CP_Image_Load("./Assets/bg.png");

	float time = CP_System_GetSeconds();

	if (time < 3)
	{
		CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));
		CP_Image_Draw(DPlogo, (float)displayWidth / 2, (float)displayHeight / 4, (float)CP_Image_GetWidth(DPlogo) * 2, (float)CP_Image_GetHeight(DPlogo) * 2, 255);
	}
	else
	{
		struct Button a1 , a2;

		CP_Image_Draw(bg, (float)displayWidth / 2, (float)displayHeight / 4, (float)displayWidth, (float)displayHeight/ 1.75f, 125);

		CP_Image_Draw(GameLogo, (float)displayWidth / 2.1f, (float)displayHeight / 6.5f, (float)CP_Image_GetWidth(GameLogo) * 2.5f, (float)CP_Image_GetHeight(GameLogo) * 2.5f, 255);

		//setting size and position of buttons
		a1.width = 550;
		a1.height = 250;
		a1.x = (float)displayWidth / 2.5f;
		a1.y = (float)displayHeight / 4;

		a2.width = 550;
		a2.height = 250;
		a2.x = (float)displayWidth / 2.5f;
		a2.y = (float)displayHeight / 2.5f;

		//draw the logo, play & exit buttons on the screen

		//CP_Image logo = CP_Image_Load("./Assets/Logo.png");
		//CP_Image_Draw(logo, a1.x, a1.y, a3.width, a3.height, 255);

		CP_Image play = CP_Image_Load("./Assets/Play.png");
		CP_Image_Draw(play, a1.x + 280, a1.y + 125, a1.width, a1.height, 255);

		CP_Image exit = CP_Image_Load("./Assets/Exit.png");
		CP_Image_Draw(exit, a2.x + 280, a2.y + 125, a1.width, a1.height, 255);

		/*
		CP_Color rectColour = CP_Color_Create(215, 196, 130, 255);
		CP_Settings_Fill(rectColour);
		CP_Graphics_DrawRect(a1.x, a1.y, a1.width, a1.height);
		CP_Graphics_DrawRect(a2.x, a2.y, a2.width, a2.height);

		CP_Settings_TextSize(FONT_SIZE);
		CP_Color fontColour = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(fontColour);
		CP_Font_DrawText("Play", (float)displayWidth / 2.2f, (float)displayHeight / 3.5f);
		CP_Font_DrawText("Exit", (float)displayWidth / 2.2f, (float)displayHeight / 2.2f);
		*/

		float mouseX = CP_Input_GetMouseX(), mouseY = CP_Input_GetMouseY();
		//if mouse hover over buttons, change color of buttons
		if (mouseX > a1.x && mouseX < (a1.x + a1.width))
		{
			if (mouseY > a1.y && mouseY < (a1.y + a1.height))
			{
				CP_Image play2 = CP_Image_Load("./Assets/Play2.png");
				CP_Image_Draw(play2, a1.x + 280, a1.y + 125, a1.width, a1.height, 255);

				/*
				CP_Color rectColour2 = CP_Color_Create(124, 126, 40, 255);
				CP_Settings_Fill(rectColour2);
				CP_Graphics_DrawRect(a1.x, a1.y, a1.width, a1.height);
				CP_Color fontColour2 = CP_Color_Create(255, 255, 255, 255);
				CP_Settings_Fill(fontColour2);

				CP_Settings_TextSize(FONT_SIZE);
				CP_Font_DrawText("Play", (float)displayWidth / 2.2f, (float)displayHeight / 3.5f);
				*/

				//if mouseclicked on first button, start the game
				if (CP_Input_MouseClicked())
				{
					CP_Engine_SetNextGameState(game_init, game_update, game_exit);
				}

			}
		}
		if (mouseX > a2.x && mouseX < (a2.x + a2.width))
		{
			if (mouseY > a2.y && mouseY < (a2.y + a2.height))
			{
				CP_Image exit2 = CP_Image_Load("./Assets/Exit2.png");
				CP_Image_Draw(exit2, a2.x + 280, a2.y + 125, a1.width, a1.height, 255);

				/*
				CP_Color rectColour2 = CP_Color_Create(124, 126, 40, 255);
				CP_Settings_Fill(rectColour2);
				CP_Graphics_DrawRect(a2.x, a2.y, a2.width, a2.height);
				CP_Color fontColour2 = CP_Color_Create(255, 255, 255, 255);
				CP_Settings_Fill(fontColour2);

				CP_Settings_TextSize(FONT_SIZE);
				CP_Font_DrawText("Exit", (float)displayWidth / 2.2f, (float)displayHeight / 2.2f);
				*/

				//if mouseclicked on the seocnd button, terminates game
				if (CP_Input_MouseClicked())
				{
					CP_Engine_Terminate();
				}
			}
		}
	}
}

void mainmenu_update(void)
{
	mainmenu_init();
}

void mainmenu_exit(void)
{

}