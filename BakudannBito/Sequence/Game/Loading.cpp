#include "GameLib/Framework.h"
#include "GameLib/GameLib.h"
using namespace GameLib;

#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Loading.h"

namespace Sequence {
namespace Game {

Loading::Loading()
    : mCount(0)
    , mStarted(false)
	, image("data/image/loading.dds")
{}

void Loading::update(Parent* parent) {
    if (!mStarted) {
		//結局ロードするのは親。なぜならStateを持っているのは親だから。
		parent->startLoading();
		mStarted = true;
    } else if (mCount == 60) { //1秒待つ
		parent->moveTo(Parent::SEQUENCE_PLAY); //Playに移動
    }

	image.draw();

	++mCount;
}

} // namespace Sequence 
} // namespace Game 