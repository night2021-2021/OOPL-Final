/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "../Game/Actors/Character/mygame_operator.h"
#include "../Game/Actors/Character/mygame_enemy.h"
#include "../Game/Map/mygame_mapAndCheckpoint.h"
#include "../Game/Map/mygame_mapManager.h"
#include "../Game/Map/mygame_checkpointManager.h"
#include "../Game/Execute/objectInteraction.h"
#include <chrono>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		void loadfirstbackground();
		void loadsecondbackground();

		int state = 0; 	//0: 水月  1:星空  2:遊戲開始
		CMovingBitmap firstbackground;
		CMovingBitmap secondbackground;
		CMovingBitmap button1;
		CMovingBitmap button2;
		CMovingBitmap button3;
		CMovingBitmap button4;
		CMovingBitmap button5;
		CMovingBitmap button6;
		CMovingBitmap button7;
		CMovingBitmap button8;
		CMovingBitmap button9;
		CMovingBitmap button10;
		CMovingBitmap button11;
		CMovingBitmap button12;
		CMovingBitmap button13;
		CMovingBitmap button14;
		CMovingBitmap button15;
		CMovingBitmap button16;
		CMovingBitmap button17;
		CMovingBitmap button18;
		CMovingBitmap button19;
		CMovingBitmap button20;
		CMovingBitmap button21;
		CMovingBitmap button22;
		CMovingBitmap button23;
		CMovingBitmap button24;
		CMovingBitmap button25;
		CMovingBitmap button26;
		CMovingBitmap button27;
		CMovingBitmap button28;
		CMovingBitmap button29;
		CMovingBitmap button30;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  		// 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);			// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);			// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point); 		 	// 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);			// 處理滑鼠的動作

		Checkpoint* FindNearestCheckpoint(CPoint point);		// 找出最近的checkpoint

		void PauseGame();										// 暫停遊戲
		void ResumeGame();										// 繼續遊戲
		void UpdateGameTime();									// 更新遊戲時間
		
		void ShowAttackRange();									// 顯示攻擊範圍
		void UnshowAttackRange();								// 隱藏攻擊範圍

		vector<int> FindPixelFromLogic(int logicX, int logicY); // 找出這個logic的pixel

	protected:
		void OnMove();											// 移動遊戲元素
		void OnShow();											// 顯示這個狀態的遊戲畫面

	private:
		CMovingBitmap background;
		std::vector<std::unique_ptr<Operator>> operators;
		std::vector<std::shared_ptr<Enemy>> enemies;			// 用vector來儲存所有的敵人
		GameMap gameMap;		
		GameMapManager gameMapManager;
		ObjectInteraction objectInteraction;
		std::unique_ptr<CheckpointManager> checkpointManager;
		void textShow();
		int cost;
		int selOpIdx;
		int nearLogicX;
		int nearLogicY;
		bool isDragging;
		bool isConfirmingPlacement;
		bool isGamePaused;										//time
		std::chrono::steady_clock::time_point mainTime;
		std::chrono::duration<float, std::milli> gameTime;
		std::chrono::steady_clock::time_point lastUpdateTime;
		std::chrono::steady_clock::time_point lastCostUpdateTime;

		void RemoveDeadEnemy();
		void SortOperator();	
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂nji
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap background;
		GameMapManager gameMapManager;
		GameMap gameMap;
		int counter;									// 倒數之計數器
	};

}