#include "CollisionManager.h"

/// This is the AABBCollisionCheck function.
/// 
/// This does a rect/rect check on two gameobjects, using their positions and height and width to determine if an overlap is taking place.
/// If there is an overlap, it returns true. 
/// @note Call this function in frameStarted of an object to test for collision against another object. 
bool CollisionManager::AABBCollisionCheck(GameObject* objectA, GameObject* objectB)
{
    const float a_xPos = objectA->GetSceneNode()->getPosition().x;
    const float a_yPos = objectA->GetSceneNode()->getPosition().y;
    const float a_width = objectA->GetWidth();
    const float a_height = objectA->GetHeight();
 
	const float b_xPos = objectB->GetSceneNode()->getPosition().x;
	const float b_yPos = objectB->GetSceneNode()->getPosition().y;
	const float b_width = objectB->GetWidth();
	const float b_height = objectB->GetHeight();
    

    if (a_xPos < b_xPos + b_width &&
        a_xPos + a_width > b_xPos &&
        a_yPos < b_yPos + b_height &&
        a_yPos + a_height > b_yPos
        )
    {
        return true;
    }
    else
    return false;
}
