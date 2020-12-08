//---------------------------------------------------------
// file:	bosslvl.c
// author:	Lee Yu Ting
// email:	yuting.lee@digipen.edu
//
// brief:	image of boss done and added in by Hau Hui Yang
//          rest of the code by Lee Yu Ting
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "cprocessing.h"
#include <stdio.h>
#include "game.h"
#include "gamelvl2.h"
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "gameover.h"
#include "transitiontolvl2.h"
#include "bosslvl.h"
#include "youwin.h"
#include "mainmenu.h"

#define FONT_SIZE 25.0f 
#define FONT_SIZE2 30.0f
#define NUMBER_STRINGS 5
#define STRING_MAX_SIZE 10
#define TIME 10
#define SCORE 10
#define LIVES 10
#define KILLS 10
#define word 100
#define LINES 10

#define MAXC 1000
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
int numlines;
char linesbuffer[KILLS];
int numofconsecutivewrong;
int numofconsecutivecorrect;

CP_Color fontColour;

int y, i;

char userinput4[MAXC];
char* ui4 = userinput4;
int nboss;

int nextchar4 = 0;
int numofcorrect4 = 0;
int x, y1, y2, y3, b1;
char* wordchosen;

float enemyx1, enemyy1;
float gridwidth, gridheight;
float velx;

char string1[MAXC];

char* pstr1;
char* pstrboss;
int numofchar;
int intvalue1[MAXC];
float playerx, playery;
CP_Color black, white;

struct WORDS
{
	char* buffer;
	int numc;


} p[MAXW];


void game4_init(void)
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
	b1 = RandomWord4();
	
	//set coordinates of enemy/player
	enemyx1 = 28;
	enemyy1 = 10;
	playerx = 2;
	playery = 10;
	velx = -0.01f;

	//set initial num of lines to type, clear user input and num of consecutively wrong and correct inputs as 0
	numlines = 7;
	memset(userinput4, 0, MAXC * sizeof(char));
	nextchar4 = 0;
	numofconsecutivecorrect = 0;
	numofconsecutivewrong = 0;


}
// initialize variables and CProcessing settings for this gamestate

