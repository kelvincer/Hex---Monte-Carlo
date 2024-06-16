//
// Created by kelvin cervan ruiz on 12/06/24.
//

#ifndef HEXGAMER_H
#define HEXGAMER_H

#include "Node.h"
#include <vector>
#include "Graph.h"

using namespace std;

template<size_t N>
class HexSimulation {
public:

    explicit HexSimulation(Graph<N> &graph);

    vector<Node> get_legal_moves(Graph<N> &graph);

    void make_move(int x, int y, Graph<N> &graph);

    pair<char, bool> is_winner(Graph<N> &graph);

    char simulate_random_game(Graph<N> &graph);

    void function(Node node, unordered_map<Node, int> &map, Graph<N> graph, int num_simulations);

    Node monte_carlo_move(int num_simulations);

private:
    Graph<N> &graph;

    const int R_VALUE = 0; // Value for red on the board array
    const int B_VALUE = 1; // Value for blue on the board array

    Node get_random_legal_node(Graph<N> &graph);

    int get_random_index(size_t size);
};

#endif //HEXGAMER_H
