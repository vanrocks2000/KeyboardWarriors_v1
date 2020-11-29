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

#define FONT_SIZE 33.0f 
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
	numlines = 7;
	memset(userinput4, 0, MAXC * sizeof(char));
	nextchar4 = 0;
	lives = 1;
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

	CP_Settings_Fill(white);
	DisplayTime(time, gridwidth, gridheight);
	DisplayScore(score, gridwidth, gridheight);
	DisplayLives(lives, gridwidth, gridheight);
	DisplayNumOfLines(numlines, gridwidth, gridheight);
	
	CP_Settings_Fill(black);
	Drawplayer(playerx, playery, gridwidth, gridheight);

	//use randomized value to obtain a word from the wordlist and store it in strings
	wordchosen = wordlist4(b1);

	nboss = numofcharacters4(b1);
	

	for (int test = 0; test < nboss; test++)
	{
		string1[test] = *(wordchosen + test);
	}
	

	pstr1 = string1;
	
	Drawboss(pstr1, enemyx1, enemyy1, gridwidth, gridheight);

	enemyx1 += velx;


	ConvertWordToInt4();

	Keyinput4();
	//displays words typed on screen
	CP_Font_DrawTextBox(ui4, 0, 120, 1280);


	if (numlines == 0)
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
			numlines = 0;
			memset(userinput4, 0, MAXC * sizeof(char));
			memset(string1, 0, MAXC * sizeof(char));
			
		}
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
		//check if they are the same
		int lenofinput = numofcharactersinput4();


		if (playery == 10)
		{

			for (int check = 0; check < lenofinput; check++)
			{
				if (intvalue1[check] == (int)userinput4[check])
				{
					numofcorrect4++;
				}

			}
			if (nboss == lenofinput)
			{
				if (numofcorrect4 == nboss)
				{
					numofcorrect4 = 0;
					score++;
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
				else if (numofcorrect4 != nboss)
				{
					numofcorrect4 = 0;
					memset(userinput4, 0, MAXC * sizeof(char));
					nextchar4 = 0;
					numofconsecutivewrong++;
				}
			}

			else
			{
				numofcorrect4 = 0;
				memset(userinput4, 0, MAXC * sizeof(char));
				nextchar4 = 0;
				numofconsecutivewrong++;
			}
		}

		
		
	}
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
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}

}


void game4_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

int RandomWord4(void)
{
	x = CP_Random_RangeInt(0, 3);
	return x;
}

char* wordlist4(int choice)
{
	p[0].buffer = "INTERNET SAFETY IS A LOT MORE THAN JUST ENSURING THAT YOUR COMPUTER HAS THE LATEST ANTIVIRUS AND FIREWALL SOFTWARE";
	/*pstrboss = "Internet safety is a lot more\n\
    than just ensuring that your\n\
    computer has the latest\n\
    antivirus and firewall\n\
	software installed. " ;*/
	p[1].buffer = "IT IS ABOUT PRACTISING GOOD CYBER HYGIENE HABITS AND NOT FALLING PREY TO ONLINE SCAMS";
	p[2].buffer = "REPORT HARMFUL POSTS AND DO NOT RESPOND, BLOCK THE USERS INSTEAD";
	p[3].buffer = "ASK FOR A MODERATOR, ADMINISTRATOR OR SITE OWNER TO INTERVENE";
	p[4].buffer = "NEVER GIVE OUT YOUR PERSONAL INFORMATION ONLINE TO STRANGERS";
	p[5].buffer = "IGNORE TROLLING ATTEMPTS AND AVOID TROLLING THE TROLLS";
	p[6].buffer = "BE COURTEOUS AND CONSIDERATE OF EVERYBODY ONLINE";
	/*p[7].buffer = "H";
	p[8].buffer = "I";
	p[9].buffer = "J";
	p[10].buffer = "K";
	p[11].buffer = "L";
	p[12].buffer = "M";
	p[13].buffer = "N";
	p[14].buffer = "O";
	p[15].buffer = "P";*/

	char* wordpicked = p[choice].buffer;

	return wordpicked;
}

int numofcharacters4(int l)
{
	p[l].numc = (int)strlen(p[l].buffer);
	int nc = p[l].numc;
	return nc;


}
int numofcharactersinput4(void)
{
	int lengthofinput = (int)strlen(userinput4);

	return lengthofinput;


}

void ConvertWordToInt4(void)
{
	for (i = 0; i < nboss; i++)
	{

		intvalue1[i] = (int)*(pstr1 + i);

	}


}


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
	if (CP_Input_KeyTriggered(KEY_PERIOD))
	{
		*(ui4 + nextchar4) = '.';
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

void DisplayNumOfLines(int numberlines, float width, float height)
{
	_itoa_s(numlines, linesbuffer, LINES, 10);
	CP_Font_DrawText(linesbuffer, (float)26 * width, (float)1 * height);
	CP_Font_DrawText("Lines Left:", (float)21 * width, (float)1 * height);
}
