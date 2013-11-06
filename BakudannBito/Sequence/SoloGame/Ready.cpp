#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/SoloGame/Parent.h"
#include "Sequence/SoloGame/Ready.h"
#include "StringRenderer.h"

using namespace GameLib;

namespace Sequence {
namespace SoloGame {

Ready::Ready() {}

void Ready::update(Parent* parent)
{
    using namespace GameLib;

    StringRenderer::instance().draw("Ready");
    StringRenderer::instance().draw("Go", 0, 1);
    StringRenderer::instance().draw("Please input space bar to contiue", 0, 2);

    if (Framework::instance().isKeyTriggered(' ')) {
        parent->moveTo(Parent::SEQUENCE_PLAY);
    }
}

} // namespace Sequence 
} // namespace SoloGame 
