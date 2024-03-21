#include "StdAfx.h"
#include "OperatorPlacement.hpp"

namespace game_framework {
    bool OperatorPlacement::CanPlaceOperator(const Operator& op, const Checkpoint& checkpoint) const {
        switch(op.operatorClass) {
            case OperatorClass::Caster:
            case OperatorClass::Medic:
            case OperatorClass::Sniper:
            case OperatorClass::Supporter:
                return checkpoint.CKPTType == "platform";
            case OperatorClass::Defender:
            case OperatorClass::Guard:
            case OperatorClass::Vanguard:
                return checkpoint.CKPTType == "path";
            default:
                return false;
        }
    }
}