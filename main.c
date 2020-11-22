//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "game.h"
#include "mainmenu.h"

int main(void)
{
	CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
	CP_Engine_Run();
	return 0;
}
