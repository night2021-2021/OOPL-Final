#include "stdafx.h"
#include <iostream>
#include "../Library/gameutil.h"
#include "../Game/Map/mygame_checkpointManager.h"
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
        CRect imageRect(Left + 60, Top + 100, Left + Width - 70, Top + Height);    

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
    

    void Operator::Retreat(CheckpointManager& checkpointManager) {
        isPlaced = false;
        isAlive = false;

        position.x = 1080;  
        position.y = 720;

        checkpointManager.unregisterOperatorAtCheckpoint(logicX, logicY, blockCounts);

        isPlaceable = false;
        DeployTimer = 0.0f;

        if (retreatCostIncreaseTimes < maxRetreatCostIncrease) {
            cost *= costIncreaseAmount; 
            ++retreatCostIncreaseTimes; 
        }
    }

    void Operator::DeployCD(float deltaTime) {          //The time that the operator can be deployed again
        if (!isPlaceable) {
            DeployTimer += deltaTime;
            if (DeployTimer >= DeployTime) {
				DeployTimer = 0.0f;
                isPlaceable = true;
			}
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
            point.y += logicY;                             
        }
    }

    void Operator::ChangeImages() {
        switch (operatorStatus) {
        case OperatorState::IDLE:
            switch (orientation) {
            case Orientation::Up:
                image = backIdleImage;
                break;
            case Orientation::Down:
                image = frontIdleImage;  
                break;
            case Orientation::Left:
                image = leftIdleImage;
                break;
            case Orientation::Right:
                image = frontIdleImage;
                break;
            }
            break;
        case OperatorState::ATTACK:
            switch (orientation) {
            case Orientation::Up:
                image = backAttackImage;  
                break;
            case Orientation::Down:
                image = frontAttackImage;  
                break;
            case Orientation::Left:
                image = leftAttackImage;  
                break;
            case Orientation::Right:
                image = frontAttackImage;  
                break;
            }
            break;
        }
    }

    void Operator::ChangeOperatorState(OperatorState newState)
    {
        if (operatorStatus != newState)
        {
            operatorStatus = newState;
            ChangeImages();
        }
    }
}
