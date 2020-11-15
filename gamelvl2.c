#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include "gamelvl2.h"
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

char userinput2[MAXC];
char* ui2 = userinput2;
int n1, n2, n3;

int nextchar2 = 0;
int numofcorrect2 = 0;
int x, y1, y2, y3;
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


void game2_init(void)
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
	y1 = RandomWord2();
	y2 = RandomWord2();
	y3 = RandomWord2();

	//set coordinates of enemy/player
	enemyx1 = 28;
	enemyy1 = 5;
	enemyx2 = 28;
	enemyy2 = 10;
	enemyx3 = 28;
	enemyy3 = 15;
	playerx = 2;
	playery = 10;
	velx = -0.15f;
	numkilled = 20;
	memset(userinput2, 0, MAXC * sizeof(char));
	nextchar2 = 0;



}
// initialize variables and CProcessing settings for this gamestate

void game2_update(void)
{

	//set time
	time += CP_System_GetDt();
	finaltime = time;
	finalscore = score;


	//set background
	CP_Image levelbg = CP_Image_Load("./Assets/levelbg.png");
	CP_Image_Draw(levelbg, (float)displaywidth / 2, (float)displayheight / 2, (float)CP_Image_GetWidth(levelbg), (float)CP_Image_GetHeight(levelbg), 255);

	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));


	DisplayTime(time, gridwidth, gridheight);
	DisplayScore(score, gridwidth, gridheight);
	DisplayLives(lives, gridwidth, gridheight);
	DisplayNumberOfEnemiesKilled(numkilled, gridwidth, gridheight);

	Drawplayer(playerx, playery, gridwidth, gridheight);

	//use randomized value to obtain a word from the wordlist and store it in strings
	wordchosen = wordlist2(y1);
	wordchosen2 = wordlist2(y2);
	wordchosen3 = wordlist2(y3);

	n1 = numofcharacters2(y1);
	n2 = numofcharacters2(y2);
	n3 = numofcharacters2(y3);

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

	ConvertWordToInt2();

	Keyinput2();
	//displays words typed on screen
	CP_Font_DrawText(ui2, 500, 100);

	PlayerMovement();

	if (numkilled == 0)
	{
		CP_Engine_SetNextGameState(gameover_init, gameover_update, gameover_exit);
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
			memset(userinput2, 0, MAXC * sizeof(char));
			memset(string1, 0, 20 * sizeof(char));
			memset(string2, 0, 20 * sizeof(char));
			memset(string3, 0, 20 * sizeof(char));
		}
		else
		{
			numofcorrect2 = 0;
			memset(string1, 0, 20 * sizeof(char));
			enemyx1 = 28;
			enemyy1 = 5;
			y1 = RandomWord2();

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
			memset(userinput2, 0, MAXC * sizeof(char));
			memset(string1, 0, 20 * sizeof(char));
			memset(string2, 0, 20 * sizeof(char));
			memset(string3, 0, 20 * sizeof(char));
		}
		else
		{
			numofcorrect2 = 0;
			memset(string2, 0, 20 * sizeof(char));
			enemyx2 = 28;
			enemyy2 = 10;
			y2 = RandomWord2();


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
			memset(userinput2, 0, MAXC * sizeof(char));
			memset(string1, 0, 20 * sizeof(char));
			memset(string2, 0, 20 * sizeof(char));
			memset(string3, 0, 20 * sizeof(char));
		}
		else
		{
			numofcorrect2 = 0;
			memset(string3, 0, 20 * sizeof(char));
			enemyx3 = 28;
			enemyy3 = 15;
			y3 = RandomWord2();

		}
	}

	//enter to check word typed = random word
	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		//check if they are the same
		int lenofinput = numofcharactersinput2();

		if (playery == 5)
		{
			for (int check = 0; check < lenofinput; check++)
			{
				if (intvalue1[check] == (int)userinput2[check])
				{
					numofcorrect2++;
				}

			}
			if (n1 == lenofinput)
			{
				if (numofcorrect2 == n1)
				{
					numofcorrect2 = 0;
					score++;
					numkilled--;
					memset(userinput2, 0, MAXC * sizeof(char));
					memset(string1, 0, MAXC * sizeof(char));
					nextchar2 = 0;
					enemyx1 = 28;
					enemyy1 = 5;
					y1 = RandomWord2();
				}
				if (numofcorrect2 != n1)
				{
					numofcorrect2 = 0;
					memset(userinput2, 0, MAXC * sizeof(char));
					nextchar2 = 0;
				}
			}

			else
			{
				numofcorrect2 = 0;
				memset(userinput2, 0, MAXC * sizeof(char));
				nextchar2 = 0;
			}
		}

		if (playery == 10)
		{

			for (int check = 0; check < lenofinput; check++)
			{
				if (intvalue2[check] == (int)userinput2[check])
				{
					numofcorrect2++;
				}

			}
			if (n2 == lenofinput)
			{
				if (numofcorrect2 == n2)
				{
					numofcorrect2 = 0;
					score++;
					numkilled--;
					memset(userinput2, 0, MAXC * sizeof(char));
					memset(string2, 0, MAXC * sizeof(char));
					nextchar2 = 0;
					enemyx2 = 28;
					enemyy2 = 10;
					y2 = RandomWord2();
				}
				if (numofcorrect2 != n2)
				{
					numofcorrect2 = 0;
					memset(userinput2, 0, MAXC * sizeof(char));
					nextchar2 = 0;
				}
			}

			else
			{
				numofcorrect2 = 0;
				memset(userinput2, 0, MAXC * sizeof(char));
				nextchar2 = 0;
			}
		}

		if (playery == 15)
		{

			for (int check = 0; check < lenofinput; check++)
			{
				if (intvalue3[check] == (int)userinput2[check])
				{
					numofcorrect2++;
				}

			}
			if (n3 == lenofinput)
			{
				if (numofcorrect2 == n3)
				{
					numofcorrect2 = 0;
					score++;
					numkilled--;
					memset(userinput2, 0, MAXC * sizeof(char));
					memset(string3, 0, MAXC * sizeof(char));
					nextchar2 = 0;
					enemyx3 = 28;
					enemyy3 = 15;
					y3 = RandomWord2();
				}
				if (numofcorrect2 != n3)
				{
					numofcorrect2 = 0;
					memset(userinput2, 0, MAXC * sizeof(char));
					nextchar2 = 0;
				}
			}

			else
			{
				numofcorrect2 = 0;
				memset(userinput2, 0, MAXC * sizeof(char));
				nextchar2 = 0;
			}
		}
	}
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}

}


