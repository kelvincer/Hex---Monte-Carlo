//
// Created by kelvin cervan ruiz on 12/06/24.
//

#ifndef HEXGAMER_H
#define HEXGAMER_H

#include "Node.h"
#include <vector>
#include "Dijkstra.h"

using namespace std;

class HexGamer {
public:

    explicit HexGamer(Graph graph);

    vector<Node> get_legal_moves(Graph &graph);

    void make_move(int x, int y, Graph &graph);

    pair<char, bool> is_winner(Graph &graph);

    char simulate_random_game(Graph &graph);

    Node monte_carlo_move(int num_simulations);

private:
    Graph graph;
    char current_player = 'X';
    const int R_VALUE = 0; // Value for red on the board array
    const int B_VALUE = 1; // Value for blue on the board array
    Node get_random_legal_node(Graph &graph);

    int get_random_index(size_t size);
};


#endif //HEXGAMER_H
