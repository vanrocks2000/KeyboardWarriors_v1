#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "gameover.h"
#include "gamelvl2.h"
#include "transitiontolvl2.h"
#include "bosslvl.h"
#include "mainmenu.h"

#define FONT_SIZE 25.0f 
#define FONT_SIZE2 35.0f
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
int numofconsecutivewrong;
int numofconsecutivecorrect;


CP_Color black, white;

int y, i;

char userinput[MAXC];
char* ui = userinput;
int n1, n2, n3;

int nextchar = 0;
int numofcorrect = 0;
int current_frame = 0;
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
	
	black = CP_Color_Create(0, 0, 0, 255);
	white = CP_Color_Create(255, 255, 255, 255);
	
	
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
	velx = -0.07f;
	lives = 3;
	numkilled = 15;
	numofconsecutivecorrect = 0;
	numofconsecutivewrong = 0;
	memset(userinput, 0, MAXC * sizeof(char));
	nextchar = 0;
	score = 0;
	time = 0;
}
// initialize variables and CProcessing settings for this gamestate

void game_update(void)
{
	
	//set time
	time += CP_System_GetDt();
	finaltime = time;
	finalscore = score;


	//set background
	CP_Image levelbg = CP_Image_Load("./Assets/Level1.png");
	CP_Image_Draw(levelbg, (float)displaywidth / 2, (float)displayheight / 2, (float)CP_Image_GetWidth(levelbg), (float)CP_Image_GetHeight(levelbg) , 255);

	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));

	CP_Settings_Fill(white);
	DisplayTime(time, gridwidth, gridheight);
	DisplayScore(score, gridwidth, gridheight);
	DisplayLives(lives, gridwidth, gridheight);
	DisplayNumberOfEnemiesLeftToKill(numkilled, gridwidth, gridheight);
	CP_Settings_Fill(black);
	CP_Settings_TextSize(FONT_SIZE2);
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

	if (current_frame == 0)
	{
		Drawenemy(pstr1, enemyx1, enemyy1, gridwidth, gridheight);
		Drawenemy(pstr2, enemyx2, enemyy2, gridwidth, gridheight);
		Drawenemy(pstr3, enemyx3, enemyy3, gridwidth, gridheight);
		current_frame++;
	}

	else if (current_frame == 1)
	{
		Drawenemy1(pstr1, enemyx1, enemyy1, gridwidth, gridheight);
		Drawenemy1(pstr2, enemyx2, enemyy2, gridwidth, gridheight);
		Drawenemy1(pstr3, enemyx3, enemyy3, gridwidth, gridheight);
		current_frame++;
	}

	else if (current_frame == 2)
	{
		Drawenemy2(pstr1, enemyx1, enemyy1, gridwidth, gridheight);
		Drawenemy2(pstr2, enemyx2, enemyy2, gridwidth, gridheight);
		Drawenemy2(pstr3, enemyx3, enemyy3, gridwidth, gridheight);
		current_frame++;
	}

	else if (current_frame == 3)
	{
		Drawenemy3(pstr1, enemyx1, enemyy1, gridwidth, gridheight);
		Drawenemy3(pstr2, enemyx2, enemyy2, gridwidth, gridheight);
		Drawenemy3(pstr3, enemyx3, enemyy3, gridwidth, gridheight);
		current_frame++;
	}

	else if (current_frame == 4)
	{
		Drawenemy4(pstr1, enemyx1, enemyy1, gridwidth, gridheight);
		Drawenemy4(pstr2, enemyx2, enemyy2, gridwidth, gridheight);
		Drawenemy4(pstr3, enemyx3, enemyy3, gridwidth, gridheight);
		current_frame++;
	}

	else if (current_frame == 5)
	{
		Drawenemy5(pstr1, enemyx1, enemyy1, gridwidth, gridheight);
		Drawenemy5(pstr2, enemyx2, enemyy2, gridwidth, gridheight);
		Drawenemy5(pstr3, enemyx3, enemyy3, gridwidth, gridheight);
		current_frame++;
	}

	else if (current_frame == 6)
	{
		Drawenemy6(pstr1, enemyx1, enemyy1, gridwidth, gridheight);
		Drawenemy6(pstr2, enemyx2, enemyy2, gridwidth, gridheight);
		Drawenemy6(pstr3, enemyx3, enemyy3, gridwidth, gridheight);
		current_frame++;
	}

	else if (current_frame == 7)
	{
		Drawenemy7(pstr1, enemyx1, enemyy1, gridwidth, gridheight);
		Drawenemy7(pstr2, enemyx2, enemyy2, gridwidth, gridheight);
		Drawenemy7(pstr3, enemyx3, enemyy3, gridwidth, gridheight);
		current_frame = 0;
	}

	enemyx1 += velx;
	enemyx2 += velx;
	enemyx3 += velx;
	
	ConvertWordToInt();
	
	Keyinput();
	//displays words typed on screen
	CP_Font_DrawText(ui, 550, 120);

	PlayerMovement();
	
	if (numkilled == 0)
	{
		memset(string1, 0, 20 * sizeof(char));
		memset(string2, 0, 20 * sizeof(char));
		memset(string3, 0, 20 * sizeof(char));
		//CP_Engine_SetNextGameState(transitiontolvl2_init, transitiontolvl2_update, transitiontolvl2_exit);
		CP_Engine_SetNextGameState(transitiontolvl2_init, transitiontolvl2_update, transitiontolvl2_exit);
	}

	//minus life if enemy reaches playerline
	if ((int)enemyx1 == (int)playerx)
	{
		lives -= 1;
		numofconsecutivewrong++;
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
		numofconsecutivewrong++;
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
		numofconsecutivewrong++;
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
					numofconsecutivecorrect++;
					numofconsecutivewrong = 0;
					x1 = RandomWord();
				}
				else if (numofcorrect != n1)
				{
					numofcorrect = 0;
					memset(userinput, 0, MAXC * sizeof(char));
					nextchar = 0;
					numofconsecutivewrong++;
				}
			}

			else
			{
				numofcorrect = 0;
				memset(userinput, 0, MAXC * sizeof(char));
				nextchar = 0;
				numofconsecutivewrong++;
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
					numofconsecutivecorrect++;
					numofconsecutivewrong = 0;
					x2 = RandomWord();
				}
				else if (numofcorrect != n2)
				{
					numofcorrect = 0;
					memset(userinput, 0, MAXC * sizeof(char));
					nextchar = 0;
					numofconsecutivewrong++;
				}
			}

			else
			{
				numofcorrect = 0;
				memset(userinput, 0, MAXC * sizeof(char));
				nextchar = 0;
				numofconsecutivewrong++;
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
					numofconsecutivecorrect++;
					numofconsecutivewrong = 0;
					x3 = RandomWord();
				}
				 else if (numofcorrect != n3)
				{
					numofcorrect = 0;
					memset(userinput, 0, MAXC * sizeof(char));
					nextchar = 0;
					numofconsecutivewrong++;
				}
			}

			else
			{
				numofcorrect = 0;
				memset(userinput, 0, MAXC * sizeof(char));
				nextchar = 0;
				numofconsecutivewrong++;
			}
		}	
	}

	if (numofconsecutivewrong > 0)
	{
		numofconsecutivecorrect = 0;
	}

	if (velx == -0.07f)
	{
		if (numofconsecutivewrong >= 2)
		{
			velx = -0.10f;
			numofconsecutivewrong = 0;
		}
	}

	if (velx == -0.10f)
	{
		if (numofconsecutivecorrect >= 2)
		{
			velx = -0.07f;
			numofconsecutivecorrect = 0;
		}
	}
	/*_itoa_s(numofconsecutivecorrect, wordbuf, word, 10);
	CP_Font_DrawText(wordbuf, (float)5 * gridwidth, (float)2 * gridheight);
	_itoa_s(numofconsecutivewrong, wordbuf, word, 10);
	CP_Font_DrawText(wordbuf, (float)6 * gridwidth, (float)2 * gridheight);*/

	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
	}

}


