#include "framework.h"
#include "Map.h"
#include "MapDataManager.h"

CMapDataManager::CMapDataManager() : curMap(nullptr)
{
}

CMapDataManager::~CMapDataManager()
{
}

HRESULT CMapDataManager::init()
{

	vecMap.clear();

	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile("save/*.map", &fd);

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			char folderPath[64] = "save/";
			strcat(folderPath, fd.cFileName);
			char* temp = fd.cFileName;
			CMap* tempRoom = new CMap(folderPath);
			vecMap.push_back(tempRoom);
		} while (FindNextFile(hFind, &fd));
	}
    return S_OK;
}

void CMapDataManager::release()
{
}

void CMapDataManager::render()
{
}
