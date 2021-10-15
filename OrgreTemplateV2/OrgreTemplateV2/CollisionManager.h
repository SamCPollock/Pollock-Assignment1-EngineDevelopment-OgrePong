#pragma once

#include "Ogre.h"
#include "GameObject.h"

class CollisionManager
{
	public: 
	static bool AABBCollisionCheck(GameObject* objectA, GameObject* objectB);
};

