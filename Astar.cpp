#include "framework.h"
#include "Astar.h"
#include "Map.h"
CAstar::CAstar()
{
}

CAstar::~CAstar()
{
}

HRESULT CAstar::init()
{
	_astarState = ASTAR_STATE::ASTAR_STATE_END;//초기상태 = 타일배치 완료전
	_selectType = TILE_TYPE::TILE_TYPE_EMPTY;//배치할 타일 속성 = 빈타일

	for (int i = 0; i < TILE_NUM_Y; i++)
	{
		for (int j = 0; j < TILE_NUM_X; j++)
		{
			_tile[i * TILE_NUM_X + j].type = TILE_TYPE::TILE_TYPE_EMPTY;
			_tile[i * TILE_NUM_X + j].color = RGB(255, 255, 255);
			_tile[i * TILE_NUM_X + j].parent = NULL;
			_tile[i * TILE_NUM_X + j].F = BIGNUM;
			_tile[i * TILE_NUM_X + j].H = 0;
			_tile[i * TILE_NUM_X + j].i = i;
			_tile[i * TILE_NUM_X + j].j = j;
			_tile[i * TILE_NUM_X + j].pos = STAGE->getCurMap()->getTile()[i * TILE_NUM_X + j]->getPos();
			_tile[i * TILE_NUM_X + j].rc = RectMake(_tile[i * TILE_NUM_X + j].pos.x, _tile[i * TILE_NUM_X + j].pos.y, 
				_tile[i * TILE_NUM_X + j].pos.x + TILE_SIZE_X, _tile[i * TILE_NUM_X + j].pos.y + TILE_SIZE_Y);
			_tile[i * TILE_NUM_X + j].tileIdx = i * TILE_NUM_X + j;
		}
	}
	return S_OK;

	isArrive = false;
}

void CAstar::release()
{
}

void CAstar::update()
{
	/*if (_astarState == ASTAR_STATE::ASTAR_STATE_END)
	{
		tileComposition();
	}
	if (InputManager->isOnceKeyDown(VK_SPACE) && _startPointSet && _endPointSet && _astarState == ASTAR_STATE::ASTAR_STATE_END)
	{
		tileInitializing();
	}
	if (InputManager->isOnceKeyDown('5'))
	{
		_openList.clear();
		_closeList.clear();
		init();
	}
	if (_astarState == ASTAR_STATE::ASTAR_STATE_END || _astarState == ASTAR_STATE::ASTAR_STATE_FOUND || _astarState == ASTAR_STATE::ASTAR_STATE_NOWAY)return;*/
	tileInitializing();
	while (!isArrive)
	{
		addOpenList();
		caculateH();
		caculateF();
		addCloseList();
		checkArrive();
	}
}

void CAstar::tileInitializing()
{

	for (size_t i = 0; i < TILE_NUM_Y; i++)
	{
		for (size_t j = 0; j < TILE_NUM_X; j++)
		{
			switch (_tile[i * TILE_NUM_X + j].type)
			{
			case TILE_TYPE::TILE_TYPE_EMPTY:
			{
				_tile[i * TILE_NUM_X + j].walkable = true;
				_tile[i * TILE_NUM_X + j].listOn = false;
			}
			break;
			case TILE_TYPE::TILE_TYPE_WALL:
			{
				_tile[i * TILE_NUM_X + j].walkable = false;
				_tile[i * TILE_NUM_X + j].listOn = false;
			}
			break;
			case TILE_TYPE::TILE_TYPE_START:
			{
				_tile[i * TILE_NUM_X + j].walkable = false;
				_tile[i * TILE_NUM_X + j].listOn = false;
				_closeList.push_back(&_tile[i * TILE_NUM_X + j]);
			}
			break;
			case TILE_TYPE::TILE_TYPE_END:
			{
				_endX = j;
				_endY = i;
				_tile[i * TILE_NUM_X + j].walkable = true;
				_tile[i * TILE_NUM_X + j].listOn = false;
			}
			break;
			}
		}
	}
	_astarState = ASTAR_STATE::ASTAR_STATE_SEARCHING;
	_lastIndex = 0;
}

