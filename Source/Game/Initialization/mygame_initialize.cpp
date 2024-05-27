#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../mygame.h"
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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////
int game_framework::selectedMapIndex = 0;

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize...");    // 一開始的loading進度為0%
	loadfirstbackground();
	loadsecondbackground();
	state = 0;
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	GotoGameState(GAME_STATE_RUN);
}

void CGameStateInit::loadfirstbackground()
{
	firstbackground.LoadBitmapByString({ "resources/cg/mizuki.bmp" });
	firstbackground.SetTopLeft(0, 0);
}
void CGameStateInit::loadsecondbackground() {
	secondbackground.LoadBitmapByString({ "resources/test_image.bmp" });
	secondbackground.SetTopLeft(0, 0);
	
	for (int i = 0; i < 3; i++) {
		int x = 325 + 250 * i;
		int y = 300;

		buttons[i].LoadBitmapByString(std::vector<std::string>{"resources/button/button" + std::to_string(i + 1) + ".bmp"});
		buttons[i].SetTopLeft(x, y);
	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	int buttonWidth = 200, buttonHeight = 140;
	int topX = 325, topY = 300;

	if (state >= 2)
	{
		for (int i = 0; i < 3; ++i) { 
			int x = topX + i * buttonWidth;
			int y = topY;

			if (point.x >= x && point.x <= x + buttonWidth - 50 &&
				point.y >= y && point.y <= y + buttonHeight - 50) {
				selectedMapIndex = i;									// 設置地圖索引
				GotoGameState(GAME_STATE_RUN);							// 切換至 GAME_STATE_RUN
				DBOUT("You choose the " << selectedMapIndex + 1 << " maps. " << endl);
				return;
			}
		}
	}
	else {
		state += 1;
	}
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{

} 

void CGameStateInit::OnShow()
{
	if(state == 0)
	{
		firstbackground.ShowBitmap();
	}
	else if(state >= 1)
	{
		secondbackground.ShowBitmap();
		for (int i = 0; i < 3; i++) {
			buttons[i].ShowBitmap();
		}
	}
}


