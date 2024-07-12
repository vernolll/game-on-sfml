#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

extern float offsetX, offsetY;
extern bool pick_up;

class PLAYER {
public:
    float dx, dy;
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    float currentFrame;

    PLAYER(Texture& image);
    void update(float time);
    void Collision(int dir);
};