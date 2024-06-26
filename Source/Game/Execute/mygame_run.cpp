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
#include "../Actors/Enemy/Giant_normal/Giant_normal.h"
#include "../Actors/Character/mygame_enemyManager.h"
#include "../Actors/Operator/Eyjafjalla/Eyjafjalla.h"
#include "../Actors/Operator/Reed/Reed.h"
#include"../Actors/Operator/Skadi/Skadi.h"
#include"../Actors/Operator/Saria/Saria.h"
#include "../Actors/Operator/Exusiai/Exusiai.h"
#include "../Actors/Operator/Bagpipe/Bagpipe.h"
#include "../Actors/Operator/Blaze/Blaze.h"
#include "../Actors/Operator/Dusk/Dusk.h"
#include "../Actors/Operator/Hongxue/Hongxue.h"
#include "../Actors/Operator/Ines/Ines.h"
#include "../Actors/Operator/Nian/Nian.h"
#include "../Actors/Operator/Nightingale/Nightingale.h"
#include "../mygame.h"
#include "../Map/mygame_mapManager.h"
#include "../Map/mygame_mapAndCheckpoint.h"
#include <vector>
#include <limits>
#include <iostream>
#include <chrono>
#include <Windows.h>
#include <sstream>
#include <algorithm>	
#include <iomanip>

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
const int costUpdateInterval = 1000;						// cost+1/1000ms，如果太慢可以調整
int enemyCount = 0;
int life = 3;
bool isGameover;

TextFormat CGameStateRun::costTextFormat(40, RGB(255, 255, 255), 300, "Segoe UI");
TextFormat CGameStateRun::operatorCostFormat(20, RGB(255, 255, 255), 500, "Segoe UI");
TextFormat CGameStateRun::lifeTextFormat(40, RGB(255, 255, 255), 500, "Segoe UI");
TextFormat CGameStateRun::remainTextFormat(50, RGB(255, 255, 255), 500, "Segoe UI");


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
	ShowInitProgress(0, "Initializing...");
	life = 3;
	cost = 30;
	operators.clear();
	isGameover = false;

	
	//以下為讀入幹員
	ShowInitProgress(5, "Loading operators...");
	operators.push_back(std::make_unique<Reed>());
	operators.push_back(std::make_unique<Skadi>());
	operators.push_back(std::make_unique<Saria>());

	ShowInitProgress(10, "Loading operators...");
	operators.push_back(std::make_unique<Exusiai>());
	operators.push_back(std::make_unique<Eyjafjalla>());
	operators.push_back(std::make_unique<Bagpipe>());

	ShowInitProgress(20, "Loading operators...");
	operators.push_back(std::make_unique<Blaze>());
	operators.push_back(std::make_unique<Dusk>());
	operators.push_back(std::make_unique<Hongxue>());

	ShowInitProgress(30, "Loading operators...");
	operators.push_back(std::make_unique<Ines>());
	operators.push_back(std::make_unique<Nian>());
	operators.push_back(std::make_unique<Nightingale>());

	SortOperator();

	//以下為讀地圖
	std::string logicMapPath;
	std::string visualMapPath;
	std::string enemyPath;

	ShowInitProgress(40, "Loading Maps...");
	if (selectedMapIndex == 1) {				//要-1
		logicMapPath = "resources/map/mapJSON/0-2.json";
		visualMapPath = "resources/map/mapJSON/0-2Visual.json";
		enemyPath = "resources/map/enemyJSON/0-2Enemy.JSON";
	}else if (selectedMapIndex == 2) {				
		logicMapPath = "resources/map/mapJSON/0-3.json";
		visualMapPath = "resources/map/mapJSON/0-3Visual.json";
		enemyPath = "resources/map/enemyJSON/0-3Enemy.JSON";
	}
	else {
		logicMapPath = "resources/map/mapJSON/0-1.json";
		visualMapPath = "resources/map/mapJSON/0-1Visual.json";
		enemyPath = "resources/map/enemyJSON/0-1Enemy.JSON";
	}

	background.LoadBitmapByString({ "resources/map/0-1.bmp", "resources/map/0-2.bmp", "resources/map/0-3.bmp" });			
	background.SetTopLeft(0, 0);
	background.SetFrameIndexOfBitmap(selectedMapIndex);


	ShowInitProgress(60, "Compare maps...");
	try {
		gameMapManager.loadLogicMapFromJson(logicMapPath);
		DBOUT("Success of logic map file open." << endl);

		gameMapManager.loadVisualMapFromJson(visualMapPath);
		DBOUT("Success of visual map file open." << endl);

		auto& gameMap = gameMapManager.getGameMap();

		for (auto& row : gameMap.checkpoint) {
			for (auto& checkpoint : row) {
				checkpoint.attackRangePoint.LoadBitmapByString({ "resources/mark/testMark.bmp" }, RGB(0, 0, 0));
			}
		}

		checkpointManager = std::make_unique<CheckpointManager>(gameMapManager.getGameMap());
		// DBOUT("OnInit - gameMap address: " << &gameMap << std::endl);	//確認地圖於記憶體位置，與FindNearestCheckpoint對應
	}
	catch (std::exception& e) {
		DBOUT("Error of file open." << e.what());
	}

	ShowInitProgress(80, "Loading Enimies...");
	//以下為讀enemy
	try {
		enemyManager.clearEnemies();
		enemyManager.loadEnemyFromJson(enemyPath);
		DBOUT("Success of enemy file open." << endl);

		auto& loadedEnemies = enemyManager.getEnemies();

		for (auto& enemy : loadedEnemies) {
			vector<int> temp = FindPixelFromLogic(enemy->trajectory[0][0], enemy->trajectory[0][1]);
			enemy->position.x = temp[0];
			enemy->position.y = temp[1];
			enemies.push_back(enemy);
		}
	}
	catch (std::exception& e) {
		DBOUT("Error of enemy file open." << e.what());
	}

	enemyCount = enemies.size();

	ShowInitProgress(100, "Mission start!");
	Sleep(1500);

	//重新計時
	CleanTime();
	isGamePaused = false;

	ost->Play(selectedMapIndex, true);
}