void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
	memset(userinput, 0, MAXC * sizeof(char));
	memset(string1, 0, 20 * sizeof(char));
	memset(string2, 0, 20 * sizeof(char));
	memset(string3, 0, 20 * sizeof(char));
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
	p[16].buffer = "COMPUTER";
	p[17].buffer = "MEME";
	p[18].buffer = "BITCOIN";
	p[19].buffer = "PROGRAMMING";


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
	if (*(ui) != '\0')
	{
		if (CP_Input_KeyTriggered(KEY_BACKSPACE))
		{
			nextchar--;
			*(ui + nextchar) = '\0';

		}
	}

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
	CP_Settings_TextSize(FONT_SIZE);
	_itoa_s((int)timeelapsed, timebuffer, TIME, 10);
	CP_Font_DrawText(timebuffer, (float)3 * width, (float)1 * height);
	CP_Font_DrawText("Time:", (float)1 * width, (float)1 * height);

}

float GetFinalTime(void)
{
	return finaltime;
}

void DisplayLives(int livesleft, float width, float height)
{
	CP_Settings_TextSize(FONT_SIZE);
	_itoa_s(lives, lifebuffer, LIVES, 10);
	CP_Font_DrawText(lifebuffer, (float)12.3f * width, (float)1 * height);
	CP_Font_DrawText("Lives Left:", (float)8 * width, (float)1 * height);

}

void DisplayScore(int currentscore, float width, float height)
{
	CP_Settings_TextSize(FONT_SIZE);
	_itoa_s(score, scorebuffer, SCORE, 10);
	CP_Font_DrawText(scorebuffer, (float)17.5 * width, (float)1 * height);
	CP_Font_DrawText("Score:", (float)15 * width, (float)1 * height);

}

int GetFinalScore(void)
{
	return finalscore;
}

void DisplayNumberOfEnemiesLeftToKill(int numberkilled, float width, float height)
{
	CP_Settings_TextSize(FONT_SIZE);
	_itoa_s(numkilled, killedbuffer, KILLS, 10);
	CP_Font_DrawText(killedbuffer, (float)26.5 * width, (float)1 * height);
	CP_Font_DrawText("Enemies To Kill:", (float)20.5 * width, (float)1 * height);

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