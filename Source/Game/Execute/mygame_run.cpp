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
#include"../Actors/Operator/Saria/Saria.h"
#include "../Actors/Operator/Exusiai/Exusiai.h"
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
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////
const int deviationX = 120;
const int deviationY = 180;


EnemyManager enemyManager;
GameMapManager gameMapManager;


CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
{
	mainTime = std::chrono::steady_clock::now();
	lastUpdateTime = mainTime;
	gameTime = std::chrono::steady_clock::duration::zero();		//�w�p�R��
}

CGameStateRun::~CGameStateRun()
{

}

void CGameStateRun::OnBeginState()
{
	//�H�U���p�ɾ�
	mainTime = std::chrono::steady_clock::now();					
	isGamePaused = false;
}

void CGameStateRun::OnMove()                            // ���ʹC������
{
	if (!enemies.empty()) {
		for (auto& enemy : enemies)
		{
			vector<int> originalLogicPosition, originalVisualPosition, nextVisualPosition;  // pixel

			if (enemy->positionIndex + 1 < enemy->trajectory.size()) {
				originalLogicPosition = (enemy->trajectory[enemy->positionIndex]);
				originalVisualPosition = FindPixelFromLogic(enemy->trajectory[enemy->positionIndex][0], enemy->trajectory[enemy->positionIndex][1]);
				nextVisualPosition = FindPixelFromLogic(enemy->trajectory[enemy->positionIndex + 1][0], enemy->trajectory[enemy->positionIndex + 1][1]);

				Checkpoint& currentCheckpoint = checkpointManager->getCheckpoint(originalLogicPosition[0], originalLogicPosition[1]);
				enemy->Move(originalVisualPosition, nextVisualPosition, *checkpointManager);

				if (currentCheckpoint.blockCount - currentCheckpoint.enemyCount <= 0) {					//�Y��checkpoint��blockCount - enemyCount <= 0�A�h�ĤH�i�H�q�L
					if (currentCheckpoint.blockCount == 0 && enemy->isBlocked == true) {				//�Y�ĤH�Q���סA�BblockCount�k�s�A�h�Ѱ�����	
						checkpointManager->unregisterEnemyAtCheckpoint(originalLogicPosition[0], originalLogicPosition[1], enemy->blockCount);
						enemy->isBlocked = false;
					}
					else if (enemy->isBlocked == false) {												//�Y�ĤH���Q���סA�h����
						enemy->logicX = enemy->trajectory[enemy->positionIndex][0];
						enemy->logicY = enemy->trajectory[enemy->positionIndex][1];
						enemy->ChangeEnemyState(EnemyState::MOVE);
					}
				}
				else {
					if (!enemy->isBlocked && !enemy->isDead) {											//�Y�ĤH���Q���סA�B�����`�A�h���׼ĤH
						checkpointManager->registerEnemyAtCheckpoint(originalLogicPosition[0], originalLogicPosition[1], enemy->blockCount);
						enemy->isBlocked = true;
						DBOUT("The CKPT (" << currentCheckpoint.logicX << "," << currentCheckpoint.logicY << ") has " << currentCheckpoint.enemyCount << " enemies. It's ID : " << enemy->ID << ". And it's in (" << enemy->logicX << ", " << enemy->logicY << "). Has block counts: "<< currentCheckpoint.blockCount << endl);
					}
				}
			}
		}
		RemoveDeadEnemy();
	}
}

void CGameStateRun::OnInit()                              // �C������Ȥιϧγ]�w
{
	cost = 30;
	selOpIdx = -1;										  //Selected Operator Index
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
				checkpoint.attackRangePoint.LoadBitmapByString({ "resources/mark/testMark.bmp" }, RGB(0, 0, 0));

			}
		}

		checkpointManager = std::make_unique<CheckpointManager>(gameMapManager.getGameMap());
		// DBOUT("OnInit - gameMap address: " << &gameMap << std::endl);	//�T�{�a�ϩ�O�����m�A�PFindNearestCheckpoint����
	}
	catch (std::exception& e) {
		DBOUT("Error of file open." << e.what());
	}

	operators.push_back(std::make_unique<Reed>());
	operators.push_back(std::make_unique<Skadi>());
	operators.push_back(std::make_unique<Saria>());
	operators.push_back(std::make_unique<Exusiai>());

	SortOperator();

	std::string enemyPath = "resources/map/enemyJSON/0-1Enemy.JSON";

	try {
		enemyManager.loadEnemyFromJson(enemyPath);
		DBOUT("Success of enemy file open." << endl);
		//�H�U��Ū�J�ĤH���{���X
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

	// ���U��V��ӧ��ܷF������V
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

		case VK_RETURN:											//�T�{��m
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
		if (selOpIdx >= 0) {
			cost += operators[selOpIdx]->cost / 2;								//�M�h���٤@�b���O��
			if(cost >= 99) cost = 99;
			
			int logicX = operators[selOpIdx]->logicX;
			int logicY = operators[selOpIdx]->logicY;

			operators[selOpIdx]->ChangeOperatorState(OperatorState::IDLE);
			operators[selOpIdx]->Retreat(*checkpointManager);
			checkpointManager->unregisterOperatorAtCheckpoint(logicX, logicY, operators[selOpIdx]->blockCounts);

			selOpIdx = -1;
		}
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)					// �B�z�ƹ����ʧ@
{
	if (!isConfirmingPlacement) {
		for (size_t i = 0; i < operators.size(); ++i) {							//�M��operator�M��click������operator
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

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)    // �B�z�ƹ����ʧ@
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

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)    // �B�z�ƹ����ʧ@
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

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)    // �B�z�ƹ����ʧ@
{
}

