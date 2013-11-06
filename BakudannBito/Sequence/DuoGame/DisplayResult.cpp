#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/DuoGame/DisplayResult.h"
#include "Sequence/DuoGame/Parent.h"
#include "StringRenderer.h"

using namespace GameLib;

namespace Sequence {
namespace DuoGame {

DisplayResult::DisplayResult() {}

void DisplayResult::update(Parent* parent)
{
    using namespace GameLib;

    StringRenderer::instance().draw("DisplayResult");
    StringRenderer::instance().draw("Please input space key go to Ready", 0, 1);
    StringRenderer::instance().draw("Please input t key go to Title", 0, 2);

    if (Framework::instance().isKeyTriggered(' ')) 
        parent->moveTo(Parent::SEQUENCE_READY);
    else if (Framework::instance().isKeyTriggered('t'))
        parent->moveTo(Parent::SEQUENCE_TITLE);
}

} // namespace DuoGame 
} // namespace Sequence 


