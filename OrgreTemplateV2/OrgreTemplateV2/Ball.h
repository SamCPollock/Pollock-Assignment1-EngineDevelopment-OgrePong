#pragma once
#include "GameObject.h"
#include "Ogre.h"
#include "CollisionManager.h"
#include "Paddle.h"
#include <iostream>

using namespace Ogre;
//using namespace OgreBites;

class Ball : public GameObject
{
	private: 
		Paddle* paddleRef;

public:
	float screenWidth;
	float ballSpeed;
	int ballScore;
	int ballLives;
	
	Ball(SceneManager* scnMgr, Ogre::SceneNode* ballNode, Paddle* paddleReference);
	

	void BoundsChecking();
	void HitBottom();
	void ReboundPaddle();
	void ReboundSides();
	bool frameStarted(const Ogre::FrameEvent& evt);
};

