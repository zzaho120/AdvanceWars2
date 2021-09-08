#include "framework.h"
#include "SoundLoad.h"

CSoundLoad::CSoundLoad()
{
}

CSoundLoad::~CSoundLoad()
{
}

void CSoundLoad::resourceLoad()
{
	SOUND->addSound("title", "sound/title.mp3", true, true);
	SOUND->addSound("mainmenu", "sound/mainmenu.mp3", true, true);
	SOUND->addSound("maptool", "sound/maptool.mp3", true, true);
	SOUND->addSound("player1bg", "sound/player1bg.mp3", true, true);
	SOUND->addSound("player2bg", "sound/player2bg.mp3", true, true);
	SOUND->addSound("gameover", "sound/gameover.mp3", true, false);
}
