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
	_astarState = ASTAR_STATE::ASTAR_STATE_END;//�ʱ���� = Ÿ�Ϲ�ġ �Ϸ���
	_selectType = TILE_TYPE::TILE_TYPE_EMPTY;//��ġ�� Ÿ�� �Ӽ� = ��Ÿ��

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


	if (Ci != 0)//0��° ���̾ƴϸ� ��ܶ��� ���
	{
		if (_tile[(Ci - 1) * TILE_NUM_X + Cj].walkable)//��� ��� Ÿ���� �������� �ִٸ�
		{
			if (!_tile[(Ci - 1) * TILE_NUM_X + Cj].listOn)//���¸���Ʈ�� ������ �ȵǾ� �ִ� Ÿ���̶��
			{
				_tile[(Ci - 1) * TILE_NUM_X + Cj].listOn = true;//���¸���Ʈ�� ���ԵǾ���.
				_tile[(Ci - 1) * TILE_NUM_X + Cj].color = RGB(220, 255, 220);
				_tile[(Ci - 1) * TILE_NUM_X + Cj].G = Cg + 10;//Ÿ����G���� Ŭ���� ����Ʈ�� ���� G+10
				_tile[(Ci - 1) * TILE_NUM_X + Cj].parent = _closeList[_lastIndex];//Ÿ���� �θ� Ŭ���� ����Ʈ�� ���������� �߰�
				_openList.push_back(&_tile[(Ci - 1) * TILE_NUM_X + Cj]);//���� ����Ʈ�� �߰�
			}
			else//���¸���Ʈ�� ������ �Ǿ� �ִ� Ÿ���̶��
			{
				if (Cg + 10 < _tile[(Ci - 1) * TILE_NUM_X + Cj].G)//����G������ ���� ����� G���� �۴ٸ�
				{
					_tile[(Ci - 1) * TILE_NUM_X + Cj].G = Cg + 10;//G�� ���Ӱ� ���
					_tile[(Ci - 1) * TILE_NUM_X + Cj].parent = _closeList[_lastIndex];
				}
			}
		}
	}
	if (Cj != 0)//���� : 0��° ���� �ƴ϶��
	{
		//����Ÿ���� �̵������ϴٸ�
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
	if (Cj != TILE_X - 1)//���� :���������� �ƴ϶��
	{
		if (_tile[Ci * TILE_NUM_X + (Cj + 1)].walkable)//����Ÿ���� �̵������ϴٸ�
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
	if (Ci != TILE_Y - 1)//������ ���� �ƴ϶�� �ϴ� ���� ���
	{
		if (_tile[(Ci + 1) * TILE_NUM_X + Cj].walkable)//�ϴ� ��� Ÿ���� �̵������ϴٸ�
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
		int vertical = (_endX - _openList[i]->j) * 10;//����H
		int horizontal = (_endY - _openList[i]->i) * 10;//����H

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
	_openList.erase(_openList.begin() + index);//���� ����Ʈ�� �߰��� Ÿ���� ���¸���Ʈ���� ����
	_lastIndex++;//���� ���߿� �߰��� Ŭ������ �ε���
}

void CAstar::checkArrive()
{
	//Ŭ���� ����Ʈ�� i,j�� ���������� ���ٸ�
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
//	tile = tile->parent;	//Ÿ���� �θ� �����ؼ� showWay�Լ��� �ٽ� �ִ´�.
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