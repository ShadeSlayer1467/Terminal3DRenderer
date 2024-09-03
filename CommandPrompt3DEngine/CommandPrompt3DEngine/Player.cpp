#include "Player.h"
#include "Constants.h"

Player::Player(float startX, float startY, float startAngle)
    : x(startX), y(startY), angle(startAngle), speed(5.0f), sensitivity(1.25f) {}

void Player::Rotate(float deltaAngle) {
    angle += deltaAngle * sensitivity;
    if (angle < 0.0f) angle += 2 * fPi;
    if (angle >= 2 * fPi) angle -= 2 * fPi;
}

void Player::Move(float deltaX, float deltaY) {
    x += deltaX;
    y += deltaY;
}
