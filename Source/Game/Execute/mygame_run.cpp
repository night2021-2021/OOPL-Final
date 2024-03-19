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
#include <limits>
#include <iostream>


using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
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

void CGameStateRun::OnMove()                            // 移動遊戲元素
{

}

void CGameStateRun::OnInit()                              // 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({ "resources/map/0_1.bmp" });
	background.SetTopLeft(0, 0);

	GameMapManager mapManager;	
	std::string logicMapPath = "resources/map/mapJSON/0_1.json";	
	std::string visualMapPath = "resources/map/mapJSON/0-1_visual.json";
	try{
		game_framework::GameMap gameMap = mapManager.loadLogicMapFromJson(logicMapPath);
		std::cout << "Success of logic file open." << std::endl;

		mapManager.loadVisualMapFromJson(visualMapPath);
		std::cout << "Visual map loaded successfully." << std::endl;

		for (const auto& row : gameMap.checkpoint) {
			for (const auto& checkpoint : row) {
				std::cout << "Checkpoint visualX: " << checkpoint.visualX << ", visualY: " << checkpoint.visualY << std::endl;
			}
		}
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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	isDragging = true;
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
	if (isDragging)
	{
		Checkpoint* nearestCheckpoint = FindNearestCheckpoint(point);
		if (nearestCheckpoint != nullptr) {
			operators[0].position.x = nearestCheckpoint->visualX;
			operators[0].position.y = nearestCheckpoint->visualY;
		}
		isDragging = false;
	}
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
	if (isDragging)
	{
		Checkpoint* nearestCheckpoint = FindNearestCheckpoint(point);
		if (nearestCheckpoint != nullptr) {
			operators[0].position.x = nearestCheckpoint->visualX;
			operators[0].position.y = nearestCheckpoint->visualY;
		}
	}
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)    // 處理滑鼠的動作
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

Checkpoint* CGameStateRun::FindNearestCheckpoint(CPoint point)  // 找出最近的checkpoint	
{
	Checkpoint* NearestCheckpoint = nullptr;
	double minDistance = 1e308;

	for (auto& row : gameMap.checkpoint) {
		for (auto& checkpoint : row) {
			double distance = std::sqrt(std::pow(checkpoint.visualX - point.x, 2) + std::pow(checkpoint.visualY - point.y, 2));
			if (distance < minDistance) {
				minDistance = distance;
				NearestCheckpoint = &checkpoint;
			}
		}
	}

	return NearestCheckpoint;
}