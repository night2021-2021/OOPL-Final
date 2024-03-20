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
#include "../Map/mygame_mapAndCheckpoint.h"
#include <vector>
#include <limits>
#include <iostream>
#include <Windows.h>
#include <sstream>

#define NOMINMAX
#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                  \
   OutputDebugString( os_.str().c_str() );  \
}	

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////
const int deviationX = 50;
const int deviationY = 50;
bool isDragging = false;
GameMapManager gameMapManager;


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

		
	std::string logicMapPath = "resources/map/mapJSON/0_1.json";	
	std::string visualMapPath = "resources/map/mapJSON/0-1_visual.json";

	try{
		gameMapManager.loadLogicMapFromJson(logicMapPath);
		DBOUT("Success of logic map file open." << endl);

		gameMapManager.loadVisualMapFromJson(visualMapPath);
		DBOUT("Success of visual map file open." << endl);

		auto& gameMap = gameMapManager.getGameMap();

		for (const auto& row : gameMap.checkpoint) {
			for (const auto& checkpoint : row) {
				DBOUT("Checkpoint In main program: visualX: " << checkpoint.visualX << ", visualY: " << checkpoint.visualY << endl);
			}
		}

		DBOUT("OnInit - gameMap address: " << &gameMap << std::endl);	//確認地圖於記憶體位置，與FindNearestCheckpoint對應
	}
	catch (std::exception& e) {
		DBOUT("Error of file open." << e.what());
	}

	game_framework::Reed reed;
	reed.image.LoadBitmapByString({ "resources/characters/operators/Reed/Reed.bmp" }, RGB(255, 255, 255));
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
			operators[0].position.x = nearestCheckpoint->visualX -deviationX;
			operators[0].position.y = nearestCheckpoint->visualY -deviationY;
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
			operators[0].position.x = nearestCheckpoint->visualX -deviationX;
			operators[0].position.y = nearestCheckpoint->visualY -deviationY;
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

Checkpoint* CGameStateRun::FindNearestCheckpoint(CPoint point)							// 找出最近的checkpoint	
{
	Checkpoint* NearestCheckpoint = nullptr;
	double minDistance = (std::numeric_limits<double>::max)();
	auto& gameMap = gameMapManager.getGameMap();

	//DBOUT("FindNearestCheckpoint - gameMap address: " << &gameMap << std::endl);	//確認地圖於記憶體位置，與OnInit對應

	for (auto& row : gameMap.checkpoint) {
		for (auto& checkpoint : row) {
			double distance = std::sqrt(std::pow(checkpoint.visualX - point.x, 2) + std::pow(checkpoint.visualY - point.y, 2));
			if (distance < minDistance) {
				minDistance = distance;
				NearestCheckpoint = &checkpoint;
			}
		}
	}

	DBOUT("The name of this checkpoint:" << NearestCheckpoint->CKPTName << endl);
	DBOUT("The type of this checkpoint:" << NearestCheckpoint->CKPTType << endl);

	return NearestCheckpoint;
}