static std::string formatFloat(float value) {
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(1) << value;
	return stream.str();
}

void CGameStateRun::OnShow()								 // ��ܹC���e��	
{
	background.ShowBitmap();
	textRenderer.ShowText("Cost: " + std::to_string(cost), 1100, 528);

	int locateFirst = 1150;
	int locateSecond = 1150;

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
		if(enemy->isDead == false && enemy->isActive == true){
			enemy->image.ShowBitmap();
		}
	}

	if (isConfirmingPlacement && selOpIdx != -1) {
		ShowAttackRange();
	}

	for (auto& op : operators) {
		if (!op->isAlive && op->DeployTimer != 0) {
			float remainingTime = op->DeployTime - op->DeployTimer;
			std::string timeText = formatFloat(remainingTime);
			textRenderer.ShowText(timeText, locateSecond, 605);
		}
		else if (!op->isAlive && op->DeployTimer == 0) {
			textRenderer.ShowText(" ", locateSecond, 605);
		}
		locateSecond -= 100;
	}

	//�ɶ��b
	UpdateGameTime();
}

void CGameStateRun::UpdateGameTime() {
	if (!isGamePaused) {
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<float, std::milli> deltaTime = now - lastUpdateTime;
		gameTime += deltaTime;							// �u���b���Ȱ��ɲֿn�C���ɶ�
		lastUpdateTime = now;							// ��s lastUpdateTime ���ثe�ɶ�

		auto LastCostUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCostUpdateTime).count();
		if (LastCostUpdate >= 500 && cost < 99) {
			cost += 1;
			lastCostUpdateTime = now;
		}

		objectInteraction.OperatorAttackPerform(operators, enemies, deltaTime.count() / 1000.0f, *checkpointManager);
		
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

// �Ȱ��C���A����C���ɶ����ֿn
void CGameStateRun::PauseGame() {
	if (!isGamePaused) {
		UpdateGameTime();												// �T�O�b�Ȱ��e�C���ɶ��O�̷s��
		isGamePaused = true;											// �]�w�C�����Ȱ����A
	}
}

// �q�Ȱ����A��_�C���A���\�C���ɶ��A���ֿn
void CGameStateRun::ResumeGame() {
	if (isGamePaused) {
		isGamePaused = false;											// �C�����A�O�Ȱ����A
		lastUpdateTime = std::chrono::steady_clock::now();				// ���m lastUpdateTime ���{�b
	}
}

Checkpoint* CGameStateRun::FindNearestCheckpoint(CPoint point)		// ��X�̪�checkpoint	
{
	Checkpoint* NearestCheckpoint = nullptr;
	double minDistance = (std::numeric_limits<double>::max)();
	auto& gameMap = gameMapManager.getGameMap();
	nearLogicX = -1;
	nearLogicY = -1;

	//DBOUT("FindNearestCheckpoint - gameMap address: " << &gameMap << std::endl);	//�T�{�a�ϩ�O�����m�A�POnInit����

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


vector<int> CGameStateRun::FindPixelFromLogic(int logicX, int logicY)		// ��X�o��logic��pixel
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

void CGameStateRun::RemoveDeadEnemy()				//�������`���ĤH
{
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const std::shared_ptr<Enemy>& enemy) {
		return enemy->enemyState == EnemyState::DEAD;
		}), enemies.end());

}

void CGameStateRun::SortOperator()					//�ƧǷF��
{
	std::sort(operators.begin(), operators.end(), [](const std::unique_ptr<Operator>& a, const std::unique_ptr<Operator>& b)
		{
			return a->cost > b->cost;
		});
}


