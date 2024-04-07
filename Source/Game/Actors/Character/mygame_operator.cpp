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
        CRect imageRect(Left, Top, Left + Width, Top + Height);

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
    
}
