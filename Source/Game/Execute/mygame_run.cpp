#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../Actors/Character/mygame_operator.h"
#include "../Actors/Operator/Reed/Reed.h"
#include "../mygame.h"
#include "../Map/mygame_mapManager.h"
#include <vector>
#include <iostream>

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////
const int GRID_SIZE = 100;
bool isDragging = false;

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()                            // ���ʹC������
{

}

void CGameStateRun::OnInit()                              // �C������Ȥιϧγ]�w
{
	background.LoadBitmapByString({ "resources/map/0_1.bmp" });
	background.SetTopLeft(0, 0);

	GameMapManager mapManager;	
	std::string mapPath = "resources/map/mapJSON/0_1.json";	

	try{
		game_framework::GameMap gameMap = mapManager.loadMapFromJson(mapPath);
		std::cout << "Success of file open." << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Error of file open." << e.what() << std::endl;
	}

	game_framework::Reed reed;
	reed.image.LoadBitmapByString({ "resources/characters/operators/Reed/Reed_Head.bmp" }, RGB(255, 255, 255));
    reed.position = CPoint(180, 320);



	operators.push_back(reed);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	isDragging = true;
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)    // �B�z�ƹ����ʧ@
{
	if (isDragging)
	{
		operators[0].position.x = (point.x / GRID_SIZE) * GRID_SIZE + 40;
		operators[0].position.y = (point.y / GRID_SIZE) * GRID_SIZE;
		isDragging = false;
	}
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)    // �B�z�ƹ����ʧ@
{
	if (isDragging)
	{
		operators[0].position.x = (point.x / GRID_SIZE) * GRID_SIZE + 40;
		operators[0].position.y = (point.y / GRID_SIZE) * GRID_SIZE;
	}
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)    // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	for (auto& op : operators) {
		op.image.SetTopLeft(op.position.x, op.position.y);
		op.image.ShowBitmap();
	}
}