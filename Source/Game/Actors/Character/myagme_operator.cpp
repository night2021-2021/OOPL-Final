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

    std::string OperatorClassToString(OperatorClass opClass) {
        switch (opClass) {
        case OperatorClass::Caster: return "caster";
        case OperatorClass::Defender: return "defender";
        case OperatorClass::Guard: return "guard";
        case OperatorClass::Medic: return "medic";
        case OperatorClass::Sniper: return "sniper";
        case OperatorClass::Supporter: return "supporter";
        case OperatorClass::Vanguard: return "vanguard";
        default: return "unknown";
        }
    }
}
