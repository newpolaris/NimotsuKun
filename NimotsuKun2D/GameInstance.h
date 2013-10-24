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
	void requestSequence(SequenceType seq);
	void clearScreen();
	bool initGameObj();	
	void reinit() { m_bReInit = true; initGameObj(); }	
	void changeStage(int stage) { m_stage=stage; }
	void drawBlackPanel();

	const std::shared_ptr<Game>& GameObj() const { return game_; }

private:
	std::shared_ptr<Sequence> sequence_;
	std::shared_ptr<Game> game_;

	int m_stage;
	bool m_bReInit;

	SequenceType mReqSequence;
	SequenceType mSequence;
};

GameInstance& gameInstance();
