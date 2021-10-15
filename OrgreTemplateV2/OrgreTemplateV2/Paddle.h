#pragma once

#include "GameObject.h"

class Paddle : public GameObject
{
	public: 
	float screenWidth;
	float paddleSpeed; 

	Paddle(Ogre::SceneManager* scnMgr, Ogre::SceneNode* paddleNode);
	void BoundsChecking();
	bool frameStarted(const Ogre::FrameEvent& evt);
};

