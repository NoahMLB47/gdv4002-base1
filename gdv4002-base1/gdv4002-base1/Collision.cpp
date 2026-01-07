#include "Collision.h"
#include "Engine.h"

#include <cmath>

Collision::Collision() 
{

}

Collision::~Collision() 
{

}

bool Collision::checkCollision(const Circle& a, const Circle& b)
{
    // Calculate distance between centers
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float distanceSquared = dx * dx + dy * dy;
    
    // Check if distance is less than sum of radii
    float radiusSum = a.radius + b.radius;
    return distanceSquared < (radiusSum * radiusSum);
}