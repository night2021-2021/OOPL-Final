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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////
int game_framework::selectedMapIndex = 0;
int topX = 250, topY = 300;
int buttonWidth = 200, buttonHeight = 100;
int gap = 100;

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0, "Start Initialize...");    // �@�}�l��loading�i�׬�0%
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
	secondbackground.LoadBitmapByString({ "resources/cg/SelectMap.bmp" });
	secondbackground.SetTopLeft(0, 0);
	
	for (int i = 0; i < 3; i++) {
		int x = topX + i * (buttonWidth + gap);
		int y = topY;

		buttons[i].LoadBitmapByString(std::vector<std::string>{"resources/button/level" + std::to_string(i + 1) + ".bmp", "resources/button/level" + std::to_string(i + 1) + "_choose.bmp", "resources/button/lock.bmp"});
		buttons[i].SetTopLeft(x, y);
	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (state >= 1)
	{
		for (int i = 0; i < 3; ++i) { 
			int x = topX + i * (buttonWidth + gap);
			int y = topY;

			if (point.x >= x && point.x <= x + buttonWidth &&
				point.y >= y && point.y <= y + buttonHeight) {
				selectedMapIndex = i;									// �]�m�a�ϯ���
				ShowInitProgress(0, "Start Initialize...");
				GotoGameState(GAME_STATE_RUN);							// ������ GAME_STATE_RUN
				ShowInitProgress(100, "Done!");
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
	if (state >= 1)
	{
		for (int i = 0; i < 3; ++i) {
			int x = topX + i * (buttonWidth + gap);
			int y = topY;

			if (point.x >= x && point.x <= x + buttonWidth &&
				point.y >= y && point.y <= y + buttonHeight) {
				selectedMapIndex = i;
				buttons[i].SetFrameIndexOfBitmap(0);

			}
			else {
				buttons[i].SetFrameIndexOfBitmap(1);
			}
		}
	}
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


