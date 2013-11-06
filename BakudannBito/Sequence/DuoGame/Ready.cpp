#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/DuoGame/Ready.h"
#include "Sequence/DuoGame/Parent.h"
#include "StringRenderer.h"

using namespace GameLib;

namespace Sequence {
namespace DuoGame {

Ready::Ready() : mImage("data/image/dummy.dds") {}


void Ready::update(Parent* parent)
{
    using namespace GameLib;

	mImage.draw();

    StringRenderer::instance().draw("Ready");
    StringRenderer::instance().draw("Go", 0, 1);
    StringRenderer::instance().draw("Please input space bar to contiue", 0, 2);

    if (Framework::instance().isKeyTriggered(' ')) {
        parent->moveTo(Parent::SEQUENCE_PLAY);
    }
}

} // namespace DuoGame 
} // namespace Sequence 

