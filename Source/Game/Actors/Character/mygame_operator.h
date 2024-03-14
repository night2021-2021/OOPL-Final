#ifndef OPERATOR_H
#define OPERATOR_H

#include <afxwin.h> 
#include "mygame_character.h"

namespace game_framework 
{
	enum class OperatorClass
	{
		Caster,
		Defender,
		Guard,
		Medic,
		Sniper,
		Supporter,
		Vanguard
	};

	class Operator : public Character
	{
	public:
		CMovingBitmap image;
		CPoint position;
		bool isPlacing;
		OperatorClass operatorClass;

		Operator(int maxHp, int atk, int def, float attackSpeed, OperatorClass opClass, bool placing = false)
        : Character(maxHp, atk, def, attackSpeed), operatorClass(opClass), isPlacing(placing) 
		{
			HP = maxHp; 
		}

	};
}

#endif