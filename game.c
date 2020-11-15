#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "gameover.h"
#include "gamelvl2.h"
#define FONT_SIZE 30.0f 
#define NUMBER_STRINGS 5
#define STRING_MAX_SIZE 10
#define TIME 10
#define SCORE 10
#define LIVES 10
#define KILLS 10
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
int numkilled;
char killedbuffer[KILLS];


CP_Color fontColour;

int y, i;

char userinput[MAXC];
char* ui = userinput;
int n1, n2, n3;

int nextchar = 0;
int numofcorrect = 0;
int x, x1, x2, x3;
char* wordchosen;
char* wordchosen2;
char* wordchosen3;


float enemyx1, enemyy1, enemyx2, enemyy2, enemyx3, enemyy3;
float gridwidth, gridheight;
float velx;

char string1[MAXC], string2[MAXC], string3[MAXC];

char* pstr1;
char* pstr2;
char* pstr3;
int numofchar;
int intvalue1[MAXC], intvalue2[MAXC], intvalue3[MAXC];
float playerx, playery;

struct WORDS
{
	char* buffer;
	int numc;


} p[MAXW];


void game_init(void)
{
	// set game window size
	displaywidth = 1280;
	displayheight = 720;
	CP_System_SetWindowSize(displaywidth, displayheight);
	//it is 30 units x 18units
	gridwidth = 40;
	gridheight = 40;

	//settings for font, colour
	CP_Settings_TextSize(FONT_SIZE);
	fontColour = CP_Color_Create(13, 50, 213, 255);
	CP_Settings_Fill(fontColour);
	
	//set random word
	x1 = RandomWord();
	x2 = RandomWord();
	x3 = RandomWord();
	
	//set coordinates of enemy/player
	enemyx1 = 28;
	enemyy1 = 5;
	enemyx2 = 28;
	enemyy2 = 10;
	enemyx3 = 28;
	enemyy3 = 15;
	playerx = 2;
	playery = 10;
	velx = -0.05f;
	lives =5;
	numkilled = 10;
	memset(userinput, 0, MAXC * sizeof(char));
	nextchar = 0;

	

}
// initialize variables and CProcessing settings for this gamestate

