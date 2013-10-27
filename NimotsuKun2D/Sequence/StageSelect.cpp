#include "GameLib/Framework.h"
#include "StageSelect.h"
#include "GameInstance.h"

void StageSelect::input()
{
	auto f = GameLib::Framework::instance();

	// 入力(にゅうりょく)取得(しゅとく)
	int stage = 0;

	// 添え(そえ)字がずれると厄介(やっかい)なので0も入れ(いれ)ておく
    // 첨자가 어긋나면 귀찮은 것으로 0도 넣어 둔다
    char numberChars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    for ( int i = 0; i < 10; ++i ) {
        if (GameLib::Framework::instance().isKeyTriggered( numberChars[ i ] ) ) {
            stage = i;
        }
    }

	if (stage != 0) {
		gameInstance().changeStage(stage);
		gameInstance().requestSequence(SEQUENCE_LOAD);
	}

    if (f.isKeyTriggered('q'))
		f.requestEnd();
}

void StageSelect::draw()
{
	auto f = GameLib::Framework::instance();
	int height = f.height();
	int width  = f.width();

	image.draw(0, 0, 0, 0, width, height);
}
