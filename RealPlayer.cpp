//
// Created by petro on 9/27/17.
//

#include "RealPlayer.hpp"

RealPlayer::RealPlayer(int x, int y) : Player(x, y) {
    Lifes = 3;
}

void RealPlayer::ChangeDirection(char dir) {
    Direction = dir;
}

int RealPlayer::GetLifes() const {
    return Lifes;
}

bool RealPlayer::DecreaseLifes() {
    Lifes = Lifes == 0 ? Lifes : Lifes - 1;
}