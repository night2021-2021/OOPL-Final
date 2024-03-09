#ifndef OPERATOR_H
#define OPERATOR_H

#include <afxwin.h> 
namespace game_framework 
{
	struct Operator
	{
		CMovingBitmap image;
		CPoint position;
		bool isPlacing;
		int maxHealth;

		Operator() : isPlacing(false) {}
	};
}

#endif