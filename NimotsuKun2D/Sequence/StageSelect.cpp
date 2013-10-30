#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
using namespace GameLib;

#include "Sequence/StageSelect.h"
#include "Sequence/GameInstance.h"

namespace Sequence{

void StageSelect::update(GameInstance* parent)
{
	// 入力(にゅうりょく)取得(しゅとく)
	int stage = 0;

	// 添え(そえ)字がずれると厄介(やっかい)なので0も入れ(いれ)ておく
    // 첨자가 어긋나면 귀찮은 것으로 0도 넣어 둔다
    char numberChars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    for ( int i = 0; i < 10; ++i ) {
        if (Framework::instance().isKeyTriggered( numberChars[ i ] ) ) {
            stage = i;
        }
    }

	if (stage != 0) {
		parent->setStageID( stage );
		parent->moveTo(GameInstance::SEQUENCE_GAME);
	}

    image.draw();
}

} //namespace Sequence
