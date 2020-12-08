//---------------------------------------------------------
// file:	game.h
// author:	Lee Yu Ting
// email:	yuting.lee@digipen.edu
//
// brief:	code done by Lee Yu Ting
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once

void game_init(void);
void game_update(void);
void game_exit(void);
int RandomWord(void);
char* wordlist(int x);
int numofcharacters(int l);
int numofcharactersinput(void);
void ConvertWordToInt(void);
void PlayerMovement(void);
void Keyinput(void);
void DisplayTime(float timeelapsed, float width, float height);
float GetFinalTime(void);
void DisplayScore(int currentscore, float width, float height);
int GetFinalScore(void);
void DisplayLives(int livesleft, float width, float height);
void DisplayNumberOfEnemiesLeftToKill(int numberkilled, float width, float height);