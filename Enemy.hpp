//
// Created by petro on 9/27/17.
//

#ifndef PACMAN_ENEMY_HPP
#define PACMAN_ENEMY_HPP

#include "Player.hpp"

class Enemy : public Player {
    static int MortalMode; // >0 - mortal; 0 - immortal
public:
    bool Move();
    void ChangeDirection();
    bool IsAtPosition(int x, int y);
    void SetMortalMode(int mm);
    int GetMortalMode() const;
};


#endif //PACMAN_ENEMY_HPP
