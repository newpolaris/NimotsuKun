#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

using namespace GameLib;

#include "Sequence/Title.h"
#include "Sequence/GameInstance.h"
#include "StringRenderer.h"

namespace Sequence {

Title::Title() : mImage("data/image/dummy.dds") 
{
    m_menu.push_back("1P Game");
    m_menu.push_back("2P Game");
}

void Title::update(GameInstance* parent) {
    using std::string;

	mImage.draw();

    StringRenderer::instance().draw("Bakudannbito");
    StringRenderer::instance().draw("Please input space bar", 0, 1);

    static int current_item = 0;

    StringRenderer::instance().draw(" > ", 0, 2+current_item);
    for (int i = 0; i < m_menu.size(); ++i)
        StringRenderer::instance().draw(m_menu[i], 4, 2+i);

    if (GameLib::Framework::instance().isKeyTriggered('w')) {
        current_item--;
        if (current_item < 0)
            current_item = 0;
    }

    if (GameLib::Framework::instance().isKeyTriggered('s')) {
        current_item++;
        if (current_item > 1)
            current_item = 1;
    }

    if (GameLib::Framework::instance().isKeyTriggered(' ')) {
        switch (current_item) {
            case 0: 
                parent->moveTo( GameInstance::SEQUENCE_SOLOGAME );
                break;
            case 1: 
                parent->moveTo( GameInstance::SEQUENCE_DUOGAME );
                break;
        }
    }
}

} // namespace Sequence
