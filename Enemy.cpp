//
// Created by petro on 9/27/17.
//

#include "Enemy.hpp"

int Enemy::MortalMode = 0;

Enemy::Enemy(int x, int y): Player(x, y){
    ChangeDirection();
}

void    Enemy::ChangeDirection() {
    char randDir = Direction;
    std::random_device rd;
    std::uniform_int_distribution<> uid(0, 3);

    while(randDir == Direction)
        randDir = static_cast<char>(uid(rd));
    Direction = randDir;
}

bool Enemy::IsAtPosition(int x, int y) {
    if (X == x && Y == y)
        return true;
    return false;
}

bool   Enemy::operator==(Enemy &rhs) const {
    if (!this)
        return false;
    if (this->X == rhs.X && this->StartX == rhs.StartX &&\
        this->Y == rhs.Y && this->StartY == rhs.StartY)
        return true;
    return false;
}
