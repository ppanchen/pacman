//
// Created by  petro on 9/27/17.
//

#ifndef PACMAN_PLAYER_HPP
#define PACMAN_PLAYER_HPP


class Player {
protected:
    int X;
    int Y;
    char Direction; // 1 - right; 2 - up; 3 - left; 4 - down
    virtual bool Move() = 0;
    virtual void ChangeDirection() = 0;
};


#endif //PACMAN_PLAYER_HPP
