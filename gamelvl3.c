#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include "gamelvl3.h"
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "gameover.h"
#include "transitiontolvl3.h"
#include "bosslvl.h"

#define FONT_SIZE 33.0f 
#define NUMBER_STRINGS 5
#define STRING_MAX_SIZE 10
#define TIME 10
#define SCORE 10
#define LIVES 10
#define KILLS 10
#define word 100

#define MAXC 20
#define MAXW 50

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

char userinput3[MAXC];
char* ui3 = userinput3;
int n1, n2, n3;

int nextchar3 = 0;
int numofcorrect3 = 0;
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
CP_Color black, white;
struct WORDS
{
	char* buffer;
	int numc;


} p[MAXW];


void game3_init(void)
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
	black = CP_Color_Create(0, 0, 0, 255);
	white = CP_Color_Create(255, 255, 255, 255);

	//set random word
	y1 = RandomWord3();
	y2 = RandomWord3();
	y3 = RandomWord3();

	//set coordinates of enemy/player
	enemyx1 = 28;
	enemyy1 = 5;
	enemyx2 = 28;
	enemyy2 = 10;
	enemyx3 = 28;
	enemyy3 = 15;
	playerx = 2;
	playery = 10;
	velx = -0.03f;
	numkilled = 20;
	lives = 5;
	memset(userinput3, 0, MAXC * sizeof(char));
	nextchar3 = 0;



}
// initialize variables and CProcessing settings for this gamestate

