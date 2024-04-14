#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../mygame.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

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
	ShowInitProgress(33, "Initialize...");    
	ShowInitProgress(66, "Initialize...");
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
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
	//按鈕一排六個
	// 按鈕 1 至 6
	button1.LoadBitmapByString({ "resources/button/button1.bmp" });
	button1.SetTopLeft(40 + 25 + 200 * 0, 10 + 25 + 140 * 0);

	button2.LoadBitmapByString({ "resources/button/button2.bmp" });
	button2.SetTopLeft(40 + 25 + 200 * 1, 10 + 25 + 140 * 0);

	button3.LoadBitmapByString({ "resources/button/button3.bmp" });
	button3.SetTopLeft(40 + 25 + 200 * 2, 10 + 25 + 140 * 0);

	button4.LoadBitmapByString({ "resources/button/button4.bmp" });
	button4.SetTopLeft(40 + 25 + 200 * 3, 10 + 25 + 140 * 0);

	button5.LoadBitmapByString({ "resources/button/button5.bmp" });
	button5.SetTopLeft(40 + 25 + 200 * 4, 10 + 25 + 140 * 0);

	button6.LoadBitmapByString({ "resources/button/button6.bmp" });
	button6.SetTopLeft(40 + 25 + 200 * 5, 10 + 25 + 140 * 0);

	// 按鈕 7 至 12
	button7.LoadBitmapByString({ "resources/button/button7.bmp" });
	button7.SetTopLeft(40 + 25 + 200 * 0, 10 + 25 + 140 * 1);

	button8.LoadBitmapByString({ "resources/button/button8.bmp" });
	button8.SetTopLeft(40 + 25 + 200 * 1, 10 + 25 + 140 * 1);

	button9.LoadBitmapByString({ "resources/button/button9.bmp" });
	button9.SetTopLeft(40 + 25 + 200 * 2, 10 + 25 + 140 * 1);

	button10.LoadBitmapByString({ "resources/button/button10.bmp" });
	button10.SetTopLeft(40 + 25 + 200 * 3, 10 + 25 + 140 * 1);

	button11.LoadBitmapByString({ "resources/button/button11.bmp" });
	button11.SetTopLeft(40 + 25 + 200 * 4, 10 + 25 + 140 * 1);

	button12.LoadBitmapByString({ "resources/button/button12.bmp" });
	button12.SetTopLeft(40 + 25 + 200 * 5, 10 + 25 + 140 * 1);

	// 按鈕 13 至 18
	button13.LoadBitmapByString({ "resources/button/button13.bmp" });
	button13.SetTopLeft(40 + 25 + 200 * 0, 10 + 25 + 140 * 2);

	button14.LoadBitmapByString({ "resources/button/button14.bmp" });
	button14.SetTopLeft(40 + 25 + 200 * 1, 10 + 25 + 140 * 2);

	button15.LoadBitmapByString({ "resources/button/button15.bmp" });
	button15.SetTopLeft(40 + 25 + 200 * 2, 10 + 25 + 140 * 2);

	button16.LoadBitmapByString({ "resources/button/button16.bmp" });
	button16.SetTopLeft(40 + 25 + 200 * 3, 10 + 25 + 140 * 2);

	button17.LoadBitmapByString({ "resources/button/button17.bmp" });
	button17.SetTopLeft(40 + 25 + 200 * 4, 10 + 25 + 140 * 2);

	button18.LoadBitmapByString({ "resources/button/button18.bmp" });
	button18.SetTopLeft(40 + 25 + 200 * 5, 10 + 25 + 140 * 2);

	// 按鈕 19 至 24
	button19.LoadBitmapByString({ "resources/button/button19.bmp" });
	button19.SetTopLeft(40 + 25 + 200 * 0, 10 + 25 + 140 * 3);

	button20.LoadBitmapByString({ "resources/button/button20.bmp" });
	button20.SetTopLeft(40 + 25 + 200 * 1, 10 + 25 + 140 * 3);

	button21.LoadBitmapByString({ "resources/button/button21.bmp" });
	button21.SetTopLeft(40 + 25 + 200 * 2, 10 + 25 + 140 * 3);

	button22.LoadBitmapByString({ "resources/button/button22.bmp" });
	button22.SetTopLeft(40 + 25 + 200 * 3, 10 + 25 + 140 * 3);

	button23.LoadBitmapByString({ "resources/button/button23.bmp" });
	button23.SetTopLeft(40 + 25 + 200 * 4, 10 + 25 + 140 * 3);

	button24.LoadBitmapByString({ "resources/button/button24.bmp" });
	button24.SetTopLeft(40 + 25 + 200 * 5, 10 + 25 + 140 * 3);

	// 按鈕 25 至 30
	button25.LoadBitmapByString({ "resources/button/button25.bmp" });
	button25.SetTopLeft(40 + 25 + 200 * 0, 10 + 25 + 140 * 4);

	button26.LoadBitmapByString({ "resources/button/button26.bmp" });
	button26.SetTopLeft(40 + 25 + 200 * 1, 10 + 25 + 140 * 4);

	button27.LoadBitmapByString({ "resources/button/button27.bmp" });
	button27.SetTopLeft(40 + 25 + 200 * 2, 10 + 25 + 140 * 4);

	button28.LoadBitmapByString({ "resources/button/button28.bmp" });
	button28.SetTopLeft(40 + 25 + 200 * 3, 10 + 25 + 140 * 4);

	button29.LoadBitmapByString({ "resources/button/button29.bmp" });
	button29.SetTopLeft(40 + 25 + 200 * 4, 10 + 25 + 140 * 4);

	button30.LoadBitmapByString({ "resources/button/button30.bmp" });
	button30.SetTopLeft(40 + 25 + 200 * 5, 10 + 25 + 140 * 4);


}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	state += 1;
	if(state >= 2)
	{
		GotoGameState(GAME_STATE_RUN);        // 切換至GAME_STATE_RUN
	}

	
}

void CGameStateInit::OnShow()
{
	if(state == 0)
	{
		firstbackground.ShowBitmap();
	}
	else if(state == 1)
	{
		secondbackground.ShowBitmap();
		button1.ShowBitmap();
		button2.ShowBitmap();
		button3.ShowBitmap();
		button4.ShowBitmap();
		button5.ShowBitmap();
		button6.ShowBitmap();
		button7.ShowBitmap();
		button8.ShowBitmap();
		button9.ShowBitmap();
		button10.ShowBitmap();
		button11.ShowBitmap();
		button12.ShowBitmap();
		button13.ShowBitmap();
		button14.ShowBitmap();
		button15.ShowBitmap();
		button16.ShowBitmap();
		button17.ShowBitmap();
		button18.ShowBitmap();
		button19.ShowBitmap();
		button20.ShowBitmap();
		button21.ShowBitmap();
		button22.ShowBitmap();
		button23.ShowBitmap();
		button24.ShowBitmap();
		button25.ShowBitmap();
		button26.ShowBitmap();
		button27.ShowBitmap();
		button28.ShowBitmap();
		button29.ShowBitmap();
		button30.ShowBitmap();
	}
	

}


