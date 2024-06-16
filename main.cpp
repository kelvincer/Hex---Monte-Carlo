#include "HexGame.h"
#include "HexSimulation.h"

int main() {
    int board_size;
    cout << "Welcome to Hex Game. Enter the size of the board, 7 o 11: ";
    cin >> board_size;
    auto hex_game = HexGame(board_size);
    hex_game.start_game();
}