void game3_update(void)
{

	//set time
	time += CP_System_GetDt();
	finaltime = time;
	finalscore = score;


	//set background
	CP_Image levelbg = CP_Image_Load("./Assets/Level1.png");
	CP_Image_Draw(levelbg, (float)displaywidth / 2, (float)displayheight / 2, (float)CP_Image_GetWidth(levelbg), (float)CP_Image_GetHeight(levelbg), 255);

	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));

	CP_Settings_Fill(white);
	DisplayTime(time, gridwidth, gridheight);
	DisplayScore(score, gridwidth, gridheight);
	DisplayLives(lives, gridwidth, gridheight);
	DisplayNumberOfEnemiesLeftToKill(numkilled, gridwidth, gridheight);
	CP_Settings_Fill(black);
	Drawplayer(playerx, playery, gridwidth, gridheight);

	//use randomized value to obtain a word from the wordlist and store it in strings
	wordchosen = wordlist3(y1);
	wordchosen2 = wordlist3(y2);
	wordchosen3 = wordlist3(y3);

	n1 = numofcharacters3(y1);
	n2 = numofcharacters3(y2);
	n3 = numofcharacters3(y3);

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

	ConvertWordToInt3();

	Keyinput3();
	//displays words typed on screen
	CP_Font_DrawText(ui3, 550, 120);

	PlayerMovement();

	if (numkilled == 0)
	{
		CP_Engine_SetNextGameState(game4_init, game4_update, game4_exit);
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
			memset(userinput3, 0, MAXC * sizeof(char));
			memset(string1, 0, 20 * sizeof(char));
			memset(string2, 0, 20 * sizeof(char));
			memset(string3, 0, 20 * sizeof(char));
		}
		else
		{
			numofcorrect3 = 0;
			memset(string1, 0, 20 * sizeof(char));
			enemyx1 = 28;
			enemyy1 = 5;
			y1 = RandomWord3();

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
			memset(userinput3, 0, MAXC * sizeof(char));
			memset(string1, 0, 20 * sizeof(char));
			memset(string2, 0, 20 * sizeof(char));
			memset(string3, 0, 20 * sizeof(char));
		}
		else
		{
			numofcorrect3 = 0;
			memset(string2, 0, 20 * sizeof(char));
			enemyx2 = 28;
			enemyy2 = 10;
			y2 = RandomWord3();


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
			memset(userinput3, 0, MAXC * sizeof(char));
			memset(string1, 0, 20 * sizeof(char));
			memset(string2, 0, 20 * sizeof(char));
			memset(string3, 0, 20 * sizeof(char));
		}
		else
		{
			numofcorrect3 = 0;
			memset(string3, 0, 20 * sizeof(char));
			enemyx3 = 28;
			enemyy3 = 15;
			y3 = RandomWord3();

		}
	}

	//enter to check word typed = random word
	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		//check if they are the same
		int lenofinput = numofcharactersinput3();

		if (playery == 5)
		{
			for (int check = 0; check < lenofinput; check++)
			{
				if (intvalue1[check] == (int)userinput3[check])
				{
					numofcorrect3++;
				}

			}
			if (n1 == lenofinput)
			{
				if (numofcorrect3 == n1)
				{
					numofcorrect3 = 0;
					score++;
					numkilled--;
					memset(userinput3, 0, MAXC * sizeof(char));
					memset(string1, 0, MAXC * sizeof(char));
					nextchar3 = 0;
					enemyx1 = 28;
					enemyy1 = 5;
					y1 = RandomWord3();
				}
				else if (numofcorrect3 != n1)
				{
					numofcorrect3 = 0;
					memset(userinput3, 0, MAXC * sizeof(char));
					nextchar3 = 0;
				}
			}

			else
			{
				numofcorrect3 = 0;
				memset(userinput3, 0, MAXC * sizeof(char));
				nextchar3 = 0;
			}
		}

		if (playery == 10)
		{

			for (int check = 0; check < lenofinput; check++)
			{
				if (intvalue2[check] == (int)userinput3[check])
				{
					numofcorrect3++;
				}

			}
			if (n2 == lenofinput)
			{
				if (numofcorrect3 == n2)
				{
					numofcorrect3 = 0;
					score++;
					numkilled--;
					memset(userinput3, 0, MAXC * sizeof(char));
					memset(string2, 0, MAXC * sizeof(char));
					nextchar3 = 0;
					enemyx2 = 28;
					enemyy2 = 10;
					y2 = RandomWord3();
				}
				else if (numofcorrect3 != n2)
				{
					numofcorrect3 = 0;
					memset(userinput3, 0, MAXC * sizeof(char));
					nextchar3 = 0;
				}
			}

			else
			{
				numofcorrect3 = 0;
				memset(userinput3, 0, MAXC * sizeof(char));
				nextchar3 = 0;
			}
		}

		if (playery == 15)
		{

			for (int check = 0; check < lenofinput; check++)
			{
				if (intvalue3[check] == (int)userinput3[check])
				{
					numofcorrect3++;
				}

			}
			if (n3 == lenofinput)
			{
				if (numofcorrect3 == n3)
				{
					numofcorrect3 = 0;
					score++;
					numkilled--;
					memset(userinput3, 0, MAXC * sizeof(char));
					memset(string3, 0, MAXC * sizeof(char));
					nextchar3 = 0;
					enemyx3 = 28;
					enemyy3 = 15;
					y3 = RandomWord3();
				}
				else if (numofcorrect3 != n3)
				{
					numofcorrect3 = 0;
					memset(userinput3, 0, MAXC * sizeof(char));
					nextchar3 = 0;
				}
			}

			else
			{
				numofcorrect3 = 0;
				memset(userinput3, 0, MAXC * sizeof(char));
				nextchar3 = 0;
			}
		}
	}
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}

}


void game3_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

int RandomWord3(void)
{
	x = CP_Random_RangeInt(0, 13);
	return x;
}

char* wordlist3(int choice)
{
	p[0].buffer = "#PH1$HING";
	p[1].buffer = "M@LW@R3!";
	p[2].buffer = "*$!@*&*";
	p[3].buffer = "($P00F1NG)";
	p[4].buffer = "ENCRYP7iNG";
	p[5].buffer = "@DWARV3";
	p[6].buffer = "A77ACK!!!";
	p[7].buffer = "F1R3W@LL";
	p[8].buffer = "******";
	p[9].buffer = "#WHIT3HAT";
	p[10].buffer = "S P @ M";
	p[11].buffer = "CACHE^";
	p[12].buffer = "H@CK3RRR";
	p[13].buffer = "*ANONYMOUS*";

	char* wordpicked = p[choice].buffer;

	return wordpicked;
}

int numofcharacters3(int l)
{
	p[l].numc = (int)strlen(p[l].buffer);
	int nc = p[l].numc;
	return nc;


}
int numofcharactersinput3(void)
{
	int lengthofinput = (int)strlen(userinput3);

	return lengthofinput;


}

