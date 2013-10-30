#include "GameInstance.h"
#include "Sequence/Title.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/StageSelect.h"
#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Loading.h"
#include "GameLib/Framework.h"

//?°ãƒ­?¼ãƒ?«å¤‰???¸ã‚“?™ã†)
Sequence::GameInstance* gRootSequence = 0; //?¹ã£?“ã‚·?¼ã‚±?³ã‚¹
int gCounter = 0; //?¡ã‚¤?³ãƒ«?¼ãƒ—?’å›?£ãŸ?æ•°?’æ•°?ˆã‚‹?«ã‚¦?³ã‚¿

namespace GameLib {
    void Framework::update() {
		if ( !gRootSequence ){
			gRootSequence = new Sequence::GameInstance();
		}
		//?•ãƒ¬?¼ãƒ ?¬ãƒ¼?ˆèª¿???¡ã‚‡?†ã›??
		setFrameRate( 60 ); //ä¸€?å‘¼?¹ã°?„ã„?? ?Œé¢?’ãª??§?¼ã‚“?§ã—?¾ã†??

		if ( gCounter % 60 == 0 ){ //60?•ãƒ¬?¼ãƒ ?«ä??ãƒ•?¬ãƒ¼? ãƒ¬?¼ãƒˆè¡¨ç¤º
			cout << " FrameRate:" << frameRate() << endl;
		}
		++gCounter;

		gRootSequence->update();

		//çµ‚äº†?¤å®š(q?ŒæŠ¼?•ã‚Œ?Ÿã‹?ãƒ?¦ã‚¹?§Ã—ãƒœ?¿ãƒ³?Œå©?‹ã‚Œ?Ÿã‹)
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
    , mStageSelect( 0 )
    , mGame( 0 )
    , mNext( SEQUENCE_NONE )
    , mStageID( 0 )
{
	mTitle = new Title();
}

GameInstance::~GameInstance()
{
	SAFE_DELETE(mTitle);
	SAFE_DELETE(mGame);
	SAFE_DELETE(mStageSelect);
}

void GameInstance::update() 
{
	if (mTitle)
		mTitle->update(this);
	else if (mStageSelect)
		mStageSelect->update(this);
	else if (mGame)
		mGame->update(this);
	else
		HALT("bakana!"); //?ê·™êµ¤??€ê²??

	//?ë£¨ã‰??µì¸£
	switch ( mNext ){
		case SEQUENCE_STAGE_SELECT:
			SAFE_DELETE( mTitle );
			SAFE_DELETE( mGame );
			mStageSelect = new StageSelect();
			break;
		case SEQUENCE_TITLE:
			SAFE_DELETE( mGame );
			mTitle = new Title(); 
			break;
		case SEQUENCE_GAME:
			SAFE_DELETE( mStageSelect );
			ASSERT( mStageID != 0 ); //??²êµ›?ë³ê²?Î³êµ??‰ê±¦??£ê²?ê¾ êµ¥??ê±?
			mGame = new Game::Parent( mStageID );
			break;
	}
	mNext = SEQUENCE_NONE;
}

void GameInstance::moveTo( SeqID next ){
	mNext = next;
}

void GameInstance::setStageID( int stageID ){
	mStageID = stageID;
}

} //namespace Sequence

