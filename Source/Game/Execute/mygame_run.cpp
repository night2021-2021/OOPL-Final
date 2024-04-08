#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../Actors/Character/mygame_operator.h"
#include "../Actors/Character/mygame_enemy.h"
#include "../Actors/Enemy/Bug_normal/Bug_normal.h"
#include "../Actors/Character/mygame_enemyManager.h"
#include "../Actors/Operator/Reed/Reed.h"
#include"../Actors/Operator/Skadi/Skadi.h"
#include "../mygame.h"
#include "../Map/mygame_mapManager.h"
#include "../Map/mygame_mapAndCheckpoint.h"
#include <vector>
#include <limits>
#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <sstream>
#include <algorithm>

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
const int deviationX = 120;
const int deviationY = 180;

bool isDragging = false;
int selOpIdx = -1;

EnemyManager enemyManager;
GameMapManager gameMapManager;

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
	mainTime = std::chrono::steady_clock::now();
	lastUpdateTime = mainTime;
	gameTime = std::chrono::steady_clock::duration::zero();
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
	cost = 30;

	background.LoadBitmapByString({ "resources/map/0_1.bmp" });
	background.SetTopLeft(0, 0);


	std::string logicMapPath = "resources/map/mapJSON/0_1.json";
	std::string visualMapPath = "resources/map/mapJSON/0-1_visual.json";

	try {
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
	game_framework::Skadi skadi;
	operators.push_back(reed);
	operators.push_back(skadi);

	std::sort(operators.begin(), operators.end(), [](const Operator& a, const Operator& b)
	{
		return a.cost > b.cost;						// 雖然是降序排列，但我是從最右邊開始往左，所以看起來像升序											
	});
	
	std::string enemyPath = "resources/map/enemyJSON/0-1_Enemy.JSON";
	
	try {
		enemyManager.loadEnemyFromJson(enemyPath);
		DBOUT("Success of enemy file open." << endl);
	}
	catch (std::exception& e) {
		DBOUT("Error of enemy file open." << e.what());
	}

	auto& loadedEnemies = enemyManager.getEnemies();
	for (auto& enemy : loadedEnemies) {
		enemies.push_back(enemy);
		DBOUT("Displaying enemies count in OnInit: " << enemies.size() << endl);
	}

	mainTime = std::chrono::steady_clock::now();
	isGamePaused = false;
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_SPACE) {

		if (isGamePaused) {
			ResumeGame();
		}
		else {
			PauseGame();
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_BACK) {
		if (selOpIdx >= 0) {
			operators[selOpIdx].isPlacing = false;
			operators[selOpIdx].position.x = 1080;
			operators[selOpIdx].position.y = 720;
		}
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  
{
	for (size_t i = 0; i < operators.size(); ++i) {						
		if (operators[i].CheckIfSelected(point)) {	
			selOpIdx = i; 

			if (cost >= operators[selOpIdx].cost) {
					DBOUT("The cost of operator is : " << operators[i].cost << endl);
					isDragging = true;
			}else {
				DBOUT("The cost is not enough" << endl);
			}
			break; 
		}
	}
}

static bool CanPlaceOperator(const Operator& op, const Checkpoint& cp) {
	switch (op.operatorClass) {
	case OperatorClass::Caster:
	case OperatorClass::Medic:
	case OperatorClass::Sniper:
	case OperatorClass::Supporter:
		return cp.CKPTType == "platform";
	case OperatorClass::Vanguard:
	case OperatorClass::Defender:
	case OperatorClass::Guard:
		return cp.CKPTType == "path";
	default:
		return false;
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
	if (isDragging && selOpIdx != -1 && operators[selOpIdx].isPlacing == false)
	{
		Checkpoint* nearestCheckpoint = FindNearestCheckpoint(point);
		if (nearestCheckpoint != nullptr) {
			if (CanPlaceOperator(operators[selOpIdx], *nearestCheckpoint)) {
				operators[selOpIdx].position.x = nearestCheckpoint->visualX - deviationX;
				operators[selOpIdx].position.y = nearestCheckpoint->visualY - deviationY;
				operators[selOpIdx].isPlacing = true;
				cost -= operators[selOpIdx].cost;
			}
			else {
				operators[selOpIdx].position.x = 1080;
				operators[selOpIdx].position.y = 720;
				DBOUT("The operator can't be placed here" << endl);
			}
		}	
		isDragging = false;
		selOpIdx= -1;
	}
	else if (isDragging && selOpIdx != -1 && operators[selOpIdx].isPlacing == true) {
		isDragging = false;
	}
	else if(isDragging){
		isDragging = false;
		selOpIdx = -1;
	}
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
	if (isDragging && operators[selOpIdx].isPlacing == false)
	{
		Checkpoint* nearestCheckpoint = FindNearestCheckpoint(point);
		if (nearestCheckpoint != nullptr) {
			operators[selOpIdx].position.x = nearestCheckpoint->visualX -deviationX;
			operators[selOpIdx].position.y = nearestCheckpoint->visualY -deviationY;
		}
	}
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()									// 顯示遊戲畫面	
{
	background.ShowBitmap();
	textShow();
	int locateFirst = 1150;

	for (auto& op : operators) {
		op.headImage.SetTopLeft(locateFirst, 605);
		op.headImage.ShowBitmap();
		locateFirst -= 100;
	}
	for (auto& op : operators) {
		op.image.SetTopLeft(op.position.x, op.position.y);
		op.image.ShowBitmap();
	}

	for (auto& enemy : enemies) {
		enemy->image.SetTopLeft(enemy->position.x, enemy->position.y);
		enemy->image.ShowBitmap();
	}

	//測試 敵人的移動 成功
	if (!enemies.empty()) {
		auto& firstEnemy = enemies[0]; // 獲取第一位敵人的引用
		firstEnemy->position.x -= 1;
	}

	UpdateGameTime();
}


void CGameStateRun::UpdateGameTime() {
	if (!isGamePaused) {
		auto now = std::chrono::steady_clock::now();
		gameTime += now - lastUpdateTime;								
		lastUpdateTime = now;											

		auto LastCostUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCostUpdateTime).count();
		if (LastCostUpdate >= 500 && cost < 99) {
			cost += 1; 
			lastCostUpdateTime = now; 
		}
	}
}


void CGameStateRun::PauseGame() {
	if (!isGamePaused) {
		UpdateGameTime();												
		isGamePaused = true;											
	}
}


void CGameStateRun::ResumeGame() {
	if (isGamePaused) {
		isGamePaused = false;											
		lastUpdateTime = std::chrono::steady_clock::now();				
	}
}

void CGameStateRun::textShow(){
	CDC* pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 40, "?L?n??????", RGB(255, 255, 255), 800);
	std::string costStr = "Cost: " + std::to_string(cost);
	CTextDraw::Print(pDC, 1100, 528, costStr.c_str());
	CDDraw::ReleaseBackCDC();
}

Checkpoint* CGameStateRun::FindNearestCheckpoint(CPoint point)		// 找出最近的checkpoint	
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
	return NearestCheckpoint;
}
