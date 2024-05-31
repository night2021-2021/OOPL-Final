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
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g): CGameState(g)
{

}

void CGameStateOver::OnMove()
{

}

void CGameStateOver::OnBeginState()
{
	loadGameOverMap();
}

void CGameStateOver::OnInit()
{

}

void CGameStateOver::OnShow()
{
	gameoverBackground.ShowBitmap();
}

void CGameStateOver::OnLButtonUp(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_INIT);
}

	
void CGameStateOver::loadGameOverMap()
{
	gameoverBackground.LoadBitmapByString({ "resources/cg/Gameover.bmp" });
	gameoverBackground.SetTopLeft(0, 0);
}	