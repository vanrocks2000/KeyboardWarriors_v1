#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "gameover.h"
#define FONT_SIZE 30.0f 
#define NUMBER_STRINGS 5
#define STRING_MAX_SIZE 10
#define TIME 10
#define SCORE 10
#define LIVES 10
#define word 100

#define MAXC 20
#define MAXW 20


int displaywidth, displayheight;
float time;
float finaltime;
char timebuffer[TIME];
int score;
int finalscore;
char scorebuffer[SCORE];
int lives;
char lifebuffer[LIVES];
char wordbuf[word];


CP_Color fontColour;

int y, i;

char userinput[MAXC];
char* ui = userinput;
int n1, n2;

int nextchar = 0;
int numofcorrect = 0;
int x, x1, x2, x3;
char* wordchosen;
char* wordchosen2;


float enemyx1, enemyy1, enemyx2, enemyy2;
float gridwidth, gridheight;
float velx;

char string1[MAXC], string2[MAXC];

char* pstr1;
char* pstr2;
int numofchar;
int intvalue1[MAXC], intvalue2[MAXC];
float playerx, playery;

struct WORDS
{
	char* buffer;
	int numc;


} p[MAXW];


void game_init(void)
{

	displaywidth = 1280;
	displayheight = 720;
	CP_System_SetWindowSize(displaywidth, displayheight);



	CP_Settings_TextSize(FONT_SIZE);
	fontColour = CP_Color_Create(13, 50, 213, 255);
	CP_Settings_Fill(fontColour);
	x1 = RandomWord();
	x2 = RandomWord();
	gridwidth = 40;
	gridheight = 40;
	//there are 30 units x 18units
	enemyx1 = 28;
	enemyy1 = 10;
	enemyx2 = 28;
	enemyy2 = 5;
	playerx = 2;
	playery = 10;
	velx = -0.05f;
	lives = 5;

	

}
// initialize variables and CProcessing settings for this gamestate

void game_update(void)
{
	displaywidth = 1280;
	displayheight = 720;

	time += CP_System_GetDt();
	finaltime = time;
	finalscore = score;



	CP_Image levelbg = CP_Image_Load("./Assets/levelbg.png");
	CP_Image_Draw(levelbg, (float)displaywidth / 2, (float)displayheight / 2, (float)CP_Image_GetWidth(levelbg), (float)CP_Image_GetHeight(levelbg) , 255);

	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));

	DisplayTime(time, gridwidth, gridheight);
	DisplayScore(score, gridwidth, gridheight);
	DisplayLives(lives, gridwidth, gridheight);
	
	Drawplayer(playerx, playery, gridwidth, gridheight);
	
	wordchosen = wordlist(x1);
	wordchosen2 = wordlist(x2);
	
	n1 = numofcharacters(x1);
	n2 = numofcharacters(x2);

	for (int test = 0; test < n1; test++)
	{
		string1[test] = *(wordchosen + test);
	}
	for (int test = 0; test < n2; test++)
	{
		string2[test] = *(wordchosen2 + test);
	}

	pstr1 = string1;
	pstr2 = string2;

	Drawenemy(pstr1, enemyx1, enemyy1, gridwidth, gridheight);
	Drawenemy(pstr2, enemyx2, enemyy2, gridwidth, gridheight);
	enemyx1 += velx;
	enemyx2 += velx;
	
	ConvertWordToInt();
	
	Keyinput();
	
	CP_Font_DrawText(ui, 600, 200);
	
	if ((int)enemyx1 == (int)playerx)
	{
		lives -= 1;
		if (lives == 0)
		{
			CP_Engine_SetNextGameState(gameover_init, gameover_update, gameover_exit);
			time = 0;
			score = 0;
			memset(userinput, 0, MAXC * sizeof(char));
			memset(string1, 0, 20 * sizeof(char));
		}
		else
		{
			numofcorrect = 0;
			memset(userinput, 0, MAXC * sizeof(char));
			memset(string1, 0, 20 * sizeof(char));
			nextchar = 0;
			enemyx1 = 28;
			enemyy1 = 10;
			x1 = RandomWord();

		}
	}

	if ((int)enemyx2 == (int)playerx)
	{
		lives -= 1;
		if (lives == 0)
		{
			CP_Engine_SetNextGameState(gameover_init, gameover_update, gameover_exit);
			time = 0;
			score = 0;
			memset(userinput, 0, MAXC * sizeof(char));
			memset(string2, 0, 20 * sizeof(char));
		}
		else
		{
			numofcorrect = 0;
			memset(userinput, 0, MAXC * sizeof(char));
			memset(string2, 0, 20 * sizeof(char));
			nextchar = 0;
			enemyx2 = 28;
			enemyy2 = 5;
			x2 = RandomWord();
			

		}
	}

	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		//check if they are the same
		int lenofinput = numofcharactersinput();
		if (playery == 10)
		{

			for (int check = 0; check < lenofinput; check++)
			{
				if (intvalue1[check] == (int)userinput[check])
				{
					numofcorrect++;
				}

			}
			if (n1 == lenofinput)
			{
				if (numofcorrect == n1)
				{
					numofcorrect = 0;
					score++;
					memset(userinput, 0, MAXC * sizeof(char));
					memset(string1, 0, MAXC * sizeof(char));
					nextchar = 0;
					enemyx1 = 28;
					enemyy1 = 10;
					x1 = RandomWord();
					

				}
			}

			else
			{
				numofcorrect = 0;
				memset(userinput, 0, MAXC * sizeof(char));
				nextchar = 0;
			}
		}

		if (playery == 5)
		{
			for (int check = 0; check < lenofinput; check++)
			{
				if (intvalue2[check] == (int)userinput[check])
				{
					numofcorrect++;
				}

			}
			if (n2 == lenofinput)
			{
				if (numofcorrect == n2)
				{
					numofcorrect = 0;
					score++;
					memset(userinput, 0, MAXC * sizeof(char));
					memset(string2, 0, MAXC * sizeof(char));
					nextchar = 0;
					enemyx2 = 28;
					enemyy2 = 5;
					x2 = RandomWord();


				}
			}

			else
			{
				numofcorrect = 0;
				memset(userinput, 0, MAXC * sizeof(char));
				nextchar = 0;
			}
		}

		}
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}
	}


	







