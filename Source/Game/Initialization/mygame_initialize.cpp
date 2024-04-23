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
	ShowInitProgress(33, "Initialize...");    
	ShowInitProgress(66, "Initialize...");
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
	
	for (int i = 0; i < 30; i++) {
		int row = i / 6;
		int col = i % 6;
		int x = 40 + 25 + 200 * col;
		int y = 10 + 25 + 140 * row;

		buttons[i].LoadBitmapByString(std::vector<std::string>{"resources/button/button" + std::to_string(i + 1) + ".bmp"});
		buttons[i].SetTopLeft(x, y);
	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	int buttonWidth = 200, buttonHeight = 140;
	int topX = 40 + 25, topY = 10 + 25;

	state += 1;
	if(state >= 2)
	{
		for (int i = 0; i < 30; ++i) {
			int row = i / 6;
			int col = i % 6;
			int x = topX + col * buttonWidth;
			int y = topY + row * buttonHeight;

			if (point.x >= x && point.x <= x + buttonWidth - 50 &&
				point.y >= y && point.y <= y + buttonHeight - 50) {
				selectedMapIndex = i;									// �]�m�a�ϯ���
				GotoGameState(GAME_STATE_RUN);							// ������ GAME_STATE_RUN
				DBOUT("You choose the " << selectedMapIndex + 1 << " maps. " << endl);
				return;
			}
		}
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
	else if(state == 1)
	{
		secondbackground.ShowBitmap();
		for (int i = 0; i < 30; i++) {
			buttons[i].ShowBitmap();
		}
	}
}


