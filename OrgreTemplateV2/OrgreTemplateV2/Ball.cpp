#include "Ball.h"


/// This is the Ball constructor
/// 
/// The ball is a rectangle object that bounces around the screen.
/// @param SceneManager*, SceneNode*, Paddle* -- Pass all of these by reference when instantiating the ball.
/// @note Set the ball's properties in here. Properties include height, width, ballSpeed, screenWidth, ballScore, 
/// @note the ball's x velocity is set higher than its y velocity to produce a more challenging trajectory. 
/// ballLives, and velocity. 
Ball::Ball(SceneManager* scnMgr, Ogre::SceneNode* ballNode, Paddle* paddleReference)
{
	height = 1;
	width = 1;
	ballSpeed = 10;
	screenWidth = 16;
	ballScore = 0;
	ballLives = 2;
	velocity = Ogre::Vector3(ballSpeed, ballSpeed * 0.7, 0);
	SetSceneNode(ballNode);
	paddleRef = paddleReference;



	Ogre::ManualObject* BallObject = NULL;
	BallObject = scnMgr->createManualObject("Triangle2");
	BallObject->setDynamic(false);
	BallObject->begin("FlatVertexColour",
		Ogre::RenderOperation::OT_TRIANGLE_LIST);
	BallObject->position(0, 0, 0);
	BallObject->colour(1, 0.5, 0);
	BallObject->position(width, 0, 0);
	BallObject->colour(1, 0, 0);
	BallObject->position(width, height, 0);
	BallObject->colour(0, 1, 0);
	BallObject->position(0, height, 0);
	BallObject->triangle(0, 1, 2);
	BallObject->triangle(0, 2, 3);

	BallObject->end();

	ballNode->attachObject(BallObject);

	ballNode->translate(Ogre::Vector3(0, 4, 0));


	scnMgr->getRootSceneNode()->addChild(this->GetSceneNode());


}

/// This is the BoundsChecking function.
/// 
/// This checks the ball's position against the sides, top, and bottom of the screen. 
/// It also checks using the CollisionManager for collision against the paddle.
void Ball::BoundsChecking()
{
	// sides checking
	if (this->GetSceneNode()->getPosition().x <= (-screenWidth / 2) || this->GetSceneNode()->getPosition().x + width >= screenWidth / 2)
	{
		ReboundSides();
	}
	// top checking
	if (this->GetSceneNode()->getPosition().y >= 5)
	{
		velocity.y = -velocity.y;
		this->GetSceneNode()->setPosition(this->GetSceneNode()->getPosition().x, 4.9, this->GetSceneNode()->getPosition().z);
	}
	// bottom checking
	if (this->GetSceneNode()->getPosition().y <= -6)
	{
		HitBottom();
	}
	if (CollisionManager::AABBCollisionCheck(paddleRef, this))
	{
		ReboundPaddle();
	}


}

/// This is the HitBottom function.
/// 
/// This is called when the BoundCheck determines the ball has reached the bottom of the screen.
/// It reversed the ball's speed, moves the ball to a safe position to avoid repeat collisions, and decrements the ball's lives. 
void Ball::HitBottom()
{
	velocity.y = -velocity.y;
	this->GetSceneNode()->setPosition(this->GetSceneNode()->getPosition().x, 3, this->GetSceneNode()->getPosition().z);
	ballLives--;
}

/// This is the ReboundPaddle function.
/// 
/// This is called when the CollisionManager determines that the ball has collided with the paddle.
/// It reverses the ball's speed, moves the ball to a safe position to avoid repeat collisions, and increments the ball's score.
void Ball::ReboundPaddle()
{
	velocity.y = -velocity.y;
	this->GetSceneNode()->setPosition(this->GetSceneNode()->getPosition().x, paddleRef->GetSceneNode()->getPosition().y + paddleRef->GetHeight(), this->GetSceneNode()->getPosition().z);
	ballScore++;
}

/// This is the ReboundSides function.
/// 
/// This is called when the ball reaches the max or minimum screen bounds on the x axis. 
///  It simply reverses the ball's x velocity. 
void Ball::ReboundSides()
{
	velocity.x = -velocity.x;
}

/// This is the frameStarted function. 
/// 
/// This calls the translate function every frame to move the ball according to it's velocity.  
/// It also calls the BoundsChecking function every frame. 
/// @note translate is adjusted by evt.timeSinceLastFrame to ensure consistent speed across frame rates. 
bool Ball::frameStarted(const Ogre::FrameEvent& evt)
{
	this->GetSceneNode()->translate(velocity * evt.timeSinceLastFrame);
	BoundsChecking();

	return true;
}
