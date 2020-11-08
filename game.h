#pragma once

void game_init(void);

void game_update(void);

void game_exit(void);
void RandomWord(void);
char* wordlist(int x);
int numofcharacters(int l);
int numofcharactersinput(void);
void ConvertWordToInt(void);
void Keyinput(void);
void DisplayTime(float timeelapsed, float width, float height);
float GetFinalTime(void);
void DisplayScore(int currentscore, float width, float height);
int GetFinalScore(void);