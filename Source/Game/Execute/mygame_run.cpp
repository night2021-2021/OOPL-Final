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
const int deviationX = 150;
const int deviationY = 220;

bool isDragging = false;

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

void CGameStateRun::OnMove()                            // ���ʹC������
{

}

void CGameStateRun::OnInit()                              // �C������Ȥιϧγ]�w
{
	cost = 0;

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

		DBOUT("OnInit - gameMap address: " << &gameMap << std::endl);	//�T�{�a�ϩ�O�����m�A�PFindNearestCheckpoint����
	}
	catch (std::exception& e) {
		DBOUT("Error of file open." << e.what());
	}

	game_framework::Reed reed;
	operators.push_back(reed);
	
	std::string enemyPath = "resources/map/enemyJSON/0-1_Enemy.JSON";
	
	try {
		enemyManager.loadEnemyFromJson(enemyPath);
		DBOUT("Success of enemy file open." << endl);
	}
	catch (std::exception& e) {
		DBOUT("Error of enemy file open." << e.what());
	}

	//�H�U��Ū�J�ĤH���{���X
	auto& loadedEnemies = enemyManager.getEnemies();
	for (auto& enemy : loadedEnemies) {
		enemies.push_back(enemy);
		DBOUT("Displaying enemies count in OnInit: " << enemies.size() << endl);
	}

	//�H�U���p�ɾ�
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
		operators[0].isPlacing = false;
		operators[0].position.x = 1080;
		operators[0].position.y = 720;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	if (cost >= operators[0].cost) {
		DBOUT("The cost of Reed is : " << operators[0].cost << endl);
		isDragging = true;

	}else {
		DBOUT("The cost is not enough" << endl);
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

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)    // �B�z�ƹ����ʧ@
{
	if (isDragging && operators[0].isPlacing == false)
	{
		Checkpoint* nearestCheckpoint = FindNearestCheckpoint(point);
		if (nearestCheckpoint != nullptr) {
			if (CanPlaceOperator(operators[0], *nearestCheckpoint)) {
				operators[0].position.x = nearestCheckpoint->visualX - deviationX;
				operators[0].position.y = nearestCheckpoint->visualY - deviationY;
				operators[0].isPlacing = true;
				cost -= operators[0].cost;
			}
			else {
				operators[0].position.x = 1080;
				operators[0].position.y = 720;
				DBOUT("The operator can't be placed here" << endl);
			}
		}	
	}
	isDragging = false;
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)    // �B�z�ƹ����ʧ@
{
	if (isDragging && operators[0].isPlacing == false)
	{
		Checkpoint* nearestCheckpoint = FindNearestCheckpoint(point);
		if (nearestCheckpoint != nullptr) {
			operators[0].position.x = nearestCheckpoint->visualX -deviationX;
			operators[0].position.y = nearestCheckpoint->visualY -deviationY;
		}
	}
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)    // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()									// ��ܹC���e��	
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

	//���� �ĤH������ ���\
	if (!enemies.empty()) {
		auto& firstEnemy = enemies[0]; // ����Ĥ@��ĤH���ޥ�
		firstEnemy->position.x -= 1;
	}

	//���� �ɶ��b
	UpdateGameTime();
}


void CGameStateRun::UpdateGameTime() {
	if (!isGamePaused) {
		auto now = std::chrono::steady_clock::now();
		gameTime += now - lastUpdateTime;								// �u���b���Ȱ��ɲֿn�C���ɶ�
		lastUpdateTime = now;											// ��s lastUpdateTime ���ثe�ɶ�

		auto LastCostUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCostUpdateTime).count();
		if (LastCostUpdate >= 500 && cost < 99) {
			cost += 1; 
			lastCostUpdateTime = now; 
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

void CGameStateRun::textShow(){
	CDC* pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 40, "�L�n������", RGB(255, 255, 255), 800);
	std::string costStr = "Cost: " + std::to_string(cost);
	CTextDraw::Print(pDC, 1100, 528, costStr.c_str());
	CDDraw::ReleaseBackCDC();
}

Checkpoint* CGameStateRun::FindNearestCheckpoint(CPoint point)		// ��X�̪�checkpoint	
{
	Checkpoint* NearestCheckpoint = nullptr;
	double minDistance = (std::numeric_limits<double>::max)();
	auto& gameMap = gameMapManager.getGameMap();

	//DBOUT("FindNearestCheckpoint - gameMap address: " << &gameMap << std::endl);	//�T�{�a�ϩ�O�����m�A�POnInit����

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
