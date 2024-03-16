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

	enum class OperatorStatus {
        Default, 
        Battle,  
        Retreat  
    };

	class Operator : public Character
	{
	public:
		CMovingBitmap image;
		CPoint position;
		bool isPlacing;
		OperatorClass operatorClass;
		OperatorStatus operatorStatus;

		Operator(int maxHp, int atk, int def, float attackSpeed, OperatorClass opClass, bool placing = false)		//構造函數，用以初始化成員變量
        : Character(maxHp, atk, def, attackSpeed), operatorClass(opClass), isPlacing(placing), operatorStatus(OperatorStatus::Default)
		{
			HP = maxHp; 
		}

	};
}

#endif