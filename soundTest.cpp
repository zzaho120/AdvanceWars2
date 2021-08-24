#include "framework.h"
#include "soundTest.h"

soundTest::soundTest()
{
}

soundTest::~soundTest()
{
}

HRESULT soundTest::init()
{

    SOUND->addSound("ī��", "sound/ü��.mp3", true, true);
    return S_OK;
}

void soundTest::release()
{
}

void soundTest::update()
{
    if (InputManager->isOnceKeyDown('Q'))
    {
        SOUND->play("ī��",1.0f);
    }
    if (InputManager->isOnceKeyDown('S'))
    {
        SOUND->stop("ī��");
    }
    if (InputManager->isOnceKeyDown('T'))
    {
        SOUND->resume("ī��");
    }
    if (InputManager->isOnceKeyDown('P'))
    {
        SOUND->pause("ī��");
    }
}
