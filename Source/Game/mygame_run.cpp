#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame_operator.h"
#include "mygame.h"
#include "mygame_map.h"
#include <vector>


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
	background.LoadBitmapByString({ "resources/0-3.bmp" });
	background.SetTopLeft(0, 0);

	Operator reed;
	reed.image.LoadBitmapByString({ "resources/Reed.bmp" }, RGB(255, 255, 255));
    reed.position = CPoint(1180, 720);

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
		operators[0].position.x = (point.x / GRID_SIZE) * GRID_SIZE + 40;
		operators[0].position.y = (point.y / GRID_SIZE) * GRID_SIZE;
		isDragging = false;
	}
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)    // 處理滑鼠的動作
{
	if (isDragging)
	{
		operators[0].position.x = (point.x / GRID_SIZE) * GRID_SIZE + 40;
		operators[0].position.y = (point.y / GRID_SIZE) * GRID_SIZE;
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