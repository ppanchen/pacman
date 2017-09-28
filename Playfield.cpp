//
// Created by petro on 9/27/17.
//

#include "Playfield.hpp"

Playfield::Playfield(std::string const &mapfile) : Score(0), EndOfGame(false) {
    std::ifstream filecontent (mapfile);
    std::string str;

    if (!filecontent) {
        std::cout << "Error while file reading!" << std::endl;
        exit(-1);
    }

    while (std::getline(filecontent, str))
        Map.push_back(str);

    filecontent.close();
    if (!ValidateMap()){
        std::cout << "Map is invalid!" << std::endl;
        exit(-1);
    }

    FillPlayers();
    InitNcurses();
    ClearMap();
    PrintMap();
    PrintPlayers();
}

Playfield::~Playfield() {
    endwin();
    for (Player *pl: Players) {
        delete pl;
    }
    Players.clear();
}

void Playfield::InitNcurses() {
    initscr();
    cbreak();
    noecho();
    start_color();
    curs_set(0);
    keypad(stdscr, true);
    timeout(1);
    init_color(COLOR_GREY, 224, 224, 224);
    init_pair(RPColor, COLOR_GREEN,   COLOR_BLACK);
    init_pair(EnemyColor, COLOR_RED,  COLOR_BLACK);
    init_pair(BonusColor, COLOR_CYAN, COLOR_BLACK);
    init_pair(MainColor, COLOR_WHITE, COLOR_BLACK);
    init_pair(ObstacleColor, COLOR_GREY, COLOR_GREY);
}

bool Playfield::ValidateMap() {
    int countOfExits = 0;
    int countOfRealPlayers = 0;
    int countOfEnemies = 0;

    for (auto str = Map.begin(); str != Map.end(); ++str){
        for (int j = 0; j < str->length(); j++) {
            int i = (int) (str - Map.begin());
            if (!((*str)[j] == ' ' || (*str)[j] != '*' ||\
                  (*str)[j] != 'E' || (*str)[j] != '0' || (*str)[j] != 'o' ))
                return false;
            if (i == 0 || j == 0 || j == str->length() - 1 || str + 1 == Map.end()) {
                if ((*str)[j] == ' ') {
                    countOfExits++;
                    ExitX = j;
                    ExitY = i;
                } else if ((*str)[j] != '*') {
                    return false;
                }
            } else {
                if ((*str)[j] == '0')
                    countOfRealPlayers++;
                else if ((*str)[j] == 'E')
                    countOfEnemies++;
            }
        }
    }

    if (countOfEnemies == 0 || countOfRealPlayers != 1 || countOfExits != 1)
        return false;
    int strlen = (*Map.begin()).length();
    for(auto str = Map.begin(); str != Map.end(); ++str){
        if (strlen != (*str).length())
            return false;
    }
    return true;
}


void Playfield::FillPlayers() {
    for (auto str = Map.begin(); str != Map.end(); ++str)
        for (int j = 0; j < str->length(); j++)
        {
            int i = (int)(str - Map.begin());
            if ((*str)[j] == '0')
                Players.insert(Players.begin(), static_cast<Player *>(new RealPlayer(j, i)));
            else if ((*str)[j] == 'E')
                Players.push_back(static_cast<Player *>(new Enemy(j, i)));
        }
}

void Playfield::ClearMap() {
    for (auto str = Map.begin(); str != Map.end(); ++str)
        for (int j = 0; j < str->length(); j++)
            if ((*str)[j] == ' ' || (*str)[j] == 'E')
                (*str)[j] = '.';
            else if ((*str)[j] == '0')
                (*str)[j] = ' ';
    (*(Map.begin() + ExitY))[ExitX] = ' ';
}

void Playfield::PrintMap() {
    for (auto str = Map.begin(); str != Map.end(); ++str)
        for (int j = 0; j < str->length(); j++)
        {
            int i = (int)(str - Map.begin());
            if ((*str)[j] == '*')
                attron(COLOR_PAIR(ObstacleColor));
            else if ((*str)[j] == 'o')
                attron(COLOR_PAIR(BonusColor));
            else
                attron(COLOR_PAIR(MainColor));
            mvprintw(i, j, "%c", (*str)[j]);
            attroff(COLOR_PAIR(ObstacleColor));
            attroff(COLOR_PAIR(MainColor));
            attroff(COLOR_PAIR(BonusColor));
        }
    mvprintw(Map.size(), 0, "Score: %i", Score);
    mvprintw(Map.size(), 20, "Lifes: %i", dynamic_cast<RealPlayer *>(Players[0])->GetLifes());
    refresh();
//    getch();
}

