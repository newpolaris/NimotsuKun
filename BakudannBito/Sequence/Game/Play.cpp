#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/Game/Play.h"
#include "Sequence/Game/Parent.h"
#include "State.h"

using namespace GameLib;

namespace Sequence{
namespace Game{


void Play::update( Parent* parent ){
	State* state = parent->state();

	bool cleared = false;
	//メインループ
	//クリアチェック
	if ( state->hasCleared() ){
		cleared = true;
	}
	//入力取得
	//SPACE押されたらメニューへ行く
	Framework f = Framework::instance();
	if ( f.isKeyTriggered( ' ' ) ){
		parent->moveTo( Parent::SEQUENCE_MENU );
	}else{ //通常更新
		int dx = 0;
		int dy = 0;
		if ( f.isKeyOn( 'a' ) ){
			dx -= 1;
		}else if ( f.isKeyOn( 's' ) ){
			dx += 1;
		}else if ( f.isKeyOn( 'w' ) ){
			dy -= 1;
		}else if ( f.isKeyOn( 'z' ) ){
			dy += 1;
		}
		//更新
		state->update(point(dx, dy));

		//クリアしたなら上へ報告
		if ( cleared ){
			parent->moveTo( Parent::SEQUENCE_CLEAR );
		}
	}
	//描画
	state->draw();
}

} //namespace Game
} //namespace Sequence
