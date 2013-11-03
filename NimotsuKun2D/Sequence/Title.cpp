#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

using namespace GameLib;

#include "Sequence/Title.h"
#include "Sequence/GameInstance.h"
#include "StringRenderer.h"

namespace Sequence {

void Title::update(GameInstance* parent) {
	if (Framework::instance().isKeyTriggered(' '))
		parent->moveTo(GameInstance::SEQUENCE_STAGE_SELECT);

    image.draw();

    StringRenderer::instance().draw("Nimotsukun");
    StringRenderer::instance().draw("Please input space bar", 0, 1);
}

} // namespace Sequence
