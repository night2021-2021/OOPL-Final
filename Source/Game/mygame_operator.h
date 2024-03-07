#ifndef OPERATOR_H
#define OPERATOR_H

#include <afxwin.h> 

struct Operator
{
	CBitmap image;
	CPoint position;
	bool isPlacing;

	Operator() : isPlacing(false) {}
};

#endif