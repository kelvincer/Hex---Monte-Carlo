#include "HexGame.h"

int main() {
    int board_size = 11;
    auto hex_game = HexGame(board_size);
    hex_game.start_game();
}
