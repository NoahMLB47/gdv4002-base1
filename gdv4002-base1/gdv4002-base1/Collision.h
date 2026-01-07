#pragma once

class Collision {

public:

    struct Circle {
        float x, y;      // center position
        float radius;
    };

    Collision();
    ~Collision();

    // static so callers don't need an instance
    static bool checkCollision(const Circle& a, const Circle& b);
private:
};