void game2_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

int RandomWord2(void)
{
	x = CP_Random_RangeInt(0, 15);
	return x;
}

char* wordlist2(int choice)
{
	p[0].buffer = "A";
	p[1].buffer = "B";
	p[2].buffer = "C";
	p[3].buffer = "D";
	p[4].buffer = "E";
	p[5].buffer = "F";
	p[6].buffer = "G";
	p[7].buffer = "H";
	p[8].buffer = "I";
	p[9].buffer = "J";
	p[10].buffer = "K";
	p[11].buffer = "L";
	p[12].buffer = "M";
	p[13].buffer = "N";
	p[14].buffer = "O";
	p[15].buffer = "P";

	char* wordpicked = p[choice].buffer;

	return wordpicked;
}

int numofcharacters2(int l)
{
	p[l].numc = (int)strlen(p[l].buffer);
	int nc = p[l].numc;
	return nc;


}
int numofcharactersinput2(void)
{
	int lengthofinput = (int)strlen(userinput2);

	return lengthofinput;


}

void ConvertWordToInt2(void)
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

void PlayerMovement2(void)
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
void Keyinput2(void)
{
	//whatever that is typed first is stored in 0 position in array, subsequent char is stored in nth position +1
	if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		*(ui2 + nextchar2) = ' ';
		nextchar2++;
	}

	if (CP_Input_KeyTriggered(KEY_A))
	{
		*(ui2 + nextchar2) = 'A';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_B))
	{
		*(ui2 + nextchar2) = 'B';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_C))
	{
		*(ui2 + nextchar2) = 'C';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_D))
	{
		*(ui2 + nextchar2) = 'D';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_E))
	{
		*(ui2 + nextchar2) = 'E';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_F))
	{
		*(ui2 + nextchar2) = 'F';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_G))
	{
		*(ui2 + nextchar2) = 'G';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_H))
	{
		*(ui2 + nextchar2) = 'H';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_I))
	{
		*(ui2 + nextchar2) = 'I';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_J))
	{
		*(ui2 + nextchar2) = 'J';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_K))
	{
		*(ui2 + nextchar2) = 'K';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_L))
	{
		*(ui2 + nextchar2) = 'L';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_M))
	{
		*(ui2 + nextchar2) = 'M';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_N))
	{
		*(ui2 + nextchar2) = 'N';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_O))
	{
		*(ui2 + nextchar2) = 'O';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_P))
	{
		*(ui2 + nextchar2) = 'P';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		*(ui2 + nextchar2) = 'Q';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_R))
	{
		*(ui2 + nextchar2) = 'R';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_S))
	{
		*(ui2 + nextchar2) = 'S';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_T))
	{
		*(ui2 + nextchar2) = 'T';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_U))
	{
		*(ui2 + nextchar2) = 'U';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_V))
	{
		*(ui2 + nextchar2) = 'V';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_W))
	{
		*(ui2 + nextchar2) = 'W';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_X))
	{
		*(ui2 + nextchar2) = 'X';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_Y))
	{
		*(ui2 + nextchar2) = 'Y';
		nextchar2++;
	}
	if (CP_Input_KeyTriggered(KEY_Z))
	{
		*(ui2 + nextchar2) = 'Z';
		nextchar2++;
	}



}
