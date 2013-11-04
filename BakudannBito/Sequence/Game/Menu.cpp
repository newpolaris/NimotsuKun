#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
using namespace GameLib;

#include "State.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Parent.h"
#include "StringRenderer.h"

namespace Sequence{
namespace Game{

Menu::Menu() 
    : image("data/image/dummy.dds") 
{
    m_menu.push_back("Retry");
    m_menu.push_back("Back to stage Select");
    m_menu.push_back("Back to title");
    m_menu.push_back("Continue");
}

void Menu::update(Parent* parent)
{
    using std::string;

	parent->state()->draw();
	image.draw();

    static int current_item = 0;

    StringRenderer::instance().draw(" > ", 0, current_item);

    for (int i = 0; i < m_menu.size(); ++i)
        StringRenderer::instance().draw(m_menu[i], 4, i);

	// 1:やりなおし(다시 고쳐 하기)
	// 2:面セレへ
	// 3:タイトルへ
	// 4:そのまま戻る
	// 添え字がずれると
	// 添え(そえ)字がずれると面倒(めんどう)なので0も入れておく
    // 첨자가 어긋나면 성가시므로 0도 넣어 둔다
    
    if (GameLib::Framework::instance().isKeyTriggered('w')) {
        current_item--;
        if (current_item < 0)
            current_item = 0;
    }

    if (GameLib::Framework::instance().isKeyTriggered('s')) {
        current_item++;
        if (current_item > 3)
            current_item = 3;
    }

    if (GameLib::Framework::instance().isKeyTriggered(' ')) {
        switch (current_item){
            case 0: //やりなおし
                parent->state()->reset();
                parent->moveTo( Parent::SEQUENCE_PLAY );
                break;
            case 1: //面セレへ
                parent->moveTo( Parent::SEQUENCE_STAGE_SELECT );
                break;
            case 2: //タイトルへ
                parent->moveTo( Parent::SEQUENCE_TITLE );
                break;
            case 3: //そのまま戻る
                parent->moveTo( Parent::SEQUENCE_PLAY );
                break;
            default: //その他は無視
                break;
        }
    }
}

} //namespace Game
} //namespace Sequence

