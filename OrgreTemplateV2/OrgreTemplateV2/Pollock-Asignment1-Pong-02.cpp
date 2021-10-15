///Pong in OGRE
///@note HOW TO PLAY: Move Paddle using A and D 
/// Earn points by bouncing the ball against the paddle
/// Lose lives by letting the ball pass the paddle and hitting the bottom
/// Made by Sam Pollock for Game Engine Development (Taught by Hooman Salamat) at George Brown College, fall 2021.

#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include "Ball.h"
#include "Paddle.h"

#include <iostream>

using namespace Ogre;
using namespace OgreBites;

Paddle* m_Paddle;
Ball* m_Ball;


Ogre::Real m_Angle = 0.0;
int lives = 3;
int score = 0;


OgreBites::TrayManager* mTrayMgr;


/// This is a LabelFrameListener class
/// 
/// this goes every frame to update labels.
class LabelsFrameListener : public Ogre::FrameListener
{
private:
	OgreBites::Label* _livesLabel;
	OgreBites::Label* _scoreLabel;
	OgreBites::Label* _timeLabel;


public:
	
	/// This is a LabelFrameListener constructor
	/// 
	/// It takes three labels as parameters: lives, score, and time per update. 
	LabelsFrameListener(OgreBites::Label* livesLabel, OgreBites::Label* scoreLabel, OgreBites::Label* tpuLabel) 
	{
		_livesLabel = livesLabel;
		_scoreLabel = scoreLabel;
		_timeLabel = tpuLabel;

	}
	/// FrameStarted function
	/// 
	/// 
	/// This updates the captions for lives and score, as well as the time since last frame.
	/// 
	bool frameStarted(const Ogre::FrameEvent& evt)
	{
		_livesLabel->setCaption("Lives: " + std::to_string(m_Ball->ballLives));
		_scoreLabel->setCaption("Score: " + std::to_string(m_Ball->ballScore));
		_timeLabel->setCaption(std::to_string(evt.timeSinceLastFrame));
		return true;

	}
};


/// This is a PongAssignment class
/// 
///
class PongAssignment
	: public ApplicationContext
	, public InputListener
{
private:
	SceneManager* scnMgr;
	Root* root;
public:
	PongAssignment();
	virtual ~PongAssignment() {}

	void setup();
	void createScene();
	void createCamera();
	bool keyPressed(const KeyboardEvent& evt);
	void createFrameListener();


	OgreBites::TrayListener mTrayListener;

	OgreBites::Label* mInfoLabel;
	OgreBites::Label* mTpuLabel;
	OgreBites::Label* mTpu;
	OgreBites::Label* mScoreLabel;
	OgreBites::Label* mLivesLabel;
};


PongAssignment::PongAssignment()
	: ApplicationContext("Pollock-PongAssignment")
{
}

/// This is a setup function
/// 
/// This calls the functions to setup the game, including the base setup(), adding scene manager, creating the scene, creating the camera, and creating the frame listeners. 
void PongAssignment::setup()
{
	// do not forget to call the base first
	ApplicationContext::setup();
	addInputListener(this);


	// get a pointer to the already created root
	root = getRoot();
	scnMgr = root->createSceneManager();

	// register our scene with the RTSS
	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);
	createScene();
	createCamera();
	createFrameListener();
}

/// This is the createScene function.
/// 
/// This creates the lights and any other objects and UI in the scene. 
void PongAssignment::createScene()
{

	//! [turnlights]
	scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
	//! [turnlights]

	//! [newlight]
	//
	Light* light1 = scnMgr->createLight("Light1");
	light1->setType(Ogre::Light::LT_POINT);
	// Set Light Color
	light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
	// Set Light Reflective Color
	light1->setSpecularColour(1.0f, 0.0f, 0.0f);
	// Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
	light1->setAttenuation(10, 0.5, 0.045, 0.0);

	//
	Entity* lightEnt = scnMgr->createEntity("LightEntity", "sphere.mesh");
	SceneNode* lightNode = scnMgr->createSceneNode("LightNode");
	lightNode->attachObject(lightEnt);
	lightNode->attachObject(light1);
	lightNode->setScale(0.01f, 0.01f, 0.01f);


	scnMgr->getRootSceneNode()->addChild(lightNode);
	//! [newlight]



	//! [lightpos]
	lightNode->setPosition(0, 4, 10);
	//! [lightpos]



	m_Paddle = new Paddle(scnMgr, scnMgr->createSceneNode("Paddle1"));


	m_Ball = new Ball(scnMgr, scnMgr->createSceneNode("Ball1"), m_Paddle);

	OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());
	scnMgr->addRenderQueueListener(mOverlaySystem);
	addInputListener(mTrayMgr);


	//mTrayMgr->showLogo(TL_TOPRIGHT);
	mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
	mTrayMgr->toggleAdvancedFrameStats();

	mTpuLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "Time/Update", "Time/Update:", 150);
	mTpu = mTrayMgr->createLabel(TL_TOPRIGHT, "tpu", "0", 150);
	mScoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Score", "Score: " + std::to_string(score), 100);
	mLivesLabel = mTrayMgr->createLabel(TL_TOP, "Lives", "Lives: " + std::to_string(lives), 100);


}

/// This is the createCamera function.
/// 
/// It creates the camera in the scene and sets its initial position and characteristics. 
void PongAssignment::createCamera()
{

	//! [camera]
	SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	// create the camera
	Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	camNode->setPosition(0, 0, 15);
	camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);

	//! [camera]
}

/// This is a keyPressed function.
/// 
/// It checks for keyboard inputs and sets the velocity of the paddle accordingly. 
/// @note more cases can be added to introduce additional inputs for the player. 
bool PongAssignment::keyPressed(const KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_ESCAPE:
		getRoot()->queueEndRendering();
		break;
	case 'a':
		m_Paddle->SetVelocity(Ogre::Vector3(-m_Paddle->paddleSpeed, 0, 0));
		break;
	case 'd':
		m_Paddle->SetVelocity(Ogre::Vector3(m_Paddle->paddleSpeed, 0, 0));
		break;
	default:
		break;
	}
	return true;
}

/// This is the createFrameListener function
/// 
/// It adds each a frame listener for each game object. It also adds a frame listenr for the UI. 
void PongAssignment::createFrameListener()
{

	Ogre::FrameListener* PaddleFrameListener = m_Paddle;
	mRoot->addFrameListener(PaddleFrameListener);

	Ogre::FrameListener* BallFrameListener = m_Ball;
	mRoot->addFrameListener(BallFrameListener);

	Ogre::FrameListener* FrameListener3 = new LabelsFrameListener(mLivesLabel, mScoreLabel, mTpu);
	mRoot->addFrameListener(FrameListener3);




}

/// This is the main function.
/// 
/// This runs at compile to instantiate the game application. 
int main(int argc, char** argv)
{
	try
	{
		PongAssignment app;
		app.initApp();
		app.getRoot()->startRendering();
		app.closeApp();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
		return 1;
	}

	return 0;
}

//! [fullsource]
