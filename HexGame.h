//
// Created by kelvin cervan ruiz on 14/06/24.
//

#ifndef HEXGAME_H
#define HEXGAME_H
#include "Graph.h"

class HexGame {
    int board_size;
    const int R_VALUE = 0;
    const int B_VALUE = 1;
    const int I_VALUE = 2;

    void print_board(Board board) const;

public:
    HexGame(int);

    void start_game();
};


#endif //HEXGAME_H
