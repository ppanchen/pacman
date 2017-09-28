//
// Created by petro on 9/27/17.
//

#ifndef PACMAN_REALPLAYER_HPP
#define PACMAN_REALPLAYER_HPP

#include "Player.hpp"

class RealPlayer: public Player {
    int Lifes;
public:
    explicit RealPlayer(int x = 0, int y = 0);
    void ChangeDirection(char dir);
    int GetLifes() const;
    bool DecreaseLifes();
};


#endif //PACMAN_REALPLAYER_HPP
