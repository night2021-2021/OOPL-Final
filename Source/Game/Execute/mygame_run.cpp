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
// ?o??class???C?????C????????A?D?n???C???{?????b?o??
/////////////////////////////////////////////////////////////////////////////
const int deviationX = 120;
const int deviationY = 180;

EnemyManager enemyManager;
GameMapManager gameMapManager;

CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
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

void CGameStateRun::OnMove()                            // ????C??????
{

}

void CGameStateRun::OnInit()                              // ?C???????�d?�^]?w
{
	cost = 30;
	selOpIdx = -1;
	isDragging = false;
	isConfirmingPlacement = false;
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

		for (auto& row : gameMap.checkpoint) {
			for (auto& checkpoint : row) {
				checkpoint.attackRangePoint.LoadBitmapByString({ "resources/mark/testmark.bmp" }, RGB(0, 0, 0));
				DBOUT("Checkpoint In main program: visualX: " << checkpoint.visualX << ", visualY: " << checkpoint.visualY << endl);
			}
		}
		//DBOUT("OnInit - gameMap address: " << &gameMap << std::endl);	//?T?{?a???O?????m?A?PFindNearestCheckpoint????
	}
	catch (std::exception& e) {
		DBOUT("Error of file open." << e.what());
	}

	//game_framework::Reed reed;
	//game_framework::Skadi skadi;
	operators.push_back(std::make_unique<Reed>());
	operators.push_back(std::make_unique<Skadi>());

	std::sort(operators.begin(), operators.end(), [](const std::unique_ptr<Operator>& a, const std::unique_ptr<Operator>& b)
	{
		return a->cost > b->cost;															
	});

	std::string enemyPath = "resources/map/enemyJSON/0-1_Enemy.JSON";

	try {
		enemyManager.loadEnemyFromJson(enemyPath);
		DBOUT("Success of enemy file open." << endl);
	}
	catch (std::exception& e) {
		DBOUT("Error of enemy file open." << e.what());
	}

	//?H?U????J??H???{???X
	auto& loadedEnemies = enemyManager.getEnemies();
	for (auto& enemy : loadedEnemies) {
		enemies.push_back(enemy);
		DBOUT("Displaying enemies count in OnInit: " << enemies.size() << endl);
	}

	//?H?U???p???
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

	// ???U??V??????F??????V
	if (selOpIdx != -1 && isConfirmingPlacement) {
		switch (nChar) {
		case VK_UP:
			operators[selOpIdx]->orientation = Orientation::Up;
			operators[selOpIdx]->LoadImagesForOrientation();
			operators[selOpIdx]->AdjustAttackRange();
			ShowAttackRange();
			break;
		case VK_DOWN:
			operators[selOpIdx]->orientation = Orientation::Down;
			operators[selOpIdx]->LoadImagesForOrientation();
			operators[selOpIdx]->AdjustAttackRange();
			ShowAttackRange();
			break;
		case VK_LEFT:
			operators[selOpIdx]->orientation = Orientation::Left;
			operators[selOpIdx]->LoadImagesForOrientation();
			operators[selOpIdx]->AdjustAttackRange();
			ShowAttackRange();
			break;
		case VK_RIGHT:
			operators[selOpIdx]->orientation = Orientation::Right;
			operators[selOpIdx]->LoadImagesForOrientation();
			operators[selOpIdx]->AdjustAttackRange();
			ShowAttackRange();
			break;
		case VK_RETURN:
			isConfirmingPlacement = false;
			operators[selOpIdx]->isPlacing = true;
			cost -= operators[selOpIdx]->cost;

			DBOUT("Attack Range for Operator " << selOpIdx << ": ");
			for (const auto& point : operators[selOpIdx]->attackRange) {
				DBOUT("(" << point.x << ", " << point.y << ") ");
			}
			DBOUT(endl);

			selOpIdx = -1;
			break;
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_BACK) {
		if (selOpIdx >= 0) {
			cost += operators[selOpIdx]->cost / 2;		//?M?h????@?b???O??
			operators[selOpIdx]->Retreat();
		}
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)		// ?B?z???????@
{
	if (!isConfirmingPlacement) {
		for (size_t i = 0; i < operators.size(); ++i) {						//?M??operator?M??click??????operator
			if (operators[i]->CheckIfSelected(point)) {
				selOpIdx = i;

				if (cost >= operators[selOpIdx]->cost) {
					DBOUT("The cost of operator is : " << operators[i]->cost << endl);
					isDragging = true;
				}
				else {
					DBOUT("The cost is not enough" << endl);
				}
				break;
			}
		}
	}
	else {
		operators[selOpIdx]->position.x = 1080;
		operators[selOpIdx]->position.y = 720;
		DBOUT("Placement canceled." << endl);
		selOpIdx = -1;
		isConfirmingPlacement = false;
	}
}

static bool CanPlaceOperator(const Operator* op, const Checkpoint& cp) {
	if(!op) return false;
	
	switch (op->operatorClass) {
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

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)    // ?B?z???????@
{
	if (isDragging && selOpIdx != -1 && operators[selOpIdx]->isPlacing == false)
	{
		Checkpoint* nearestCheckpoint = FindNearestCheckpoint(point);
		if (nearestCheckpoint != nullptr) {
			if (CanPlaceOperator(operators[selOpIdx].get(), *nearestCheckpoint)) {
				operators[selOpIdx]->position.x = nearestCheckpoint->visualX - deviationX;
				operators[selOpIdx]->position.y = nearestCheckpoint->visualY - deviationY;
				operators[selOpIdx]->logicX = nearLogicX;
				operators[selOpIdx]->logicY = nearLogicY;

				operators[selOpIdx]->AdjustAttackRange();
				isConfirmingPlacement = true;
				ShowAttackRange();
			}
			else {
				operators[selOpIdx]->position.x = 1080;
				operators[selOpIdx]->position.y = 720;
				DBOUT("The operator can't be placed here" << endl);
			}
		}
		isDragging = false;
	}
	else if (isDragging && selOpIdx != -1 && operators[selOpIdx]->isPlacing == true) {
		isDragging = false;
	}
	else if(isDragging){
		isDragging = false;
		selOpIdx = -1;
	}
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)    // ?B?z???????@
{
	if (isDragging && operators[selOpIdx]->isPlacing == false)
	{
		Checkpoint* nearestCheckpoint = FindNearestCheckpoint(point);
		if (nearestCheckpoint != nullptr) {
			operators[selOpIdx]->position.x = nearestCheckpoint->visualX - deviationX;
			operators[selOpIdx]->position.y = nearestCheckpoint->visualY - deviationY;
		}
	}
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // ?B?z???????@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)    // ?B?z???????@
{
}

void CGameStateRun::OnShow()									// ???C???e??	
{
	background.ShowBitmap();
	textShow();
	int locateFirst = 1150;

	for (auto& op : operators) {
		op->headImage.SetTopLeft(locateFirst, 605);
		op->headImage.ShowBitmap();
		locateFirst -= 100;
	}
	for (auto& op : operators) {
		op->image.SetTopLeft(op->position.x, op->position.y);
		op->image.ShowBitmap();
	}

	for (auto& enemy : enemies) {
		enemy->image.SetTopLeft(enemy->position.x, enemy->position.y);
		enemy->image.ShowBitmap();
	}

	if (isConfirmingPlacement && selOpIdx != -1) {
		ShowAttackRange();
	}

	//???? ??H?????? ???\
	if (!enemies.empty()) {
		auto& firstEnemy = enemies[0]; 
		firstEnemy->position.x -= 1;
	}

	//????b
	UpdateGameTime();
}


void CGameStateRun::UpdateGameTime() {
	if (!isGamePaused) {
		auto now = std::chrono::steady_clock::now();
		gameTime += now - lastUpdateTime;								// ?u???b????????n?C?????
		lastUpdateTime = now;											// ??s lastUpdateTime ????e???

		auto LastCostUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCostUpdateTime).count();
		if (LastCostUpdate >= 500 && cost < 99) {
			cost += 1;
			lastCostUpdateTime = now;
		}
	}
}

// ????C???A????C?????????n
void CGameStateRun::PauseGame() {
	if (!isGamePaused) {
		UpdateGameTime();												// ?T?O?b????e?C??????O??s??
		isGamePaused = true;											// ?]?w?C??????????A
	}
}

// ?q??????A??_?C???A???\?C??????A????n
void CGameStateRun::ResumeGame() {
	if (isGamePaused) {
		isGamePaused = false;											// ?C?????A?O??????A
		lastUpdateTime = std::chrono::steady_clock::now();				// ???m lastUpdateTime ???{?b
	}
}

void CGameStateRun::textShow() {
	CDC* pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 40, "?L?n??????", RGB(255, 255, 255), 800);
	std::string costStr = "Cost: " + std::to_string(cost);
	CTextDraw::Print(pDC, 1100, 528, costStr.c_str());
	CDDraw::ReleaseBackCDC();
}

Checkpoint* CGameStateRun::FindNearestCheckpoint(CPoint point)		// ??X???checkpoint	
{
	Checkpoint* NearestCheckpoint = nullptr;
	double minDistance = (std::numeric_limits<double>::max)();
	auto& gameMap = gameMapManager.getGameMap();
	nearLogicX = -1;
	nearLogicY = -1;

	//DBOUT("FindNearestCheckpoint - gameMap address: " << &gameMap << std::endl);	//?T?{?a???O?????m?A?POnInit????

	for (int y = 0; y < gameMap.height; ++y) {
		for (int x = 0; x < gameMap.width; ++x) {
			Checkpoint& checkpoint = gameMap.checkpoint[y][x];
			double distance = std::sqrt(std::pow(checkpoint.visualX - point.x, 2) + std::pow(checkpoint.visualY - point.y, 2));
			if (distance < minDistance) {
				minDistance = distance;
				NearestCheckpoint = &checkpoint;
				nearLogicX = x; 
				nearLogicY = y;
			}
		}
	}
	return NearestCheckpoint;
}

void CGameStateRun::ShowAttackRange() {
	auto& selectedOperator = operators[selOpIdx];
	auto& gameMap = gameMapManager.getGameMap();

	for (const auto& rangePoint : selectedOperator->attackRange) {
		if (rangePoint.x >= 0 && rangePoint.x < gameMap.width && rangePoint.y >= 0 && rangePoint.y < gameMap.height) {
			auto& checkpoint = gameMap.checkpoint[rangePoint.y][rangePoint.x];
			checkpoint.attackRangePoint.SetTopLeft(checkpoint.visualX, checkpoint.visualY);
			checkpoint.attackRangePoint.ShowBitmap();
		}
	}
}

void CGameStateRun::UnshowAttackRange() {
	auto& gameMap = gameMapManager.getGameMap();
	for (auto& row : gameMap.checkpoint) {
		for (auto& checkpoint : row) {
			checkpoint.attackRangePoint.UnshowBitmap();
		}
	}
}