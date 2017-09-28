//
// Created by petro on 9/27/17.
//

#ifndef PACMAN_ENEMY_HPP
#define PACMAN_ENEMY_HPP

#include "Player.hpp"
#include <cstdlib>
#include <random>
#include <ctime>

class Enemy : public Player {

public:
    void ChangeDirection();
    bool IsAtPosition(int x, int y);
    explicit Enemy(int x = 0, int y = 0);
    bool operator==(Enemy& rhs)const;

public: //static data members
    static int MortalMode; // >0 - mortal; 0 - immortal
};


#endif //PACMAN_ENEMY_HPP
