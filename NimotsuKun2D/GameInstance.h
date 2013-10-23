#pragma once

#include <memory>
#include "Sequence/Sequence.h"

class Title;
class Game;

class GameInstance
{
public:
	GameInstance();
	void update();
	void changeSequence();
	void requestSequence(Sequence seq);
	void clearScreen();

private:
	std::shared_ptr<Title> title_;
	std::shared_ptr<Game> game_;

	int gameStage;

	Sequence mReqSequence;
	Sequence mSequence;
};

GameInstance& gameInstance();
