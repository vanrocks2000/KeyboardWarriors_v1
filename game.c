#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include <stdlib.h>
#include <string.h>
#define FONT_SIZE 30.0f 
#define NUMBER_STRINGS 5
#define STRING_MAX_SIZE 10

#define MAXC 20
#define MAXW 10


int displaywidth, displayheight;
float time;
float interval = 2.0f;

CP_Color fontColour;
char wordbuf[MAXC];
int y, i, j;

char userinput[MAXC];
char* ui = userinput;
int n;

int nextchar = 0;
int numofcorrect = 0;
int x;
char* wordchosen;


float wordx, wordy;
float gridwidth, gridheight;
float velx;

char string[MAXC];

char* pstr;
int numofchar;
int intvalue[MAXC];
int k;

struct WORDS
{
	char* buffer;
	int numc;


} p[MAXW], word[MAXW];


void game_init(void)
{
	displaywidth = 1280;
	displayheight = 720;
	CP_System_SetWindowSize(displaywidth, displayheight);
	CP_Settings_TextSize(FONT_SIZE);
	fontColour = CP_Color_Create(13, 50, 213, 255);
	CP_Settings_Fill(fontColour);
	RandomWord();
	gridwidth = 40;
	gridheight = 40;
	//there are 30 units x 18units
	wordx = 28;
	wordy = 10;

	velx = -0.05f;
	k = 2;

}
// initialize variables and CProcessing settings for this gamestate

void game_update(void)
{

	time += CP_System_GetDt();


	CP_Settings_Background(CP_Color_Create(135, 245, 157, 255));

	wordchosen = wordlist(x);
	n = numofcharacters(x);

	for (int test = 0; test < n; test++)
	{
		string[test] = *(wordchosen + test);
	}

	pstr = string;

	Drawenemy(wordx, wordy);
	wordx += velx;
	ConvertWordToInt();

	Keyinput();
	CP_Font_DrawText(ui, 500, 100);


	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		//check if they are the same
		int lenofinput = numofcharactersinput();
		for (int check = 0; check < lenofinput; check++)
		{
			if (intvalue[check] == (int)userinput[check])
			{
				numofcorrect++;
			}

		}
		if (numofcorrect == lenofinput)
		{
			numofcorrect = 0;
			memset(userinput, 0, MAXC * sizeof(char));
			memset(string, 0, 20 * sizeof(char));
			nextchar = 0;
			wordx = 28;
			wordy = 10;
			RandomWord();


		}

		else
		{
			numofcorrect = 0;
			memset(userinput, 0, MAXC * sizeof(char));
			nextchar = 0;
		}

	}








}

void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

void RandomWord(void)
{
	x = CP_Random_RangeInt(0, 9);
}
/*void RandomWord2(void)
{
	x2 = CP_Random_RangeInt(0, 9);
}*/
char* wordlist(int choice)
{
	p[0].buffer = "TYPEFASTFAST";
	p[1].buffer = "HELLO";
	p[2].buffer = "CATS";
	p[3].buffer = "HEY";
	p[4].buffer = "MORNING";
	p[5].buffer = "AFTERNOON";
	p[6].buffer = "GREAT";
	p[7].buffer = "BOY";
	p[8].buffer = "ADVENTURE";
	p[9].buffer = "RACE";


	char* wordpicked = p[choice].buffer;

	return wordpicked;
}


int numofcharacters(int l)
{
	p[l].numc = (int)strlen(p[l].buffer);
	int nc = p[l].numc;
	return nc;


}
int numofcharactersinput(void)
{
	int lengthofinput = (int)strlen(userinput);

	return lengthofinput;


}

void ConvertWordToInt(void)
{
	for (i = 0; i < n; i++)
	{

		intvalue[i] = (int)*(pstr + i);

	}


}

void Keyinput(void)
{
	//whatever that is typed first is stored in 0 position in array, subsequent char is stored in nth position +1
	if (CP_Input_KeyTriggered(KEY_A))
	{
		*(ui + nextchar) = 'A';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_B))
	{
		*(ui + nextchar) = 'B';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_C))
	{
		*(ui + nextchar) = 'C';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_D))
	{
		*(ui + nextchar) = 'D';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_E))
	{
		*(ui + nextchar) = 'E';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_F))
	{
		*(ui + nextchar) = 'F';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_G))
	{
		*(ui + nextchar) = 'G';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_H))
	{
		*(ui + nextchar) = 'H';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_I))
	{
		*(ui + nextchar) = 'I';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_J))
	{
		*(ui + nextchar) = 'J';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_K))
	{
		*(ui + nextchar) = 'K';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_L))
	{
		*(ui + nextchar) = 'L';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_M))
	{
		*(ui + nextchar) = 'M';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_N))
	{
		*(ui + nextchar) = 'N';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_O))
	{
		*(ui + nextchar) = 'O';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_P))
	{
		*(ui + nextchar) = 'P';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		*(ui + nextchar) = 'Q';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_R))
	{
		*(ui + nextchar) = 'R';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_S))
	{
		*(ui + nextchar) = 'S';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_T))
	{
		*(ui + nextchar) = 'T';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_U))
	{
		*(ui + nextchar) = 'U';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_V))
	{
		*(ui + nextchar) = 'V';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_W))
	{
		*(ui + nextchar) = 'W';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_X))
	{
		*(ui + nextchar) = 'X';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_Y))
	{
		*(ui + nextchar) = 'Y';
		nextchar++;
	}
	if (CP_Input_KeyTriggered(KEY_Z))
	{
		*(ui + nextchar) = 'Z';
		nextchar++;
	}
}
void Drawenemy(float posx, float posy)
{

	CP_Font_DrawText(pstr, (posx-1) * gridwidth, (posy- 1) * gridheight);
	CP_Image enemy = CP_Image_Load("./Assets/Enemy1.png");
	CP_Image_Draw(enemy, posx * gridwidth, posy * gridheight, 2*gridwidth, 2*gridheight, 255);
	//CP_Graphics_DrawRect(posx * gridwidth, posy * gridheight, gridwidth, gridheight);
}




// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
//float characX = 100;
//float characY = 100;

/*void game_init(void)
{


	CP_Settings_Background(CP_Color_Create(135, 245, 157, 255));
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)
{
	// char colour[6] = {'H', 'E', 'L', 'L', 'O' };



	CP_Settings_TextSize(FONT_SIZE);
	//for (int i = 0; i < 5; i++)
	//{
	//	if (CP_Input_KeyTriggered(KEY_H) == colour[i] )
	//	{
	//		//CP_Font_DrawText(colour[i], characX, characY);
	//		CP_Font_DrawText("Correct", characX, characY);
	//	}
	//	else
	//	{
	//		CP_Font_DrawText("Wrong", characX, characY);
	//	}

	//
	//}

	//if (CP_Input_KeyTriggered() == 72 )
	//{
	//	//CP_Font_DrawText(colour[i], characX, characY);
	//	CP_Font_DrawText("Correct", characX, characY);
	//}
	//else
	//{
	//	CP_Font_DrawText("Wrong", characX, characY);
	//}



	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}

}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{

}

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation*/