void game_update(void)
{
	
	//set time
	time += CP_System_GetDt();
	finaltime = time;
	finalscore = score;


	//set background
	CP_Image levelbg = CP_Image_Load("./Assets/levelbg.png");
	CP_Image_Draw(levelbg, (float)displaywidth / 2, (float)displayheight / 2, (float)CP_Image_GetWidth(levelbg), (float)CP_Image_GetHeight(levelbg) , 255);

	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));

	
	DisplayTime(time, gridwidth, gridheight);
	DisplayScore(score, gridwidth, gridheight);
	DisplayLives(lives, gridwidth, gridheight);
	DisplayNumberOfEnemiesKilled(numkilled, gridwidth, gridheight);
	
	Drawplayer(playerx, playery, gridwidth, gridheight);
	
	//use randomized value to obtain a word from the wordlist and store it in strings
	wordchosen = wordlist(x1);
	wordchosen2 = wordlist(x2);
	wordchosen3 = wordlist(x3);
	
	n1 = numofcharacters(x1);
	n2 = numofcharacters(x2);
	n3 = numofcharacters(x3);

	for (int test = 0; test < n1; test++)
	{
		string1[test] = *(wordchosen + test);
	}
	for (int test = 0; test < n2; test++)
	{
		string2[test] = *(wordchosen2 + test);
	}
	for (int test = 0; test < n3; test++)
	{
		string3[test] = *(wordchosen3 + test);
	}

	pstr1 = string1;
	pstr2 = string2;
	pstr3 = string3;

	Drawenemy(pstr1, enemyx1, enemyy1, gridwidth, gridheight);
	Drawenemy(pstr2, enemyx2, enemyy2, gridwidth, gridheight);
	Drawenemy(pstr3, enemyx3, enemyy3, gridwidth, gridheight);
	enemyx1 += velx;
	enemyx2 += velx;
	enemyx3 += velx;
	
	ConvertWordToInt();
	
	Keyinput();
	//displays words typed on screen
	CP_Font_DrawText(ui, 500, 100);

	PlayerMovement();
	
	if (numkilled == 0)
	{
		memset(string1, 0, 20 * sizeof(char));
		memset(string2, 0, 20 * sizeof(char));
		memset(string3, 0, 20 * sizeof(char));
		CP_Engine_SetNextGameState(game2_init, game2_update, game2_exit);
	}

	//minus life if enemy reaches playerline
	if ((int)enemyx1 == (int)playerx)
	{
		lives--;
		if (lives == 0)
		{
			CP_Engine_SetNextGameState(gameover_init, gameover_update, gameover_exit);
			time = 0;
			score = 0;
			numkilled = 0;
			memset(userinput, 0, MAXC * sizeof(char));
			memset(string1, 0, 20 * sizeof(char));
			memset(string2, 0, 20 * sizeof(char));
			memset(string3, 0, 20 * sizeof(char));
		}
		else
		{
			numofcorrect = 0;
			memset(string1, 0, 20 * sizeof(char));
			enemyx1 = 28;
			enemyy1 = 5;
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
			numkilled = 0;
			memset(userinput, 0, MAXC * sizeof(char));
			memset(string1, 0, 20 * sizeof(char));
			memset(string2, 0, 20 * sizeof(char));
			memset(string3, 0, 20 * sizeof(char));
		}
		else
		{
			numofcorrect = 0;
			memset(string2, 0, 20 * sizeof(char));
			enemyx2 = 28;
			enemyy2 = 10;
			x2 = RandomWord();
			

		}
	}
	if ((int)enemyx3 == (int)playerx)
	{
		lives -= 1;
		if (lives == 0)
		{
			CP_Engine_SetNextGameState(gameover_init, gameover_update, gameover_exit);
			time = 0;
			score = 0;
			numkilled = 0;
			memset(userinput, 0, MAXC * sizeof(char));
			memset(string1, 0, 20 * sizeof(char));
			memset(string2, 0, 20 * sizeof(char));
			memset(string3, 0, 20 * sizeof(char));
		}
		else
		{
			numofcorrect = 0;
			memset(string3, 0, 20 * sizeof(char));
			enemyx3 = 28;
			enemyy3 = 15;
			x3 = RandomWord();

		}
	}

	//enter to check word typed = random word
	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		//check if they are the same
		int lenofinput = numofcharactersinput();
		
		if (playery == 5)
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
					numkilled--;
					memset(userinput, 0, MAXC * sizeof(char));
					memset(string1, 0, MAXC * sizeof(char));
					nextchar = 0;
					enemyx1 = 28;
					enemyy1 = 5;
					x1 = RandomWord();
				}
				if (numofcorrect != n1)
				{
					numofcorrect = 0;
					memset(userinput, 0, MAXC * sizeof(char));
					nextchar = 0;
				}
			}

			else
			{
				numofcorrect = 0;
				memset(userinput, 0, MAXC * sizeof(char));
				nextchar = 0;
			}
		}
		
		if (playery == 10)
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
					numkilled--;
					memset(userinput, 0, MAXC * sizeof(char));
					memset(string2, 0, MAXC * sizeof(char));
					nextchar = 0;
					enemyx2 = 28;
					enemyy2 = 10;
					x2 = RandomWord();
				}
				if (numofcorrect != n2)
				{
					numofcorrect = 0;
					memset(userinput, 0, MAXC * sizeof(char));
					nextchar = 0;
				}
			}

			else
			{
				numofcorrect = 0;
				memset(userinput, 0, MAXC * sizeof(char));
				nextchar = 0;
			}
		}

		if (playery == 15)
		{

			for (int check = 0; check < lenofinput; check++)
			{
				if (intvalue3[check] == (int)userinput[check])
				{
					numofcorrect++;
				}

			}
			if (n3 == lenofinput)
			{
				if (numofcorrect == n3)
				{
					numofcorrect = 0;
					score++;
					numkilled--;
					memset(userinput, 0, MAXC * sizeof(char));
					memset(string3, 0, MAXC * sizeof(char));
					nextchar = 0;
					enemyx3 = 28;
					enemyy3 = 15;
					x3 = RandomWord();
				}
				if (numofcorrect != n3)
				{
					numofcorrect = 0;
					memset(userinput, 0, MAXC * sizeof(char));
					nextchar = 0;
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
	for (i = 0; i < n3; i++)
	{

		intvalue3[i] = (int)*(pstr3 + i);

	}


}

void PlayerMovement(void)
{
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
	
	
	
}

void DisplayTime(float timeelapsed, float width, float height)
{
	_itoa_s((int)timeelapsed, timebuffer, TIME, 10);
	CP_Font_DrawText(timebuffer, (float)5 * width, (float)1 * height);
	CP_Font_DrawText("Time:", (float)2 * width, (float)1 * height);

}

float GetFinalTime(void)
{
	return finaltime;
}

void DisplayLives(int livesleft, float width, float height)
{
	_itoa_s(lives, lifebuffer, LIVES, 10);
	CP_Font_DrawText(lifebuffer, (float)12 * width, (float)1 * height);
	CP_Font_DrawText("Lives Left:", (float)8 * width, (float)1 * height);

}

void DisplayScore(int currentscore, float width, float height)
{
	_itoa_s(score, scorebuffer, SCORE, 10);
	CP_Font_DrawText(scorebuffer, (float)18 * width, (float)1 * height);
	CP_Font_DrawText("Score:", (float)15 * width, (float)1 * height);

}

int GetFinalScore(void)
{
	return finalscore;
}

void DisplayNumberOfEnemiesKilled(int numberkilled, float width, float height)
{
	_itoa_s(numkilled, killedbuffer, KILLS, 10);
	CP_Font_DrawText(killedbuffer, (float)26 * width, (float)1 * height);
	CP_Font_DrawText("Enemies Killed:", (float)21 * width, (float)1 * height);

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