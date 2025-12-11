#pragma once

class Collision {

public:
    struct Box {
        float x, y;      // top-left position
        float width;
        float height;
    };

    struct Circle {
        float x, y;      // center position
        float radius;
    };

    Collision();
    ~Collision();

    // static so callers don't need an instance
    static bool checkCollision(const Box& a, const Box& b);
    static bool checkCollision(const Circle& a, const Circle& b);
private:
};
