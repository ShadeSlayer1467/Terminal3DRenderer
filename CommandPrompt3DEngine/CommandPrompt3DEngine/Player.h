#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    float x, y, angle;
    float speed, sensitivity;

    Player(float startX, float startY, float startAngle);

    void Rotate(float deltaAngle);
    void Move(float deltaX, float deltaY);
};

#endif // PLAYER_H
