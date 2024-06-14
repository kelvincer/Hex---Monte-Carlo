//
// Created by kelvin cervan ruiz on 12/06/24.
//

#include "HexGamer.h"
#include <random>
#include <map>
#include "Dijkstra.h"
#include <vector>

template<typename KeyType, typename ValueType>
std::pair<KeyType, ValueType> get_max(const std::unordered_map<KeyType, ValueType> &x) {
    using pairtype = std::pair<KeyType, ValueType>;
    return *std::max_element(x.begin(), x.end(), [](const pairtype &p1, const pairtype &p2) {
        return p1.second < p2.second;
    });
}

HexGamer::HexGamer(Graph graph): graph(graph) {
}

vector<Node> HexGamer::get_legal_moves(Graph &graph) {
    vector<Node> legal_moves;
    for (int i = 0; i < graph.get_size(); i++) {
        for (int j = 0; j < graph.get_size(); j++) {
            if (graph.get_board()[i][j] == -1) {
                legal_moves.push_back(Node(i, j));
            }
        }
    }

    return legal_moves;
}

void HexGamer::make_move(int x, int y, Graph &graph) {
    if (graph.get_board()[x][y] == -1) {
        //cout << endl << "Player: " << current_player << endl;
        graph.set_movement(x, y, current_player);
        current_player = current_player == 'X' ? 'O' : 'X';
    }
}

pair<char, bool> HexGamer::is_winner(Graph &graph) {
    auto winner = graph.get_winner();
    return winner;
}

char HexGamer::simulate_random_game(Graph &graph) {
    while (!is_winner(graph).second) {
        Node node = get_random_legal_node(graph);
        make_move(node.x, node.y, graph);
    }
    return current_player;
}

Node HexGamer::monte_carlo_move(int num_simulations) {
    vector<Node> legal_moves = get_legal_moves(graph);
    std::unordered_map<Node, int> move_with_counts;
    for (auto node: legal_moves) {
        for (int i = 0; i < num_simulations; i++) {
            auto graph_copy = graph;
            graph_copy.initialize_game();
            //graph_copy.create_board();
            auto result = simulate_random_game(graph_copy);
            if (result == 'O') {
                //std::cout << "winner: " << node << std::endl;
                move_with_counts[node] += 1;
            } else {
                //cout << "loser: " << node << endl;
            }
        }
    }
    return get_max(move_with_counts).first;
}

int HexGamer::get_random_index(size_t size) {
    random_device rd;
    default_random_engine engine{rd()};
    uniform_int_distribution<> distribution{0, static_cast<int>(size - 1)};
    return distribution(engine);
}

Node HexGamer::get_random_legal_node(Graph &graph) {
    auto legal_moves = get_legal_moves(graph);
    auto legal_move = legal_moves[get_random_index(legal_moves.size())];
    return legal_move;
}