void CGameStateRun::OnMove()																	// 移動遊戲元素
{
	if (!enemies.empty()) {
		for (auto& enemy : enemies) {
			if (enemy->positionIndex + 1 < enemy->trajectory.size()) {
				vector<int> originalLogicPosition = enemy->trajectory[enemy->positionIndex];
				vector<int> nextLogicPosition = enemy->trajectory[enemy->positionIndex + 1];
				vector<int> originalVisualPosition = FindPixelFromLogic(originalLogicPosition[0], originalLogicPosition[1]);
				vector<int> nextVisualPosition = FindPixelFromLogic(nextLogicPosition[0], nextLogicPosition[1]);

				Checkpoint& currentCheckpoint = checkpointManager->getCheckpoint(originalLogicPosition[0], originalLogicPosition[1]);
				enemy->Move(originalVisualPosition, nextVisualPosition, *checkpointManager);

				if (currentCheckpoint.blockCount - currentCheckpoint.enemyCount <= 0) {				//若該checkpoint的blockCount - enemyCount <= 0，則敵人可以通過
					if (currentCheckpoint.blockCount == 0 && enemy->isBlocked == true) {			//若敵人被阻擋，且blockCount=0，則解除阻擋	
						checkpointManager->unregisterEnemyAtCheckpoint(originalLogicPosition[0], originalLogicPosition[1], enemy->blockCount);
						enemy->isBlocked = false;
					}
					else if (!enemy->isBlocked && !enemy->isDead) {									//若敵人未被阻擋，則改為移動
						enemy->ChangeEnemyState(EnemyState::MOVE);
					}
				}
				else {
					if (!enemy->isBlocked && !enemy->isDead) {										//若敵人未被阻擋且未死亡，則改為阻擋		
						checkpointManager->registerEnemyAtCheckpoint(originalLogicPosition[0], originalLogicPosition[1], enemy->blockCount);
						enemy->isBlocked = true;
						DBOUT("The CKPT (" << currentCheckpoint.logicX << "," << currentCheckpoint.logicY << ") has " << currentCheckpoint.enemyCount << " enemies. It's ID : " << enemy->ID << ". And it's in (" << enemy->logicX << ", " << enemy->logicY << "). Has block counts: " << currentCheckpoint.blockCount << endl);
					}
				}
			}
		}
		DecreaseLife();
		RemoveDeadEnemy();
	}
	else {
		isGameover = true;
		Gameover();
	}
}

