#include "GameLib/Framework.h"
#include "GameInstance.h"
#include "Menu.h"
#include "Sequence/Game.h"

void Menu::input()
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

    switch ( inputNumber ) {
        case 1: // やりなおし
            gameInstance().reset();
            gameInstance().requestSequence(SEQUENCE_GAME);
            break;
        case 2: // 面セレへ
            gameInstance().requestSequence(SEQUENCE_STAGE_SELECT);
			break;
		case 3: // タイトルへ
            gameInstance().requestSequence(SEQUENCE_TITLE);
			break;
		case 4: // そのまま戻る
            gameInstance().requestSequence(SEQUENCE_GAME);
			break;
		default: // その他(ほか)は無視(むし)
			break;
    }
}

void Menu::draw()
{
	auto f = GameLib::Framework::instance();

    gameInstance().GameObj()->draw();
	gameInstance().drawBlackPanel();

	int height = f.height();
	int width  = f.width();

	titleImage.draw(0, 0, 0, 0, width, height);
}
