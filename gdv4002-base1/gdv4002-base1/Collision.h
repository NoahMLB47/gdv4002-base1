#pragma once

class Collision {

public:
    struct Box {
        float x, y;      // top-left position
        float width;
        float height;
    };

    Collision();
    ~Collision();

    // static so callers don't need an instance
    static bool checkCollision(const Box& a, const Box& b);
private:
};
