#include <vector>

#include "GameLib/Framework.h"
#include "state.h"


namespace GameLib {
    void Framework::update() {
        static std::shared_ptr<state> status(state::initalize_state());
        status->update();
        if (status->is_finished())
            requestEnd();
        status->draw();
    }
}