void CAstar::addOpenList()
{
	Ci = _closeList[_lastIndex]->i;
	Cj = _closeList[_lastIndex]->j;
	Cg = _closeList[_lastIndex]->G;


	if (Ci != 0)//0번째 줄이아니면 상단라인 계산
	{
		if (_tile[(Ci - 1) * TILE_NUM_X + Cj].walkable)//상단 가운데 타일이 지나갈수 있다면
		{
			if (!_tile[(Ci - 1) * TILE_NUM_X + Cj].listOn)//오픈리스트에 포함이 안되어 있는 타일이라면
			{
				_tile[(Ci - 1) * TILE_NUM_X + Cj].listOn = true;//오픈리스트에 포함되었다.
				_tile[(Ci - 1) * TILE_NUM_X + Cj].color = RGB(220, 255, 220);
				_tile[(Ci - 1) * TILE_NUM_X + Cj].G = Cg + 10;//타일의G값을 클로즈 리스트의 누적 G+10
				_tile[(Ci - 1) * TILE_NUM_X + Cj].parent = _closeList[_lastIndex];//타일의 부모를 클로즈 리스트의 마지막으로 추가
				_openList.push_back(&_tile[(Ci - 1) * TILE_NUM_X + Cj]);//오픈 리스트에 추가
			}
			else//오픈리스트에 포함이 되어 있던 타일이라면
			{
				if (Cg + 10 < _tile[(Ci - 1) * TILE_NUM_X + Cj].G)//기존G값보다 새로 계산한 G값이 작다면
				{
					_tile[(Ci - 1) * TILE_NUM_X + Cj].G = Cg + 10;//G값 새롭게 계산
					_tile[(Ci - 1) * TILE_NUM_X + Cj].parent = _closeList[_lastIndex];
				}
			}
		}
	}
	if (Cj != 0)//좌측 : 0번째 열이 아니라면
	{
		//좌측타일이 이동가능하다면
		if (_tile[Ci * TILE_NUM_X + (Cj - 1)].walkable)
		{
			if (!_tile[Ci * TILE_NUM_X + (Cj - 1)].listOn)
			{
				_tile[Ci * TILE_NUM_X + (Cj - 1)].listOn = true;
				_tile[Ci * TILE_NUM_X + (Cj - 1)].color = RGB(220, 255, 220);
				_tile[Ci * TILE_NUM_X + (Cj - 1)].G = Cg + 10;
				_tile[Ci * TILE_NUM_X + (Cj - 1)].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci * TILE_NUM_X + (Cj - 1)]);
			}
			else
			{
				if (Cg + 10 < _tile[Ci * TILE_NUM_X + (Cj - 1)].G)
				{
					_tile[Ci * TILE_NUM_X + (Cj - 1)].G = Cg + 10;
					_tile[Ci * TILE_NUM_X + (Cj - 1)].parent = _closeList[_lastIndex];
				}
			}
		}
	}
	if (Cj != TILE_X - 1)//우측 :마지막열이 아니라면
	{
		if (_tile[Ci * TILE_NUM_X + (Cj + 1)].walkable)//우측타일이 이동가능하다면
		{
			if (!_tile[Ci * TILE_NUM_X + (Cj + 1)].listOn)
			{
				_tile[Ci * TILE_NUM_X + (Cj + 1)].listOn = true;
				_tile[Ci * TILE_NUM_X + (Cj + 1)].color = RGB(220, 255, 220);
				_tile[Ci * TILE_NUM_X + (Cj + 1)].G = Cg + 10;
				_tile[Ci * TILE_NUM_X + (Cj + 1)].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci * TILE_NUM_X + (Cj + 1)]);
			}
			else
			{
				if (Cg + 10 < _tile[Ci * TILE_NUM_X + (Cj + 1)].G)
				{
					_tile[Ci * TILE_NUM_X + (Cj + 1)].G = Cg + 10;
					_tile[Ci * TILE_NUM_X + (Cj + 1)].parent = _closeList[_lastIndex];
				}
			}
		}
	}
	if (Ci != TILE_Y - 1)//마지막 행이 아니라면 하단 라인 계산
	{
		if (_tile[(Ci + 1) * TILE_NUM_X + Cj].walkable)//하단 가운데 타일이 이동가능하다면
		{
			if (!_tile[(Ci + 1) * TILE_NUM_X + Cj].listOn)
			{
				_tile[(Ci + 1) * TILE_NUM_X + Cj].listOn = true;
				_tile[(Ci + 1) * TILE_NUM_X + Cj].color = RGB(220, 255, 220);
				_tile[(Ci + 1) * TILE_NUM_X + Cj].G = Cg + 10;
				_tile[(Ci + 1) * TILE_NUM_X + Cj].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[(Ci + 1) * TILE_NUM_X + Cj]);
			}
			else
			{
				if (Cg + 10 < _tile[(Ci + 1) * TILE_NUM_X + Cj].G)
				{
					_tile[(Ci + 1) * TILE_NUM_X + Cj].G = Cg + 10;
					_tile[(Ci + 1) * TILE_NUM_X + Cj].parent = _closeList[_lastIndex];
				}
			}
		}
	}
}