void game4_update(void)
{

	//set time
	time += CP_System_GetDt();
	finaltime = time;
	finalscore = score;


	//set background
	CP_Image levelbg = CP_Image_Load("./Assets/Level1.png");
	CP_Image_Draw(levelbg, (float)displaywidth / 2, (float)displayheight / 2, (float)CP_Image_GetWidth(levelbg), (float)CP_Image_GetHeight(levelbg), 255);

	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));

	//displays time, score, num of lives and num of lines left
	CP_Settings_Fill(white);
	DisplayTime(time, gridwidth, gridheight);
	DisplayScore(score, gridwidth, gridheight);
	DisplayLives(lives, gridwidth, gridheight);
	DisplayNumOfLines(numlines, gridwidth, gridheight);
	
	CP_Settings_Fill(black);
	
	//draws player
	Drawplayer(playerx, playery, gridwidth, gridheight);

	//use randomized value to obtain a sentence from the list, counts the length and store it in a string
	wordchosen = wordlist4(b1);

	nboss = numofcharacters4(b1);
	
	for (int test = 0; test < nboss; test++)
	{
		string1[test] = *(wordchosen + test);
	}
	pstr1 = string1;

	//draws boss and displays sentence above boss
	CP_Settings_TextSize(FONT_SIZE2);
	Drawboss(pstr1, enemyx1, enemyy1, gridwidth, gridheight);
	enemyx1 += velx;

	//convert sentence in a string to array of int
	ConvertWordToInt4();

	Keyinput4();
	//displays words typed on screen
	CP_Font_DrawTextBox(ui4, 0, 120, 1280);

	//if lines left to type is 0, changes game state
	if (numlines == 0)
	{
		CP_Engine_SetNextGameState(youwin_init, youwin_update, youwin_exit);
	}

	//minus life if enemy reaches playerline
	if ((int)enemyx1 == (int)playerx)
	{
		lives--;
		//if num of lives left is 0 changes gamestate to gameover
		if (lives == 0)
		{
			CP_Engine_SetNextGameState(gameover_init, gameover_update, gameover_exit);
			time = 0;
			score = 0;
			numlines = 0;
			memset(userinput4, 0, MAXC * sizeof(char));
			memset(string1, 0, MAXC * sizeof(char));
			
		}
		//if lives left >0, spawn new enemy with a new word at starting position
		else
		{
			numofcorrect4 = 0;
			memset(string1, 0, MAXC * sizeof(char));
			enemyx1 = 28;
			enemyy1 = 10;
			b1 = RandomWord4();

		}
	}


	//enter to check word typed = random word
	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		//counts length of input
		int lenofinput = numofcharactersinput4();


		if (playery == 10)
		{
			//check if ascii value of each character in the sentence and input is the same
			for (int check = 0; check < lenofinput; check++)
			{
				if (intvalue1[check] == (int)userinput4[check])
				{
					numofcorrect4++;
				}

			}
			if (nboss == lenofinput)
			{
				//if input is same as sentence, increase score, decrease num of lines left to type, spawn new enemy with new sentence
				if (numofcorrect4 == nboss)
				{
					numofcorrect4 = 0;
					score += 50;
					numlines--;
					memset(userinput4, 0, MAXC * sizeof(char));
					memset(string1, 0, MAXC * sizeof(char));
					nextchar4 = 0;
					enemyx1 = enemyx1 + 3;
					enemyy1 = 10;
					b1 = RandomWord4();
					numofconsecutivecorrect++;
					numofconsecutivewrong = 0;
				}
				////if length of input == sentence length but incorrect, clears input
				else if (numofcorrect4 != nboss)
				{
					numofcorrect4 = 0;
					memset(userinput4, 0, MAXC * sizeof(char));
					nextchar4 = 0;
					numofconsecutivewrong++;
				}
			}
			//if length of input != length of sentence, clears input
			else
			{
				numofcorrect4 = 0;
				memset(userinput4, 0, MAXC * sizeof(char));
				nextchar4 = 0;
				numofconsecutivewrong++;
			}
		}

		
		
	}
	//increases enemy speed when sentence is entered is incorrect/enemy reaches player two times in a row
	if (numofconsecutivewrong > 0)
	{
		numofconsecutivecorrect = 0;
	}

	if (velx == -0.01f)
	{
		if (numofconsecutivewrong >= 1)
		{
			velx = -0.02f;
			numofconsecutivewrong = 0;
		}
	}

	if (velx == -0.02f)
	{
		if (numofconsecutivecorrect >= 1)
		{
			velx = -0.01f;
			numofconsecutivecorrect = 0;
		}
	}

	//esc key to go back to main menu
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
	}

}


void game4_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
	memset(userinput4, 0, MAXC * sizeof(char));
	memset(string1, 0, MAXC * sizeof(char));
}

//get a random int from 0 to 19
int RandomWord4(void)
{
	x = CP_Random_RangeInt(0, 12);
	return x;
}

//list of sentences, returns a pointer to first char of chosen sentence
char* wordlist4(int choice)
{
	p[0].buffer = "INSTALL ANTIVIRUS AND FIREWALL SOFTWARES AND UPDATE THEM REGULARLY";
	p[1].buffer = "PRACTISE GOOD CYBER HYGIENE HABITS AND TRY NOT TO FALL PREY TO ONLINE SCAMS";
	p[2].buffer = "REPORT HARMFUL POSTS AND DO NOT RESPOND, BLOCK THE USERS INSTEAD";
	p[3].buffer = "ASK FOR A MODERATOR, ADMINISTRATOR OR SITE OWNER TO INTERVENE";
	p[4].buffer = "NEVER GIVE OUT YOUR PERSONAL INFORMATION TO STRANGERS ONLINE";
	p[5].buffer = "PLEASE IGNORE TROLLING ATTEMPTS AND AVOID TROLLING THE TROLLS";
	p[6].buffer = "TRY TO BE COURTEOUS AND BE CONSIDERATE OF EVERYBODY ONLINE";
	p[7].buffer = "ALWAYS MAKE SURE THAT YOU CREATE UNIQUE AND STRONG PASSWORDS";
	p[8].buffer = "AVOID CLICKING ON SUSPICIOUS LINKS FROM UNTRUSTED SOURCES AND EMAILS";
	p[9].buffer = "BE AWARE OF ANY UNAUTHORIZED USE OF YOUR PERSONAL INFORMATION";
	p[10].buffer = "BE CAUTIOUS ABOUT WHO YOU ACCEPT AS A FRIEND ON SOCIAL MEDIA";
	p[11].buffer = "CUSTOMIZE YOUR PRIVACY SETTINGS TO CONTROL WHO CAN SEE YOUR POSTS";
	p[12].buffer = "BE CAREFUL WHEN INSTALLING THIRD PARTY APPLICATIONS";
	

	char* wordpicked = p[choice].buffer;

	return wordpicked;
}

