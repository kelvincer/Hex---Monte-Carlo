//
// Created by kelvin cervan ruiz on 12/06/24.
//

#include "HexSimulation.h"
#include <random>
#include "Graph.h"
#include <vector>
#include <thread>
#include <unordered_map>

template<typename KeyType, typename ValueType>
std::pair<KeyType, ValueType> get_max(const std::unordered_map<KeyType, ValueType> &x) {
    using pairtype = std::pair<KeyType, ValueType>;
    return *std::max_element(x.begin(), x.end(), [](const pairtype &p1, const pairtype &p2) {
        return p1.second < p2.second;
    });
}

template<size_t N>
HexSimulation<N>::HexSimulation(Graph<N> &graph): graph(graph) {
}

template<size_t N>
vector<Node> HexSimulation<N>::get_legal_moves(Graph<N> &graph) {
    vector<Node> legal_moves;
    for (int j = 0; j < graph.get_size(); j++) {
        for (int i = 0; i < graph.get_size(); i++) {
            if (graph.get_board()[i][j] == -1) {
                legal_moves.push_back(Node(i, j));
            }
        }
    }

    return legal_moves;
}

template<size_t N>
void HexSimulation<N>::make_move(int x, int y, Graph<N> &graph) {
    if (graph.get_board()[x][y] == -1) {
        graph.current_player = graph.current_player == 'X' ? 'O' : 'X';
        graph.set_movement(x, y, graph.current_player);
    }
}

template<size_t N>
pair<char, bool> HexSimulation<N>::is_winner(Graph<N> &graph) {
    auto winner = graph.get_winner();
    return winner;
}

template<size_t N>
char HexSimulation<N>::simulate_random_game(Graph<N> &graph) {
    auto win_pair = is_winner(graph);
    while (!win_pair.second) {
        Node node = get_random_legal_node(graph);
        make_move(node.x, node.y, graph);
        win_pair = is_winner(graph);
    }
    return win_pair.first;
}

template<size_t N>
void HexSimulation<N>::function(Node node, unordered_map<Node, int> &map, Graph<N> graph, int num_simulations) {
    for (int i = 0; i < num_simulations; i++) {
        auto result = simulate_random_game(graph);
        if (result == 'R') {
            map[node] += 1;
        }
    }
}

/*template<size_t N>
Node HexSimulation<N>::monte_carlo_move(int num_simulations) {
    vector<Node> legal_moves = get_legal_moves(graph);
    unordered_map<Node, int> move_with_counts;
    std::vector<future<void> > some_threads;
    for (auto node: legal_moves) {
        some_threads.push_back(async(launch::async, &HexSimulation<N>::function, this, node, ref(move_with_counts),
                                     graph,
                                     num_simulations));
    }
    for (auto &t: some_threads) t.wait();
    return get_max(move_with_counts).first;
}*/

template<size_t N>
Node HexSimulation<N>::monte_carlo_move(int num_simulations) {
    vector<Node> legal_moves = get_legal_moves(graph);
    unordered_map<Node, int> move_with_counts;
    std::vector<std::thread> some_threads;
    for (auto node: legal_moves) {
        some_threads.push_back(thread(&HexSimulation::function, this, node, ref(move_with_counts), graph,
                                      num_simulations));
    }
    for (auto &t: some_threads) t.join();
    return get_max(move_with_counts).first;
}

template<size_t N>
int HexSimulation<N>::get_random_index(size_t size) {
    random_device rd;
    default_random_engine engine{rd()};
    uniform_int_distribution<> distribution{0, static_cast<int>(size - 1)};
    return distribution(engine);
}

template<std::size_t N>
Node HexSimulation<N>::get_random_legal_node(Graph<N> &graph) {
    auto legal_moves = get_legal_moves(graph);
    auto legal_move = legal_moves[get_random_index(legal_moves.size())];
    return legal_move;
}

template class HexSimulation<7>;
template class HexSimulation<11>;
