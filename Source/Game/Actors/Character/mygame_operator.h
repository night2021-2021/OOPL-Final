#ifndef OPERATOR_H
#define OPERATOR_H

#include <afxwin.h> 
#include "mygame_character.h"
#include "../../../Library/gameutil.h"
#include <vector>


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

	enum class OperatorState {
        IDLE,
		ATTACK,
		DEAD
    };

	enum class Orientation {
		Up,
		Down,
		Left,
		Right
	};

	struct AttackRange
	{
		int x, y;
	};

	class Operator : public Character
	{
	public:
		CMovingBitmap image;
		CMovingBitmap frontIdleImage;
		CMovingBitmap leftIdleImage;
		CMovingBitmap backIdleImage;
		CMovingBitmap frontAttackImage;
		CMovingBitmap leftAttackImage;
		CMovingBitmap backAttackImage;
		CMovingBitmap headImage;
		CPoint position;
		int blockCounts;		//the number of blocks that the operator can block the enemy
		int cost;
		int sp;
		int maxSp;
		int logicX, logicY;	 	//the position of the operator in the logic map (0, 0)
		bool isPlacing;
		float attackCD;
		OperatorClass operatorClass;
		OperatorState operatorStatus;
		Orientation orientation;

		Operator(int maxHp, int atk, int def, int blocks, int cost, int sp, int maxSP, float attackSpeed, OperatorClass opClass, Orientation ori = Orientation::Down, bool placing = false)
			: Character(maxHp, atk, def, attackSpeed), blockCounts(blocks), cost(cost), maxSp(maxSP), sp(sp), operatorClass(opClass), isPlacing(placing), operatorStatus(OperatorState::IDLE), orientation(ori), attackCD(0.0f)
		{
		}

		//Operator's Load Images
		virtual void LoadImages() {};
		virtual void LoadIdleImagesForDirection(const char* subfolder, const char* statusfolder, CMovingBitmap& imageObject, int imageCount) {};

		//Operator's Skill
		virtual void Skill() {};

		//Operator's setting
		virtual void ChangeImages();
		void ChangeOperatorState(OperatorState newState);

		//Operator Selected
		void SetHeadPosition(int x, int y);
		bool CheckIfSelected(const CPoint& point);

		//Add cost if retreat
		int retreatCostIncreaseTimes = 0;
		static constexpr int maxRetreatCostIncrease = 3;
		static constexpr int costIncreaseAmount = 2;
		void Retreat();

		//Define the operator's attack range	
		std::vector<AttackRange> attackRange;
		std::vector<AttackRange> originalAttackRange;
		virtual void SetAttackRange() {}
		void AdjustAttackRange();
	};

	std::ostream& operator<<(std::ostream& os, const OperatorClass& opClass);
}

#endif