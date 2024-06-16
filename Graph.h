//
// Created by kelvin cervan ruiz on 12/06/24.
//

#ifndef DISJTRA_H
#define DISJTRA_H

#include <queue>
#include "Node.h"

using namespace std;
#define INF 0x3f3f3f3f

typedef pair<Node, int> iPair;
typedef unordered_map<Node, vector<iPair> > Adj;

template<std::size_t N>
class Graph {
    typedef array<array<int, N>, N> Board;

    int V;

    Adj adj_red;

    Adj adj_blue;

    vector<iPair> dist_red;
    vector<iPair> dist_blue;

    void initialize_dist();

    void update_cost(int x, int y, int w, Adj &adj);

    Board board{};
    const int R_VALUE = 0;
    const int B_VALUE = 1;
    const int I_VALUE = 2;
    unordered_map<Node, vector<Node> > connections;
    vector<Node> red_end_nodes;
    vector<Node> blue_end_nodes;
    vector<Node> red_nodes;
    vector<Node> blue_nodes;

public:
    explicit Graph(int V); // Constructor
    void initialize_game();

    void addEdge(Node u, Node v, int w);

    bool shortestPath(Node src, unordered_map<Node, vector<iPair> > adj, vector<iPair> dist, int color);

    iPair find_pair(Node node, vector<iPair> dist);

    void update_distance(iPair ipair, vector<iPair> &dist);

    int get_size() const;

    void create_board();

    Board get_board();

    void set_movement(int i, int y, char current_player);

    void update_graph(int x, int y, Adj &adj);

    vector<Node> get_all_nodes_of_red_from_same_row(vector<Node> &nodes, int y);

    vector<Node> get_all_nodes_of_blue_from_same_column(vector<Node> &nodes, int x);

    void add_edges();

    pair<char, bool> get_winner();

    void print_board(Board board);

    void print_map(unordered_map<Node, vector<iPair> > adj);

    void print_vector(vector<Node> vec);

    char current_player;
};

struct LessThanBySecond {
    bool operator()(const iPair &lhs, const iPair &rhs) const {
        return lhs.second > rhs.second;
    }
};

#endif //DISJTRA_H
