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
	//=============================== BGM =============================
	//=============================== BGM =============================

	SOUND->addSound("title", "sound/title.mp3", false, true);
	SOUND->addSound("mainmenu", "sound/mainmenu.mp3", false, true);
	SOUND->addSound("maptool", "sound/maptool.mp3", false, true);
	SOUND->addSound("player1bg", "sound/player1bg.mp3", false, true);
	SOUND->addSound("player2bg", "sound/player2bg.mp3", false, true);
	SOUND->addSound("gameover", "sound/gameover.mp3", false, false);


	//============================= EFFECT ===========================
	//============================= EFFECT ===========================

	SOUND->addSound("destroy", "sound/destroy.wav", false, false);
	SOUND->addSound("select_menu", "sound/select_menu.wav", false, false);
	SOUND->addSound("move_menu", "sound/move_menu.wav", false, false);
	SOUND->addSound("move_cursor", "sound/move_cursor.wav", false, false);
	SOUND->addSound("select_unit", "sound/select_unit.wav", false, false);
	SOUND->addSound("select", "sound/select.wav", false, false);
	SOUND->addSound("cancel", "sound/cancel.wav", false, false);
	SOUND->addSound("unavailable", "sound/unavailable.wav", false, false);
	SOUND->addSound("capturing", "sound/capturing.wav", false, false);
	SOUND->addSound("capture_finish", "sound/capture_finish.wav", false, false);
	SOUND->addSound("capture_finish", "sound/capture_finish.wav", false, false);
	SOUND->addSound("caterpillar_start", "sound/caterpillar_start.wav", false, true);
	SOUND->addSound("caterpillar_end", "sound/caterpillar_end.wav", false, false);
	SOUND->addSound("walk", "sound/walk.wav", false, true);
	SOUND->addSound("maptool_set", "sound/maptool_set.wav", false, false);
}