void CAstar::caculateH()
{
	for (size_t i = 0; i < _openList.size(); i++)
	{
		int vertical = (_endX - _openList[i]->j) * 10;//가로H
		int horizontal = (_endY - _openList[i]->i) * 10;//세로H

		if (vertical < 0) vertical *= -1;
		if (horizontal < 0) horizontal *= -1;

		_openList[i]->H = vertical + horizontal;
	}
}

void CAstar::caculateF()
{
	for (size_t i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;
	}
}

void CAstar::addCloseList()
{
	if (_openList.size() == 0)
	{
		_astarState = ASTAR_STATE::ASTAR_STATE_NOWAY;
		return;
	}
	int index = 0;
	int lowest = BIGNUM;

	for (size_t i = 0; i < _openList.size(); i++)
	{
		if (_openList[i]->F < lowest)
		{
			lowest = _openList[i]->F;
			index = i;
		}
	}


	_openList[index]->color = RGB(180, 180, 255);
	_closeList.push_back(_openList[index]);
	roadList.push(_openList[index]->tileIdx);
	_openList.erase(_openList.begin() + index);//오픈 리스트에 추가된 타일은 오픈리스트에서 제외
	_lastIndex++;//가장 나중에 추가된 클로즈의 인덱스
}

void CAstar::checkArrive()
{
	//클로즈 리스트의 i,j가 도착지점과 같다면
	if (_closeList[_lastIndex]->i == _endY && _closeList[_lastIndex]->j == _endX)
	{
		isArrive = true;
		_astarState = ASTAR_STATE::ASTAR_STATE_FOUND;
	}
}
//
//void CAstar::showWay(aStarTile* tile)
//{
//	if (!(tile->i == _endY && tile->j == _endX))
//	{
//		tile->color = RGB(255, 180, 180);
//		roadList.push(tile->tileIdx);
//	}
//	tile = tile->parent;	//타일의 부모를 참조해서 showWay함수에 다시 넣는다.
//
//	if (tile->parent == NULL)
//	{
//		return;
//	}
//	else
//		showWay(tile);
//}

void CAstar::setStartEnd(int startIdx, int endIdx)
{
	if (!roadList.empty())
		roadList.pop();
	_openList.clear();
	_closeList.clear();

	_startX = startIdx % TILE_NUM_X;
	_startY = startIdx / TILE_NUM_X;
	_endX = endIdx % TILE_NUM_X;
	_endY = endIdx / TILE_NUM_X;

	_tile[_startY * TILE_NUM_X + _startX].type = TILE_TYPE::TILE_TYPE_START;
	_tile[_endY * TILE_NUM_X + _endX].type = TILE_TYPE::TILE_TYPE_END;
}