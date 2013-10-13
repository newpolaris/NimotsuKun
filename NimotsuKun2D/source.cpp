#include <vector>

#include "GameLib/Framework.h"
#include "state.h"

char getInput()
{
	// get input and analysis exit status
	char ch;
	GameLib::cin >> ch;

	return ch;
}

namespace GameLib {
    void Framework::update() {
        static std::shared_ptr<state> status(state::initalize_state());
        status->update(getInput());
        if (status->is_finished())
            requestEnd();
        status->draw();
    }
}
