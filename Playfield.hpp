//
// Created by petro on 9/27/17.
//

#ifndef PACMAN_PLAYFIELD_HPP
#define PACMAN_PLAYFIELD_HPP

#include "Enemy.hpp"
#include "RealPlayer.hpp"
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <ncurses.h>
#include <iostream>
#include <typeinfo>


void PauseGame(int x, int y, char *message = 0);

class Playfield {
    std::vector<Player *> Players;
    std::vector<std::string> Map;
    int ExitX;
    int ExitY;
    bool EndOfGame;
    int Score;

    enum Colors{
        MainColor,
        RPColor,
        BonusColor,
        ObstacleColor,
        EnemyColor,
        COLOR_GREY,
    };

private:                                    //private methods
    bool ValidateMap();
    void FillPlayers();
    void ClearMap();
    bool IsAtObstacle(Player &pl);
    Player *IsColision();
    char &GetPointUnderPlayer(Player &pl);
    void InitNcurses();
    void ResetGame();

public:
    explicit Playfield(std::string const &mapfile);
    bool ReadInput();
    ~Playfield();
    void PrintPlayers();
    void PrintMap();
    void MakeStep();
    bool GetEnd() const;
    std::vector<std::string> const & GetMap() const;
};


#endif //PACMAN_PLAYFIELD_HPP