//counts the length of the sentence
int numofcharacters4(int l)
{
	p[l].numc = (int)strlen(p[l].buffer);
	int nc = p[l].numc;
	return nc;


}
//counts the length of user input
int numofcharactersinput4(void)
{
	int lengthofinput = (int)strlen(userinput4);

	return lengthofinput;


}

//converts an array of char to array of int
void ConvertWordToInt4(void)
{
	for (i = 0; i < nboss; i++)
	{

		intvalue1[i] = (int)*(pstr1 + i);

	}

}

//stores user input in an array
void Keyinput4(void)
{
	//whatever that is typed first is stored in 0 position in array, subsequent char is stored in nth position +1
	if (*(ui4) != '\0')
	{
		if (CP_Input_KeyTriggered(KEY_BACKSPACE))
		{
			nextchar4--;
			*(ui4 + nextchar4) = '\0';

		}
	}
	if (CP_Input_KeyTriggered(KEY_COMMA))
	{
		*(ui4 + nextchar4) = ',';
		nextchar4++;
	}
	
	if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		*(ui4 + nextchar4) = ' ';
		nextchar4++;
	}

	if (CP_Input_KeyTriggered(KEY_A))
	{
		*(ui4 + nextchar4) = 'A';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_B))
	{
		*(ui4 + nextchar4) = 'B';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_C))
	{
		*(ui4 + nextchar4) = 'C';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_D))
	{
		*(ui4 + nextchar4) = 'D';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_E))
	{
		*(ui4 + nextchar4) = 'E';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_F))
	{
		*(ui4 + nextchar4) = 'F';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_G))
	{
		*(ui4 + nextchar4) = 'G';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_H))
	{
		*(ui4 + nextchar4) = 'H';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_I))
	{
		*(ui4 + nextchar4) = 'I';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_J))
	{
		*(ui4 + nextchar4) = 'J';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_K))
	{
		*(ui4 + nextchar4) = 'K';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_L))
	{
		*(ui4 + nextchar4) = 'L';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_M))
	{
		*(ui4 + nextchar4) = 'M';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_N))
	{
		*(ui4 + nextchar4) = 'N';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_O))
	{
		*(ui4 + nextchar4) = 'O';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_P))
	{
		*(ui4 + nextchar4) = 'P';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		*(ui4 + nextchar4) = 'Q';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_R))
	{
		*(ui4 + nextchar4) = 'R';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_S))
	{
		*(ui4 + nextchar4) = 'S';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_T))
	{
		*(ui4 + nextchar4) = 'T';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_U))
	{
		*(ui4 + nextchar4) = 'U';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_V))
	{
		*(ui4 + nextchar4) = 'V';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_W))
	{
		*(ui4 + nextchar4) = 'W';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_X))
	{
		*(ui4 + nextchar4) = 'X';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_Y))
	{
		*(ui4 + nextchar4) = 'Y';
		nextchar4++;
	}
	if (CP_Input_KeyTriggered(KEY_Z))
	{
		*(ui4 + nextchar4) = 'Z';
		nextchar4++;
	}

}

//displays num of lines left to type
void DisplayNumOfLines(int numberlines, float width, float height)
{
	_itoa_s(numlines, linesbuffer, LINES, 10);
	CP_Font_DrawText(linesbuffer, (float)25.2f * width, (float)1 * height);
	CP_Font_DrawText("Lines Left:", (float)21 * width, (float)1 * height);
}
