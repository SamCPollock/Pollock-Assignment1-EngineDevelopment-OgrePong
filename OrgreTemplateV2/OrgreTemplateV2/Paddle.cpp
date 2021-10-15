#include "Paddle.h"
#include <iostream>

/// This is the Paddle constructor
/// 
/// The paddle is a rectangle object that moves left and right at the bottom of the screen according to player input.
/// @param SceneManager*, SceneNode* -- Pass all of these by reference when instantiating the paddle.
/// @note Set the paddles's properties in here. Properties include height, width, paddleSpeed, screenWidth.
Paddle::Paddle(Ogre::SceneManager* scnMgr, Ogre::SceneNode* paddleNode)
{
	height = 0.5;
	width = 3; 
	paddleSpeed = 15;
	screenWidth = 16;
	SetSceneNode(paddleNode);


	Ogre::ManualObject* PaddleObject = NULL;
	PaddleObject = scnMgr->createManualObject("Triangle");
	PaddleObject->setDynamic(false);
	PaddleObject->begin("FlatVertexColour",
		Ogre::RenderOperation::OT_TRIANGLE_LIST);
	PaddleObject->position(0, 0, 0);
	PaddleObject->colour(1, 0.5, 0);
	PaddleObject->position(width, 0, 0);
	PaddleObject->colour(1, 0, 0);
	PaddleObject->position(width, height, 0);
	PaddleObject->colour(1, 0, 0);
	PaddleObject->position(0, height, 0);
	PaddleObject->triangle(0, 1, 2);
	PaddleObject->triangle(0, 2, 3);

	PaddleObject->end();

	paddleNode->attachObject(PaddleObject);

	paddleNode->translate(Ogre::Vector3(0, -5, 0));


	scnMgr->getRootSceneNode()->addChild(this->GetSceneNode());
	

}

/// This is the BoundChecking function
/// 
/// This checks the paddle's position against the x limits of the screen and ensures that the paddle does not move off the screen. 
void Paddle::BoundsChecking()
{
	if (this->GetSceneNode()->getPosition().x <= (-screenWidth / 2))
	{
		this->GetSceneNode()->setPosition(-screenWidth / 2, this->GetSceneNode()->getPosition().y, this->GetSceneNode()->getPosition().z);

	}
	else if (this->GetSceneNode()->getPosition().x + width>= screenWidth / 2)
	{
		this->GetSceneNode()->setPosition(screenWidth / 2 - width, this->GetSceneNode()->getPosition().y, this->GetSceneNode()->getPosition().z);
	}
}

/// This is the frameStarted function
/// 
/// This calls boundsChecking every frame. 
/// It also translates the paddle according to its velocity. 
/// @note velocity is returned to 0 after moving every frame to ensure the paddle only moves while the player is inputting a direction.
bool Paddle::frameStarted(const Ogre::FrameEvent& evt)
{
	this->GetSceneNode()->translate(velocity * evt.timeSinceLastFrame);

	velocity = Ogre::Vector3(0,0,0);

	BoundsChecking();

	return true;
}
