#include "Collision.h"

Collision::Collision() {}
Collision::~Collision() {}

bool Collision::checkCollision(const Box& a, const Box& b)
{
    // a.x,a.y are top-left; width/height positive
    return (a.x < b.x + b.width &&
            a.x + a.width > b.x &&
            a.y < b.y + b.height &&
            a.y + a.height > b.y);
}