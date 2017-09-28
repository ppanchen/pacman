//
// Created by  petro on 9/27/17.
//

#ifndef PACMAN_PLAYER_HPP
#define PACMAN_PLAYER_HPP

#include "string"

class Player {
protected:
    const int           StartX;
    const int           StartY;
    int                 X;
    int                 Y;
    char                Direction;     // 0 - right; 1 - up; 2 - left; 3 - down

public:
    int                 GetX() const;
    int                 GetY() const;
    void                Move();
    void                MoveBack();
    void                ResetPlayer();
    virtual             ~Player();

protected:
    explicit            Player(int x = 0, int y = 0);
};


#endif //PACMAN_PLAYER_HPP
