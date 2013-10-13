#include <vector>

#include "GameLib/Framework.h"
#include "status.h"

char getInput()
{
	// get input and analysis exit status
	char ch;
	GameLib::cin >> ch;

	return ch;
}

namespace GameLib {
    void Framework::update() {
        static std::shared_ptr<game_status> status(game_status::initalize_game_status());

        status->update(getInput());
        if (status->is_finished())
            requestEnd();
        status->draw();
    }
}
