#include <iostream>
#include "Playfield.hpp"

void PauseGame(int x, int y, char *message){
    int key;
    if (message)
        mvprintw(y, x, "%s", message);
    else
        mvprintw(y, x, "%s", "Pause, press space to continue!");
    while (true){
        key = wgetch(stdscr);
        if (key == ' ')
            break;
        else if (key == 'q'){
            endwin();
            exit(0);
        }
    }
    mvprintw(y, x, "%*s", message ? strlen(message) : strlen("Pause, press space to continue!"), " ");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Give a map file as argument" << std::endl;
        exit(1);
    }
    Playfield pf(argv[1]);

    pf.PrintMap();
    PauseGame(0, pf.GetMap().size(), "Welcome,\n"
                                     "w, a, s, d - for control\n"
                                     "space - for pause\n"
                                     "e - for end game\n"
                                     "q - for quit game\n"
                                     "Now, press a space for start\n"
                                     "Have a nice game!");
    clear();

    char i = 0;
    while (!pf.GetEnd()){
        if (i == 10){
            pf.MakeStep();
            pf.PrintMap();
            pf.PrintPlayers();
            i = 0;
        }
        pf.ReadInput();
        system("sleep 0.01s");
        i++;
    }
    PauseGame(0, pf.GetMap().size() + 1, "Game over, press space to exit");

    return 0;
}