void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

int RandomWord(void)
{
	x = CP_Random_RangeInt(0, 15);
	return x;
}
/*void RandomWord2(void)
{
	x2 = CP_Random_RangeInt(0, 9);
}*/
char* wordlist(int choice)
{
	p[0].buffer = "TECHNOLOGY";
	p[1].buffer = "CYBERBULLY";
	p[2].buffer = "PRIVACY";
	p[3].buffer = "SECURITY";
	p[4].buffer = "INTERNET";
	p[5].buffer = "ONLINE";
	p[6].buffer = "CHAT";
	p[7].buffer = "SOCIAL MEDIA";
	p[8].buffer = "WEBSITE";
	p[9].buffer = "SPAM";
	p[10].buffer = "DATA";
	p[11].buffer = "USER";
	p[12].buffer = "ADVERTISEMENT";
	p[13].buffer = "MEDIA";
	p[14].buffer = "FAKE NEWS";
	p[15].buffer = "TROLLING";


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
	for (i = 0; i < n1; i++)
	{

		intvalue1[i] = (int)*(pstr1 + i);

	}

	for (i = 0; i < n2; i++)
	{

		intvalue2[i] = (int)*(pstr2 + i);

	}


}

void Keyinput(void)
{
	//whatever that is typed first is stored in 0 position in array, subsequent char is stored in nth position +1
	if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		*(ui + nextchar) = ' ';
		nextchar++;
	}

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
	
	if (playery >= 10 && playery <= 15)
	{
		if (CP_Input_KeyTriggered(KEY_UP))
		{
				playery -= 5;
		}
	}
	if (playery >= 5 && playery <= 10)
	{
		if (CP_Input_KeyTriggered(KEY_DOWN))
		{
			playery += 5;
		}
	}
	
}

void DisplayTime(float timeelapsed, float width, float height)
{
	_itoa_s((int)timeelapsed, timebuffer, TIME, 10);
	CP_Font_DrawText(timebuffer, (float)8 * width, (float)1 * height);
	CP_Font_DrawText("Time:", (float)5 * width, (float)1 * height);

}

float GetFinalTime(void)
{
	return finaltime;
}

void DisplayScore(int currentscore, float width, float height)
{
	_itoa_s(score, scorebuffer, SCORE, 10);
	CP_Font_DrawText(scorebuffer, (float)26 * width, (float)1 * height);
	CP_Font_DrawText("Score:", (float)23 * width, (float)1 * height);

}

int GetFinalScore(void)
{
	return finalscore;
}

void DisplayLives(int livesleft, float width, float height)
{
	_itoa_s(lives, lifebuffer, LIVES, 10);
	CP_Font_DrawText(lifebuffer, (float)17 * width, (float)1 * height);
	CP_Font_DrawText("Lives Left:", (float)13 * width, (float)1 * height);

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