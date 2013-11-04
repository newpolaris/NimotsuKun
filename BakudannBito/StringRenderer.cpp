#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include <string>
#include "StringRenderer.h"
#include "point.h"

StringRenderer& StringRenderer::instance()
{
    static StringRenderer renderer;
    return renderer;
}

StringRenderer::StringRenderer()
    : image("data/image/font.dds")
{
}

point charPos(char c) 
{
	// 48 is assci offset, 32 is image offset
	c = c - 48 + 16;
    // 0 is 48(0x30), in (1,0) and one row has 16 elements.
    return point(c%0x10, c/0x10);
}

void StringRenderer::draw(std::string text, int x, int y)
{
    static int FontFixedWidth  = 8;
    static int FontFixedHeight = 16;

    for (unsigned i=0; i < text.size(); ++i)
    {
        point pos = charPos(text[i]);

        image.drawWithReplacementColor(FontFixedWidth*(x+i), y*FontFixedHeight,
									   pos.x*FontFixedWidth, pos.y*FontFixedHeight,
									   FontFixedWidth, FontFixedHeight);
    }
}

