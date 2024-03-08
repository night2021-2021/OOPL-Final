#ifndef OPERATOR_H
#define OPERATOR_H

#include <afxwin.h> 

struct Operator
{
	CMovingBitmap image;
	CPoint position;
	bool isPlacing;

	Operator() : isPlacing(false) {}
};

#endif