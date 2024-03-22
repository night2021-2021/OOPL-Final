#ifndef OPERATOR_H
#define OPERATOR_H

#include <afxwin.h> 
#include "mygame_character.h"
#include "../../../Library/gameutil.h"


namespace game_framework 
{
	enum class OperatorClass
	{
		Caster,			//High purple
		Defender,		//Tank
		Guard,			//Low Red
		Medic,			//Healer	
		Sniper,			//High Red	
		Supporter,		//High other
		Vanguard		//Low cost
	};

	enum class OperatorStatus {
        Default, 
        Battle,  
        Retreat  
    };

	enum class Orientation {
		Up,
		Down,
		Left,
		Right
	};

	class Operator : public Character
	{
	public:
		CMovingBitmap image;
		CMovingBitmap headImage;
		CPoint position;
		int blockCounts;		//the number of blocks that the operator can block the enemy
		bool isPlacing;
		OperatorClass operatorClass;
		OperatorStatus operatorStatus;
		Orientation orientation;

		Operator(int maxHp, int atk, int def, int blockCounts, float attackSpeed, OperatorClass opClass, Orientation ori = Orientation::Down, bool placing = false)
        : Character(maxHp, atk, def, attackSpeed), blockCounts(0), operatorClass(opClass), isPlacing(placing), operatorStatus(OperatorStatus::Default), orientation(ori)
		{
			HP = maxHp; 
		}

	};

	std::ostream& operator<<(std::ostream& os, const OperatorClass& opClass);
}

#endif