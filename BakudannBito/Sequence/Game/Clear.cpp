#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/GameInstance.h"
#include "Image.h"
#include "State.h"

using namespace GameLib;

namespace Sequence {
namespace Game {
	
Clear::Clear() 
    : mCount(0)
    , image("data/image/clear.dds") {}

void Clear::update(Parent* parent) {
	if (mCount == 60) {
		parent->moveTo(Parent::SEQUENCE_STAGE_SELECT);
	}
	parent->state()->draw();
	image.draw();

	++mCount;
}

} // namespace Game
} // namespace Sequence
