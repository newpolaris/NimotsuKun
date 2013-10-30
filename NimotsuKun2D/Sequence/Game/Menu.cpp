#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
using namespace GameLib;

#include "State.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Parent.h"

namespace Sequence{
namespace Game{

void Menu::update(Parent* parent)
{
	// 1:やりなおし(다시 고쳐 하기)
	// 2:面セレへ
	// 3:タイトルへ
	// 4:そのまま戻る
	// 添え字がずれると
	// 添え(そえ)字がずれると面倒(めんどう)なので0も入れておく
    // 첨자가 어긋나면 성가시므로 0도 넣어 둔다
    char numberChars[] = { '0', '1', '2', '3', '4' };
    int inputNumber = 0;
    for ( int i = 0; i < 5; ++i ) {
        if ( GameLib::Framework::instance().isKeyTriggered( numberChars[i] ) ) {
            inputNumber = i;
        }
    }

	switch ( inputNumber ){
		case 1: //やりなおし
			parent->state()->reset();
			parent->moveTo( Parent::SEQUENCE_PLAY );
			break;
		case 2: //面セレへ
			parent->moveTo( Parent::SEQUENCE_STAGE_SELECT );
			break;
		case 3: //タイトルへ
			parent->moveTo( Parent::SEQUENCE_TITLE );
			break;
		case 4: //そのまま戻る
			parent->moveTo( Parent::SEQUENCE_PLAY );
			break;
		default: //その他は無視
			break;
    }

	parent->state()->draw();
	image.draw();
}

} //namespace Game
} //namespace Sequence

