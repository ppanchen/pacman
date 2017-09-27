//
// Created by petro on 9/27/17.
//

#ifndef PACMAN_REALPLAYER_HPP
#define PACMAN_REALPLAYER_HPP

#include "Player.hpp"

class RealPlayer: public Player {
public:
    bool Move();
    void ChangeDirection();
};


#endif //PACMAN_REALPLAYER_HPP
