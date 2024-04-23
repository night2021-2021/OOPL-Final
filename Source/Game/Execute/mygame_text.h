#pragma once
#include <string>
#include <afxwin.h>
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"


namespace game_framework {
    class TextRenderer {

    public:
        void Init() {
            CDC* pDC = CDDraw::GetBackCDC();
            CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
            CDDraw::ReleaseBackCDC();
        }

        void ShowText(const std::string& text, int x, int y) {
            CDC* pDC = CDDraw::GetBackCDC();
            CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 800);
            CTextDraw::Print(pDC, x, y, text.c_str());
            CDDraw::ReleaseBackCDC();
        }
    };
}