void ConvertWordToInt3(void)
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

void PlayerMovement3(void)
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
void Keyinput3(void)
{

	//whatever that is typed first is stored in 0 position in array, subsequent char is stored in nth position +1
	if (*(ui3) != '\0')
	{
		if (CP_Input_KeyTriggered(KEY_BACKSPACE))
		{
			nextchar3--;
			*(ui3 + nextchar3) = '\0';

		}
	}

	if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		*(ui3 + nextchar3) = ' ';
		nextchar3++;
	}

	if (CP_Input_KeyTriggered(KEY_A))
	{
		*(ui3 + nextchar3) = 'A';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_B))
	{
		*(ui3 + nextchar3) = 'B';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_C))
	{
		*(ui3 + nextchar3) = 'C';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_D))
	{
		*(ui3 + nextchar3) = 'D';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_E))
	{
		*(ui3 + nextchar3) = 'E';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_F))
	{
		*(ui3 + nextchar3) = 'F';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_G))
	{
		*(ui3 + nextchar3) = 'G';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_H))
	{
		*(ui3 + nextchar3) = 'H';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_I))
	{
		*(ui3 + nextchar3) = 'I';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_J))
	{
		*(ui3 + nextchar3) = 'J';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_K))
	{
		*(ui3 + nextchar3) = 'K';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_L))
	{
		*(ui3 + nextchar3) = 'L';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_M))
	{
		*(ui3 + nextchar3) = 'M';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_N))
	{
		*(ui3 + nextchar3) = 'N';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_O))
	{
		*(ui3 + nextchar3) = 'O';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_P))
	{
		*(ui3 + nextchar3) = 'P';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		*(ui3 + nextchar3) = 'Q';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_R))
	{
		*(ui3 + nextchar3) = 'R';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_S))
	{
		*(ui3 + nextchar3) = 'S';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_T))
	{
		*(ui3 + nextchar3) = 'T';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_U))
	{
		*(ui3 + nextchar3) = 'U';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_V))
	{
		*(ui3 + nextchar3) = 'V';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_W))
	{
		*(ui3 + nextchar3) = 'W';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_X))
	{
		*(ui3 + nextchar3) = 'X';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_Y))
	{
		*(ui3 + nextchar3) = 'Y';
		nextchar3++;
	}
	if (CP_Input_KeyTriggered(KEY_Z))
	{
		*(ui3 + nextchar3) = 'Z';
		nextchar3++;
	}

	if (CP_Input_KeyDown(KEY_LEFT_SHIFT) || CP_Input_KeyDown(KEY_RIGHT_SHIFT))
	{
		if (CP_Input_KeyTriggered(KEY_1))
		{
			*(ui3 + nextchar3) = '!';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_2))
		{
			*(ui3 + nextchar3) = '@';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_3))
		{
			*(ui3 + nextchar3) = '#';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_4))
		{
			*(ui3 + nextchar3) = '$';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_5))
		{
			*(ui3 + nextchar3) = '%';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_6))
		{
			*(ui3 + nextchar3) = '^';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_7))
		{
			*(ui3 + nextchar3) = '&';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_8))
		{
			*(ui3 + nextchar3) = '*';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_9))
		{
			*(ui3 + nextchar3) = '(';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_0))
		{
			*(ui3 + nextchar3) = ')';
			nextchar3++;
		}
	}
	else
	{
		if (CP_Input_KeyTriggered(KEY_1))
		{
			*(ui3 + nextchar3) = '1';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_2))
		{
			*(ui3 + nextchar3) = '2';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_3))
		{
			*(ui3 + nextchar3) = '3';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_4))
		{
			*(ui3 + nextchar3) = '4';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_5))
		{
			*(ui3 + nextchar3) = '5';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_6))
		{
			*(ui3 + nextchar3) = '6';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_7))
		{
			*(ui3 + nextchar3) = '7';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_8))
		{
			*(ui3 + nextchar3) = '8';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_9))
		{
			*(ui3 + nextchar3) = '9';
			nextchar3++;
		}
		if (CP_Input_KeyTriggered(KEY_0))
		{
			*(ui3 + nextchar3) = '0';
			nextchar3++;
		}
	}
}
