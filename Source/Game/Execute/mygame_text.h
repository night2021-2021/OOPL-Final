#pragma once
#include <string>
#include <afxwin.h>
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"


namespace game_framework {
    struct TextFormat {
        int fontSize;
        COLORREF color;
        int fontWeight;
        std::string fontName;

        TextFormat(int size = 40, COLORREF col = RGB(255, 255, 255), int weight = 800, std::string name = "Times New Roman")
            : fontSize(size), color(col), fontWeight(weight), fontName(name) {}
    };

    class TextRenderer {
    public:
        void ShowText(const std::string& text, int x, int y, const TextFormat& format) {
            CDC* pDC = CDDraw::GetBackCDC();
            CTextDraw::ChangeFontLog(pDC, format.fontSize, format.fontName.c_str(), format.color, format.fontWeight);
            CTextDraw::Print(pDC, x, y, text.c_str());
            CDDraw::ReleaseBackCDC();
        }
    };
}