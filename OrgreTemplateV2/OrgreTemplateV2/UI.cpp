//#include "UI.h"
//
//
//UI::UI(SceneManager* scnMgr, Ogre::SceneNode* UINode)
//{
//
//	OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());
//	scnMgr->addRenderQueueListener(mOverlaySystem);
//	addInputListener(mTrayMgr);
//
//
//	//mTrayMgr->showLogo(TL_TOPRIGHT);
//	mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
//	mTrayMgr->toggleAdvancedFrameStats();
//
//	mTpuLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "Time/Update", "Time/Update:", 150);
//	mTpu = mTrayMgr->createLabel(TL_TOPRIGHT, "tpu", "0", 150);
//
//	//mInfoLabel = mTrayMgr->createLabel(TL_TOP, "T1Info", "PollockPong", 350);
//	mScoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Score", "Score: " + std::to_string(score), 100);
//
//
//	mLivesLabel = mTrayMgr->createLabel(TL_TOP, "Lives", "Lives: " + std::to_string(lives), 100);
//}