void Playfield::PrintPlayers() {
    try {
        attron(COLOR_PAIR(RPColor));
        auto rp = Players.begin();
        int x = dynamic_cast<RealPlayer *>(*rp)->GetX();
        int y = dynamic_cast<RealPlayer *>(*rp)->GetY();
        mvprintw(y, x, "%c", 'O');
        attroff(COLOR_PAIR(RPColor));
        if (Enemy::MortalMode)
            attron(COLOR_PAIR(BonusColor));
        else
            attron(COLOR_PAIR(EnemyColor));
        for (auto i = Players.begin() + 1; i != Players.end(); ++i){
            x = dynamic_cast<Enemy *>(*i)->GetX();
            y = dynamic_cast<Enemy *>(*i)->GetY();
            mvprintw(y, x, "%c", 'E');
        }
        attroff(COLOR_PAIR(EnemyColor));
        attroff(COLOR_PAIR(BonusColor));

    }
    catch (std::bad_cast& bc){
        endwin();
        std::cerr << "bad_cast caught: " << bc.what() << '\n';
        exit(3);
    }
    refresh();

}

char & Playfield::GetPointUnderPlayer(Player &pl){
    return (*(Map.begin() + pl.GetY()))[pl.GetX()];
}

bool Playfield::IsAtObstacle(Player &pl) {
    if (GetPointUnderPlayer(pl) == '*')
        return true;
    return false;
}

Player *Playfield::IsColision() {
    int x = (*Players.begin())->GetX();
    int y = (*Players.begin())->GetY();
    Enemy *en;

    for (auto pl = Players.begin() + 1; pl != Players.end() ; ++pl) {
        en = dynamic_cast<Enemy *>(*pl);
        if (en->IsAtPosition(x, y))
            return en;
    }
    return nullptr;
}

void Playfield::MakeStep() {
    Enemy *en;

    // Handle real player move
    auto *RP =  dynamic_cast<RealPlayer *>(*Players.begin());
    RP->Move();
    if (IsAtObstacle(*RP))
        RP->MoveBack();
    Player *col = IsColision();
    if (col && !Enemy::MortalMode) {
        ResetGame();
    }
    else if (col && Enemy::MortalMode){
        (dynamic_cast<Enemy *>(col))->ChangeDirection();
        col->ResetPlayer();
        Score += 20;
    }
    char &c = GetPointUnderPlayer(*RP);
    if (c == '.'){
        Score++;
        c = ' ';
    }
    else if (c == 'o'){
        Enemy::MortalMode = 100 + 1;
        c = ' ';
    }

    // handle enemy move
    for (auto pl = Players.begin() + 1; pl != Players.end() ; ++pl) {
        en = dynamic_cast<Enemy *>(*pl);
        en->Move();
        if (IsAtObstacle(*en)) {
            en->MoveBack();
            en->ChangeDirection();
        }
        col = IsColision();
        if (*(dynamic_cast<Enemy *>(col)) == *en) {
            if (col && !Enemy::MortalMode) {
                ResetGame();
            }
            else if (col && Enemy::MortalMode)
                Score += 20;
                en->ChangeDirection();
                col->ResetPlayer();
        }
    }
    if ((RP->GetX() == ExitX && RP->GetY() == ExitY) || !(RP->GetLifes()))
        EndOfGame = true;
    Enemy::MortalMode = Enemy::MortalMode == 0 ? Enemy::MortalMode : Enemy::MortalMode - 1;
}


void Playfield::ResetGame(){
    PrintMap();
    attron(COLOR_PAIR(EnemyColor));
    for (auto pl = Players.begin(); pl != Players.end() ; ++pl) {
        if (pl != Players.begin()){
            mvprintw((*pl)->GetY(), (*pl)->GetX(), "%c", 'E');
            (dynamic_cast<Enemy *>(*pl))->ChangeDirection();
        }
        (*pl)->ResetPlayer();
    }
    attroff(COLOR_PAIR(EnemyColor));
    dynamic_cast<RealPlayer *>(Players[0])->DecreaseLifes();
    dynamic_cast<RealPlayer *>(Players[0])->ChangeDirection(-1);
    if (!dynamic_cast<RealPlayer *>(Players[0])->GetLifes())
        return ;
    PauseGame(0, Map.size(), "You died, press space to continue!");
}

bool Playfield::ReadInput(){
    char key[2];
    wgetstr(stdscr, key);

    RealPlayer *RealPl = dynamic_cast<RealPlayer *>(Players[0]);
    switch (key[0]){
        case 'e' :
            EndOfGame = true;
            break;
        case 'q' :
            endwin();
            exit(0);
            break;
        case 'w' :
            RealPl->ChangeDirection(1);
            break;
        case 'a' :
            RealPl->ChangeDirection(2);
            break;
        case 's' :
            RealPl->ChangeDirection(3);
            break;
        case 'd' :
            RealPl->ChangeDirection(0);
            break;
        case ' ':
            PauseGame(0, Map.size());
            break;
        default:
            break;
    }
}

std::vector<std::string> const & Playfield::GetMap() const {
    return Map;
}

bool Playfield::GetEnd() const {
    return EndOfGame;
}
