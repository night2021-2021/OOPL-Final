#include "stdafx.h"
#include <iostream>
#include "../Library/gameutil.h"
#include "mygame_operator.h"

namespace game_framework {

    void Operator::SetHeadPosition(int x, int y) {
        headImage.SetTopLeft(x, y);
    }

    bool Operator::CheckIfSelected(const CPoint& point){
        int headTop = headImage.GetTop();
        int headLeft = headImage.GetLeft();
        int headHeight = headImage.GetHeight();
        int headWidth = headImage.GetWidth();

        int Top = image.GetTop();
        int Left = image.GetLeft();
        int Height = image.GetHeight();
        int Width = image.GetWidth();

        CRect headRect(headLeft, headTop, headLeft + headWidth, headTop + headHeight);
        CRect imageRect(Left, Top + 100, Left + Width, Top + Height);    // 0.4 is the ratio of the head image height to the whole image height

        bool selectedHead = point.x >= headRect.left && point.x <= headRect.right && point.y >= headRect.top && point.y <= headRect.bottom;
        bool selectedImage = point.x >= imageRect.left && point.x <= imageRect.right && point.y >= imageRect.top && point.y <= imageRect.bottom;

        return selectedHead || selectedImage;
    }

    std::ostream& operator<<(std::ostream& os, const OperatorClass& opClass) {
        switch (opClass) {
            case OperatorClass::Caster: os << "Caster"; break;
            case OperatorClass::Defender: os << "Defender"; break;
            case OperatorClass::Guard: os << "Guard"; break;
            case OperatorClass::Medic: os << "Medic"; break;
            case OperatorClass::Sniper: os << "Sniper"; break;
            case OperatorClass::Supporter: os << "Supporter"; break;
            case OperatorClass::Vanguard: os << "Vanguard"; break;
            default: os << "Unknown Class"; break;
        }
        return os;
    }
    

    void Operator::Retreat() {
        isPlacing = false;

        position.x = 1080;  
        position.y = 720;

        if (retreatCostIncreaseTimes < maxRetreatCostIncrease) {
            cost += costIncreaseAmount; 
            ++retreatCostIncreaseTimes; 
        }
    }

    void Operator::AdjustAttackRange() {
        attackRange = originalAttackRange;  

        for (auto& point : attackRange) {
            int originalX = point.x;
            int originalY = point.y;

            switch (orientation) {
            case Orientation::Up:                           // Rotate 270 degrees
                point.x = originalY;
                point.y = -originalX;
                break;
            case Orientation::Down:                         // Rotate 90 degrees
                point.x = -originalY;
                point.y = originalX;
                break;
            case Orientation::Left:                         // Rotate 180 degrees
                point.x = -originalX;
                point.y = -originalY;
                break;
            case Orientation::Right:                        // No rotation
                default:
                break;
            }
    
            point.x += logicX;
            point.y += logicY;                              //There are some problem with calculate
        }
    }
}
