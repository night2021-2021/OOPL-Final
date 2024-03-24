#include "stdafx.h"
#include <iostream>
#include "mygame_operator.h"

namespace game_framework {

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
