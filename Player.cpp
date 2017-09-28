//
// Created by petro on 9/27/17.
//

#include "Player.hpp"

Player::Player(int x, int y) : X(x), StartX(x), Y(y), StartY(y), Direction(-1) {}
Player::~Player(){};

void    Player::Move(){
    switch (Direction) {
        case 0:
            X++;
            break;
        case 1:
            Y--;
            break;
        case 2:
            X--;
            break;
        case 3:
            Y++;
            break;
        default:
            return;
    }
}

void    Player::MoveBack(){
    switch (Direction) {
        case 0:
            X--;
            break;
        case 1:
            Y++;
            break;
        case 2:
            X++;
            break;
        case 3:
            Y--;
            break;
        default:
            return;
    }
}

void    Player::ResetPlayer() {
    X = StartX;
    Y = StartY;
}

int Player::GetX() const {
    return X;
}

int Player::GetY() const {
    return Y;
}