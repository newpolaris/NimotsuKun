#include <fstream>
#include <cassert>

#include "GameLib/Framework.h"

#include "GameInstance.h"
#include "Sequence/Title.h"
#include "Sequence/GameOver.h"
#include "Sequence/Ending.h"
#include "Sequence/SoloGame/Parent.h"
#include "Sequence/DuoGame/Parent.h"

Sequence::GameInstance* gRootSequence = 0; 
int gCounter = 0;

namespace GameLib {
    void Framework::update() {
		if ( !gRootSequence ){
			try {
				gRootSequence = new Sequence::GameInstance();
			}
			catch (std::ifstream::failure e) {
				cout << "File Read Failure" << endl; 
				GameLib::Framework::instance().requestEnd();
				return;
			}
			catch (std::exception e) {
				cout << "Can't find file" << endl; 
				GameLib::Framework::instance().requestEnd();
				return;
			}
		}

		setFrameRate( 60 ); 

		if ( gCounter % 60 == 0 ){ 
			cout << " FrameRate:" << frameRate() << endl;
		}
		++gCounter;

		gRootSequence->update();

		if ( isKeyOn( 'q' ) ){
			requestEnd();
		}
		if ( isEndRequested() ){
			SAFE_DELETE( gRootSequence );
		}
    }
}

namespace Sequence {

GameInstance::GameInstance() 
    : mTitle( 0 )
    , mEnding( 0 )
    , mGameOver( 0 )
    , mSoloGame( 0 )
    , mDuoGame( 0 )
    , mNext( SEQUENCE_NONE )
    , mStageID( 0 )
{
	mTitle = new Title();
}

GameInstance::~GameInstance()
{
	SAFE_DELETE(mTitle);
	SAFE_DELETE(mEnding);
	SAFE_DELETE(mGameOver);
	SAFE_DELETE(mSoloGame);
	SAFE_DELETE(mDuoGame);
}

void GameInstance::update() 
{
	if (mTitle)
		mTitle->update(this);
	else if (mEnding)
		mEnding->update(this);
	else if (mGameOver)
		mGameOver->update(this);
	else if (mSoloGame)
		mSoloGame->update(this);
	else if (mDuoGame)
		mDuoGame->update(this);
	else
		HALT("bakana!");

	switch ( mNext ){
		case SEQUENCE_TITLE:
			SAFE_DELETE( mGameOver );
			SAFE_DELETE( mEnding );
			SAFE_DELETE( mSoloGame );
			SAFE_DELETE( mDuoGame );
			mTitle = new Title(); 
			break;
        case SEQUENCE_ENDING:
			SAFE_DELETE( mSoloGame );
			mEnding = new Ending(); 
			break;
        case SEQUENCE_GAMEOVER:
			SAFE_DELETE( mSoloGame );
			mGameOver = new GameOver();
			break;
		case SEQUENCE_SOLOGAME:
			SAFE_DELETE( mTitle );
			mSoloGame = new SoloGame::Parent();
			break;
		case SEQUENCE_DUOGAME:
            SAFE_DELETE( mTitle );
			mDuoGame = new DuoGame::Parent();
			break;
	}
	mNext = SEQUENCE_NONE;
}

void GameInstance::moveTo( SeqID next ){
	mNext = next;
}

} //namespace Sequence

