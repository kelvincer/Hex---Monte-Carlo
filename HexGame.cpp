//
// Created by kelvin cervan ruiz on 14/06/24.
//

#include "HexGame.h"
#include <thread>
#include "Graph.h"
#include "HexSimulation.h"

constexpr int num_simulations = 1;

HexGame::HexGame(int board_size): board_size(board_size) {
}

template<size_t N>
void start_playing(Graph<N> &graph, HexSimulation<N> &hex_simulation, int board_size) {
    char player_one, player_two;
    cout << "Choose your color Red(enter R) or Blue(enter B): ";
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
    graph.print_board(graph.get_board());

    bool is_computer_turn = false;

    // Loop of the game
    while (true) {
        if (is_computer_turn) {
            cout << "Computing next movement..." << endl;
            Node node = hex_simulation.monte_carlo_move(num_simulations);
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
        char s = red_turn ? 'X' : 'O';
        int x = input_x - 1, y = input_y - 1;

        if (is_computer_turn)
            cout << "Computer movement: " << input_x << " " << input_y << endl;

        if (graph.get_board()[x][y] != -1 || x < 0 || x > board_size || y < 0 || y > board_size) {
            cout << endl << "This position is invalid!" << endl;
            continue;
        }

        graph.set_movement(x, y, s);

        graph.print_board(graph.get_board());

        auto result = graph.get_winner();

        if (result.second) {
            cout << "Winner: " << result.first << endl;
            break;;
        }
        is_computer_turn = !is_computer_turn;
        red_turn = !red_turn;
    }
}

void HexGame::start_game() const {
    if (board_size == 7) {
        Graph<7> graph(7);
        auto hex_simulation = HexSimulation(graph);
        start_playing(graph, hex_simulation, 7);
    } else if (board_size == 11) {
        Graph<11> graph(11);
        auto hex_simulation = HexSimulation(graph);
        start_playing(graph, hex_simulation, 11);
    } else {
        cout << "Wrong board size. Please restart the game.";
    }
}
