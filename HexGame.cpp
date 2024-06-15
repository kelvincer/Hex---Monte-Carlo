//
// Created by kelvin cervan ruiz on 14/06/24.
//

#include "HexGame.h"

#include <thread>

#include "Graph.h"
#include "HexSimulation.h"

constexpr int num_simulations = 500;

HexGame::HexGame(int board_size): board_size(board_size) {
}


void HexGame::start_game() {
    Graph graph(board_size);
    HexGamer hex_gamer = HexGamer(graph);

    char player_one, player_two;
    cout << "Welcome to Hex game. Choose your color Red(enter R) or Blue(enter B): ";
    cin >> player_one;
    if (player_one == 'R') {
        player_two = 'B';
    } else {
        player_two = 'R';
    }
    cout << "Player one: " << player_one << ", player two: " << player_two << endl;

    int input_x, input_y;

    bool red_turn = player_one == 'R';

    // Print board
    print_board(graph.get_board());

    bool is_computer_turn = false;

    // Loop of the game
    while (true) {
        if (is_computer_turn) {
            Node node = hex_gamer.monte_carlo_move(num_simulations);
            input_x = node.x + 1;
            input_y = node.y + 1;
        } else {
            if (red_turn) {
                cout << "Red(R) enter a position (i j): ";
                cin >> input_x >> input_y;
            } else {
                cout << "Blue(B) enter a position (i j): ";
                cin >> input_x >> input_y;
            }
        }
        is_computer_turn = !is_computer_turn;
        char s = red_turn ? 'X' : 'O';
        int x = input_x - 1, y = input_y - 1;

        cout << endl << "next position: " << x << ", " << y << endl;

        if (graph.get_board()[x][y] != -1 || x < 0 || x > board_size || y < 0 || y > board_size) {
            cout << endl << "This position is invalid!" << endl;
            is_computer_turn = !is_computer_turn;
            continue;
        }

        graph.set_movement(x, y, s);

        print_board(graph.get_board());

        auto result = graph.get_winner();

        if (result.second) {
            cout << "Winner: " << result.first << endl;
            break;;
        }

        if (is_computer_turn) {
            cout << "Computing next computer movement..." << endl;
        }

        red_turn = !red_turn;
    }
}

void HexGame::print_board(Board board) const {
    cout << endl;

    int h = 0;
    int l = 1;
    for (int j = 0; j < board_size; j++) {
        // Print first node
        int i = 0;
        if (board[i][j] == -1) {
            cout << "•";
        } else if (board[i][j] == R_VALUE) {
            cout << "X";
        } else if (board[i][j] == I_VALUE) {
            cout << "I";
        } else {
            cout << "O";
        }
        // Print next rows of nodes
        i++;
        for (; i < board_size; i++) {
            if (board[i][j] == -1) {
                cout << " - " << "•";
            } else if (board[i][j] == R_VALUE) {
                cout << " - " << "X";
            } else if (board[i][j] == I_VALUE) {
                cout << " - " << "I";
            } else {
                cout << " - " << "O";
            }
        }
        cout << endl;
        for (int j = 0; j < h + 1; j = j + 1) {
            cout << " ";
        }
        if (j == board_size - 1) {
            break;
        }

        // Print connections between nodes
        h += 2;
        cout << "\\ ";
        for (int i = 0; i < board_size * 2 - 2; i++) {
            cout << (i % 2 == 0 ? "/ " : "\\ ");
        }
        cout << endl;
        for (int j = 0; j < l + 1; j = j + 1)
            cout << " ";
        l += 2;
    }
    cout << endl;
}