void CGameStateRun::OnInit()                              // 遊戲的初值及圖形設定
{
	selOpIdx = -1;										  //Selected Operator Index
	isDragging = false;
	isConfirmingPlacement = false;

	for (int i = 0; i <= 2; i++) {
		std::string filePath = "resources/music/ost/0-" + std::to_string(i + 1) + ".wav";
		if (!ost->Load(i, &filePath[0])) {
			DBOUT("Fail to load OST :" << i + 1 << endl);
			ost->Close();
			return;
		}
		else {
			DBOUT("Success to load OST :" << i + 1 << endl);
		}
	}
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

	// 按下方向鍵來改變幹員的方向
	if (selOpIdx != -1 && isConfirmingPlacement) {
		switch (nChar) {
		case VK_UP:
			operators[selOpIdx]->orientation = Orientation::Up;
			operators[selOpIdx]->ChangeImages();
			operators[selOpIdx]->AdjustAttackRange();
			ShowAttackRange();
			break;

		case VK_DOWN:
			operators[selOpIdx]->orientation = Orientation::Down;
			operators[selOpIdx]->ChangeImages();
			operators[selOpIdx]->AdjustAttackRange();
			ShowAttackRange();
			break;

		case VK_LEFT:
			operators[selOpIdx]->orientation = Orientation::Left;
			operators[selOpIdx]->ChangeImages();
			operators[selOpIdx]->AdjustAttackRange();
			ShowAttackRange();
			break;

		case VK_RIGHT:
			operators[selOpIdx]->orientation = Orientation::Right;
			operators[selOpIdx]->ChangeImages();
			operators[selOpIdx]->AdjustAttackRange();
			ShowAttackRange();
			break;

		case VK_RETURN:											//確認放置
			isConfirmingPlacement = false;
			operators[selOpIdx]->isPlaced = true;
			operators[selOpIdx]->isAlive = true;	
			cost -= operators[selOpIdx]->cost;

			int logicX = operators[selOpIdx]->logicX;
			int logicY = operators[selOpIdx]->logicY;
			
			checkpointManager->registerOperatorAtCheckpoint(logicX, logicY, operators[selOpIdx]->blockCounts);
			selOpIdx = -1;
			break;
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_BACK) {
		if (selOpIdx >= 0 && !isDragging && !isConfirmingPlacement) {
			cost += operators[selOpIdx]->cost / 2;								//撤退返還一半的費用
			if(cost >= 99) cost = 99;
			
			int logicX = operators[selOpIdx]->logicX;
			int logicY = operators[selOpIdx]->logicY;

			operators[selOpIdx]->ChangeOperatorState(OperatorState::IDLE);
			operators[selOpIdx]->Retreat(*checkpointManager);
			selOpIdx = -1;
		}
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)					// 處理滑鼠的動作
{
	if (!isConfirmingPlacement) {
		for (size_t i = 0; i < operators.size(); ++i) {							//遍歷operator尋找click對應的operator
			if (operators[i]->CheckIfSelected(point)) {
				selOpIdx = i;

				if (cost >= operators[selOpIdx]->cost && operators[selOpIdx]->isPlaceable == true) {
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
	if (!op) return false;

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

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
	if (isDragging && selOpIdx != -1 && operators[selOpIdx]->isPlaced == false)
	{
		Checkpoint* nearestCheckpoint = FindNearestCheckpoint(point);
		if (nearestCheckpoint != nullptr) {
			if (!nearestCheckpoint -> occupied && CanPlaceOperator(operators[selOpIdx].get(), *nearestCheckpoint)) {
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
	else if (isDragging && selOpIdx != -1 && operators[selOpIdx]->isPlaced == true) {
		isDragging = false;
	}
	else if (isDragging) {
		isDragging = false;
		selOpIdx = -1;
	}
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
	if (isDragging && operators[selOpIdx]->isPlaced == false)
	{
		Checkpoint* nearestCheckpoint = FindNearestCheckpoint(point);
		if (nearestCheckpoint != nullptr) {
			operators[selOpIdx]->position.x = nearestCheckpoint->visualX - deviationX;
			operators[selOpIdx]->position.y = nearestCheckpoint->visualY - deviationY;
		}
	}
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if (selOpIdx != -1) {
		operators[selOpIdx]->Skill();
		DBOUT("It's time to execute " << operators[selOpIdx]->operatorName << "'s skill!" << endl);
	}
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
}

static std::string formatFloat(float value) {
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(1) << value;
	return stream.str();
}

void CGameStateRun::OnShow() {                                  // 顯示遊戲畫面   
	background.ShowBitmap();
	textRenderer.ShowText("Cost: " + std::to_string(cost), 1100, 528, costTextFormat);

	int locateFirst = 1150;
	int locateSecond = 1150;

	for (auto& op : operators) {
		op->headImage.SetTopLeft(locateFirst, 605);									//顯示幹員頭像
		if (!op->isAlive) {
			op->headImage.ShowBitmap();
		}
		else {
			op->headImage.UnshowBitmap();
		}
		locateFirst -= 100;

		if (op->isAlive || isConfirmingPlacement || isDragging) {					//顯示幹員
			op->image.SetTopLeft(op->position.x, op->position.y);
			op->image.ShowBitmap();
			if (op->hp < op->maxHp) {
				int healthPercent = static_cast<int>(100.0 * op->hp / op->maxHp);
				ShowHealthBar(healthPercent, op->position.x + 100, op->position.y + 230, false);
			}
		}

		if (!op->isAlive && op->DeployTimer != 0) {
			float remainingTime = op->DeployTime - op->DeployTimer;
			std::string timeText = formatFloat(remainingTime);
			textRenderer.ShowText(timeText, locateSecond + 25, 630, remainTextFormat);
		}
		else if (!op->isAlive && op->DeployTimer == 0) {
			textRenderer.ShowText(std::to_string(op->cost), locateSecond + 5, 620, operatorCostFormat);
		}
		locateSecond -= 100;
	}

	for (auto& enemy : enemies) {
		enemy->image.SetTopLeft(enemy->position.x, enemy->position.y);
		if (enemy->isDead == false && enemy->isActive == true) {
			enemy->image.ShowBitmap();
			if (enemy->hp != enemy->maxHp) {
				int healthPercent = static_cast<int>(100.0 * enemy->hp / enemy->maxHp);
				ShowHealthBar(healthPercent, enemy->position.x + 100, enemy->position.y + 230, true);
			}
		}
	}

	textRenderer.ShowText(std::to_string(enemyCount - enemies.size()) + "/" + std::to_string(enemyCount) + "                " + std::to_string(life) + "/ 3", 480, 0, lifeTextFormat);

	if (isConfirmingPlacement && selOpIdx != -1) {
		ShowAttackRange();
	}

	//時間軸
	UpdateGameTime();
}


void CGameStateRun::UpdateGameTime() {
	if (!isGamePaused) {
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<float, std::milli> deltaTime = now - lastUpdateTime;
		gameTime += deltaTime;										// 只有在未暫停時累積遊戲時間
		lastUpdateTime = now;										// 更新 lastUpdateTime 為目前時間

		auto LastCostUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCostUpdateTime).count();
		if (LastCostUpdate >= costUpdateInterval && cost < 99) {				
			cost += 1;
			lastCostUpdateTime = now;
		}

		objectInteraction.OperatorAttackPerform(operators, enemies, deltaTime.count() / 1000.0f, *checkpointManager);
		objectInteraction.OperatorHealPerform(operators, operators, deltaTime.count() / 1000.0f, *checkpointManager);

		for (auto& enemy : enemies) {
			if (!enemy->isActive && gameTime.count() >= enemy->entryTime * 1000) {  
				enemy->isActive = true;
				enemy->EnterGame();												
			}
		}

		objectInteraction.EnemyAttackPerform(enemies, operators, deltaTime.count() / 1000.0f, *checkpointManager);

		for (auto& op : operators) {
			if (!op->isPlaceable) {
				op->DeployCD(deltaTime.count() / 1000.0f);
			}
		}
	}
}

// 暫停遊戲，停止遊戲時間的累積
void CGameStateRun::PauseGame() {
	if (!isGamePaused) {
		UpdateGameTime();												// 確保在暫停前遊戲時間是最新的
		isGamePaused = true;											// 設定遊戲為暫停狀態
	}
}

// 從暫停狀態恢復遊戲，允許遊戲時間再次累積
void CGameStateRun::ResumeGame() {
	if (isGamePaused) {
		isGamePaused = false;											// 遊戲不再是暫停狀態
		lastUpdateTime = std::chrono::steady_clock::now();				// 重置 lastUpdateTime 為現在
	}
}

void CGameStateRun::CleanTime() {
	mainTime = std::chrono::steady_clock::now();						// 重置 mainTime 為現在
	gameTime = std::chrono::steady_clock::duration::zero();				// 重置 gameTime 為 0
	lastUpdateTime = std::chrono::steady_clock::now();					// 重置 lastUpdateTime 為現在
}

Checkpoint* CGameStateRun::FindNearestCheckpoint(CPoint point)			// 找出最近的checkpoint	
{
	Checkpoint* NearestCheckpoint = nullptr;
	double minDistance = (std::numeric_limits<double>::max)();
	auto& gameMap = gameMapManager.getGameMap();
	nearLogicX = -1;
	nearLogicY = -1;

	//DBOUT("FindNearestCheckpoint - gameMap address: " << &gameMap << std::endl);		//確認地圖於記憶體位置，與OnInit對應

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


vector<int> CGameStateRun::FindPixelFromLogic(int logicX, int logicY)		// 找出這個logic的pixel
{
	double minDistance = (std::numeric_limits<double>::max)();
	auto& gameMap = gameMapManager.getGameMap();
	vector<int> result;

	result.push_back(gameMap.checkpoint[logicY][logicX].visualX - deviationX);
	result.push_back(gameMap.checkpoint[logicY][logicX].visualY - deviationY);
	return result;
}

void CGameStateRun::ShowAttackRange() {
	auto& selectedOperator = operators[selOpIdx];
	auto& gameMap = gameMapManager.getGameMap();

	for (const auto& rangePoint : selectedOperator->attackRange) {
		if (rangePoint.x >= 0 && rangePoint.x < gameMap.width && rangePoint.y >= 0 && rangePoint.y < gameMap.height) {
			auto& checkpoint = gameMap.checkpoint[rangePoint.y][rangePoint.x];
			checkpoint.attackRangePoint.SetTopLeft(checkpoint.visualX -20, checkpoint.visualY -20);
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

void CGameStateRun::DecreaseLife() {				//進藍門-1HP
	auto blueDoorEnemyIt = std::find_if(enemies.begin(), enemies.end(), [](const std::shared_ptr<Enemy>& enemy) {
		return enemy->enemyState == EnemyState::BLUE_DOOR;
		});

	if (blueDoorEnemyIt != enemies.end()) {

		(*blueDoorEnemyIt)->enemyState = EnemyState::DEAD;
		--life;
	}

	if (life <= 0) {
		isGameover = true;
		Gameover();
	}
}


void CGameStateRun::RemoveDeadEnemy()			//移除死亡的敵人
{
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const std::shared_ptr<Enemy>& enemy) {
		return enemy->enemyState == EnemyState::DEAD;
		}), enemies.end());
}

void CGameStateRun::SortOperator()				//排序幹員
{
	std::sort(operators.begin(), operators.end(), [](const std::unique_ptr<Operator>& a, const std::unique_ptr<Operator>& b)
		{
			return a->cost > b->cost;
		});
}

void CGameStateRun::ShowHealthBar(int healthPercent, int posX, int posY, bool isEnemy)
{
	const int bar_width = 60;					// 調整血條寬度
	const int bar_height = 8;					// 調整血條高度
	const int x1 = posX;						// 血條的水平位置
	const int x2 = x1 + bar_width;
	const int y1 = posY - bar_height - 10;		
	const int y2 = y1 + bar_height;
	const int pen_width = bar_height / 8;
	const int health_x1 = x1 + pen_width;
	const int health_x2 = health_x1 + healthPercent * (bar_width - 2 * pen_width) / 100;
	const int health_x2_end = x2 - pen_width;
	const int health_y1 = y1 + pen_width;
	const int health_y2 = y2 - pen_width;

	CDC* pDC = CDDraw::GetBackCDC();			// 取得後端畫布的CDC 

	CBrush b1(RGB(255, 255, 255));				// 白色的血條底色
	pDC->SelectObject(&b1);
	pDC->Rectangle(health_x1, health_y1, health_x2_end, health_y2);

	CBrush b2(isEnemy ? RGB(255, 0, 0) : RGB(135, 206, 255));	
	pDC->SelectObject(&b2);
	pDC->Rectangle(health_x1, health_y1, health_x2, health_y2);

	CDDraw::ReleaseBackCDC();					// 釋放畫布的CDC
}


void CGameStateRun::Gameover()						//遊戲結束
{
	ost->Pause();
	Sleep(2000);

	if (!enemies.empty()) {
		levelpass = 0;
	}else {
		levelpass = 1;
	}
	
	GotoGameState(GAME_STATE_OVER);
	enemies.clear();
	background.UnshowBitmap();
	isGameover = false;
}
