//
// Created by kelvin cervan ruiz on 12/06/24.
//
#include "Graph.h"
#include "Node.h"
#include <thread>

template<size_t T>
using Board = typename Graph<T>::Board;

template<size_t N>
void Graph<N>::initialize_dist() {
    dist_blue.clear();
    dist_red.clear();
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist_red.push_back(make_pair(Node(i, j), INF));
            dist_blue.push_back(make_pair(Node(i, j), INF));
        }
    }
}

template<size_t N>
void Graph<N>::update_cost(int x, int y, int w, Adj &adj) {
    const auto node = Node(x, y);
    auto &edges = adj[node];
    for (auto it = edges.begin(); it != edges.end(); it++) {
        it->second = w;
    }
}

template<size_t N>
void Graph<N>::print_map(unordered_map<Node, vector<iPair> > adj) {
    cout << endl;
    for (auto r: adj) {
        cout << endl << r.first << ": ";
        for (auto e: r.second) {
            cout << e.first << ": " << e.second << ", ";
        }
    }
}

template<size_t N>
void Graph<N>::print_vector(vector<Node> vec) {
    cout << endl;
    for (auto v: vec) {
        cout << v << ", ";
    }
}

template<size_t N>
Graph<N>::Graph(int V) {
    this->V = V;
    create_board();
    initialize_game();
    add_edges();
}

template<size_t N>
void Graph<N>::initialize_game() {
    red_end_nodes.clear();
    blue_end_nodes.clear();
    for (int i = 0; i < V; i++)
        red_end_nodes.push_back(Node(i, V - 1));
    for (int j = 0; j < V; j++)
        blue_end_nodes.push_back(Node(V - 1, j));
}

template<size_t N>
void Graph<N>::addEdge(Node u, Node v, int w) {
    adj_blue[u].push_back(make_pair(v, w));
    adj_red[u].push_back(make_pair(v, w));
}

template<size_t N>
bool Graph<N>::shortestPath(Node src, unordered_map<Node, vector<iPair> > adj, vector<iPair> dist, int color) {
    priority_queue<iPair, vector<iPair>, LessThanBySecond> pq;
    pq.push(make_pair(src, 0));
    update_distance(make_pair(src, 0), dist);

    while (!pq.empty()) {
        Node u = pq.top().first;
        pq.pop();
        auto adjacent_nodes = adj[u];

        for (auto i = adjacent_nodes.begin(); i != adjacent_nodes.end(); ++i) {
            Node v = i->first;
            int weight = i->second;
            auto adj_v = adj[v];
            auto u_connection = find_if(adj_v.begin(), adj_v.end(), [u](iPair pair) { return u == pair.first; });
            if (weight != u_connection->second) {
                continue;
            }

            auto dist_v = find_pair(v, dist);
            auto dist_u = find_pair(u, dist);
            if (dist_v.second > dist_u.second + weight) {
                dist_v.second = dist_u.second + weight;
                update_distance(make_pair(v, dist_v.second), dist);
                pq.push(make_pair(v, dist_v.second));
            }
        }

        if (color == R_VALUE) {
            auto it = find(red_end_nodes.begin(), red_end_nodes.end(), u);
            if (it != red_end_nodes.end()) {
                return true;
            }
        } else {
            auto it = find(blue_end_nodes.begin(), blue_end_nodes.end(), u);
            if (it != blue_end_nodes.end()) {
                return true;
            }
        }
    }

    return false;
}

template<size_t N>
iPair Graph<N>::find_pair(Node node, vector<iPair> dist) {
    for (auto it = dist.begin(); it != dist.end(); it++) {
        if (it->first == node) {
            return make_pair(node, it->second);
        }
    }
    return make_pair(node, INF);
}

template<size_t N>
void Graph<N>::update_distance(iPair ipair, vector<iPair> &dist) {
    if (auto it = find_if(dist.begin(), dist.end(), [ipair](iPair ip) { return ipair.first == ip.first; });
        it != dist.end()) {
        (*it).second = ipair.second;
    }
}

template<size_t N>
int Graph<N>::get_size() const {
    return V;
}

template<size_t N>
void Graph<N>::create_board() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            blue_board[i][j] = -1;
            red_board[i][j] = -1;
            board[i][j] = -1;
        }
    }
}

template<size_t N>
Board<N> Graph<N>::get_blue_board() {
    return blue_board;
}

template<size_t N>
Board<N> Graph<N>::get_red_board() {
    return red_board;
}

template<size_t N>
Board<N> Graph<N>::get_board() {
    return board;
}

template<size_t N>
void Graph<N>::set_movement(int x, int y, char current_player) {
    this->current_player = current_player;
    board[x][y] = current_player == 'X' ? R_VALUE : B_VALUE;
    if (current_player == 'X') {
        red_board[x][y] = R_VALUE;
        blue_board[x][y] = I_VALUE;
        update_cost(x, y, 1, adj_red);
        update_graph(x, y, adj_blue);
        red_nodes.push_back(Node(x, y));
        if (x == V - 1) {
            blue_end_nodes.erase(std::remove(blue_end_nodes.begin(), blue_end_nodes.end(), Node(x, y)),
                                 blue_end_nodes.end());
        }
    } else {
        blue_board[x][y] = B_VALUE;
        red_board[x][y] = I_VALUE;
        update_cost(x, y, 1, adj_blue);
        update_graph(x, y, adj_red);
        blue_nodes.push_back(Node(x, y));
        if (y == V - 1) {
            red_end_nodes.erase(std::remove(red_end_nodes.begin(), red_end_nodes.end(), Node(x, y)),
                                red_end_nodes.end());
        }
    }
}

template<size_t N>
void Graph<N>::update_graph(int x, int y, Adj &adj) {
    auto node = Node(x, y);
    auto &edges = adj[node];
    for (auto it = edges.begin(); it != edges.end(); it++) {
        auto neighbor = it->first;
        auto &neighbor_edge = adj[neighbor];
        auto iter = find_if(neighbor_edge.begin(), neighbor_edge.end(),
                            [node](iPair pair) { return node == pair.first; });
        neighbor_edge.erase(iter);
    }
    adj.erase(node);
}

template<size_t N>
vector<Node> Graph<N>::get_all_nodes_of_red_from_same_row(vector<Node> &nodes, int y) {
    auto predicate = [y](const Node n) {
        return n.y == y;
    };

    // Find the nodes with the condition
    auto it = find_if(begin(nodes), end(nodes), predicate);
    vector<Node> occurrences;
    while (it != nodes.end()) {
        occurrences.push_back(*it);
        it = find_if(it + 1, nodes.end(), predicate);
    }

    return occurrences;
}

template<size_t N>
vector<Node> Graph<N>::get_all_nodes_of_blue_from_same_column(vector<Node> &nodes, int x) {
    auto predicate = [x](const Node n) {
        return n.x == x;
    };

    auto it = find_if(begin(nodes), end(nodes), predicate);

    vector<Node> occurrences;
    while (it != nodes.end()) {
        occurrences.push_back(*it);
        it = find_if(it + 1, nodes.end(), predicate);
    }

    return occurrences;
}

template<size_t N>
void Graph<N>::add_edges() {
    int edge_cost = INF;

    // Connections for node: (0,0)
    addEdge(Node(0, 0), Node(0, 1), edge_cost);
    addEdge(Node(0, 0), Node(1, 0), edge_cost);

    // Connections for node: (board_size-1, board_size - 1)
    addEdge(Node(V - 1, V - 1), Node(V - 1, V - 2), edge_cost);
    addEdge(Node(V - 1, V - 1), Node(V - 2, V - 1), edge_cost);

    // Connections for nodes: (i, 0)
    for (int i = 1; i < V - 1; i++) {
        addEdge(Node(i, 0), Node(i - 1, 0), edge_cost);
        addEdge(Node(i, 0), Node(i - 1, 1), edge_cost);
        addEdge(Node(i, 0), Node(i, 1), edge_cost);
        addEdge(Node(i, 0), Node(i + 1, 0), edge_cost);
    }

    // Connections for nodes: (board_size-1,0)
    addEdge(Node(V - 1, 0), Node(V - 2, 0), edge_cost);
    addEdge(Node(V - 1, 0), Node(V - 2, 1), edge_cost);
    addEdge(Node(V - 1, 0), Node(V - 1, 1), edge_cost);

    // Connections for node: (0, board_size-1)
    addEdge(Node(0, V - 1), Node(0, V - 2), edge_cost);
    addEdge(Node(0, V - 1), Node(1, V - 2), edge_cost);
    addEdge(Node(0, V - 1), Node(1, V - 1), edge_cost);

    // Connections for nodes: (i, board_size-1)
    for (int i = 1; i < V - 1; i++) {
        addEdge(Node(i, V - 1), Node(i - 1, V - 1), edge_cost);
        addEdge(Node(i, V - 1), Node(i, V - 2), edge_cost);
        addEdge(Node(i, V - 1), Node(i + 1, V - 2), edge_cost);
        addEdge(Node(i, V - 1), Node(i + 1, V - 1), edge_cost);
    }

    // Connections for nodes: (0, j)
    for (int j = 1; j < V - 1; j++) {
        addEdge(Node(0, j), Node(0, j - 1), edge_cost);
        addEdge(Node(0, j), Node(1, j - 1), edge_cost);
        addEdge(Node(0, j), Node(1, j), edge_cost);
        addEdge(Node(0, j), Node(0, j + 1), edge_cost);
    }

    // Connections for nodes: (board_size-1, j)
    for (int j = 1; j < V - 1; j++) {
        addEdge(Node(V - 1, j), Node(V - 1, j - 1), edge_cost);
        addEdge(Node(V - 1, j), Node(V - 2, j), edge_cost);
        addEdge(Node(V - 1, j), Node(V - 2, j + 1), edge_cost);
        addEdge(Node(V - 1, j), Node(V - 1, j + 1), edge_cost);
    }

    // Connections for nodes: (i, j)
    for (int i = 1; i < V - 1; i++) {
        for (int j = 1; j < V - 1; j++) {
            addEdge(Node(i, j), Node(i - 1, j), edge_cost);
            addEdge(Node(i, j), Node(i, j - 1), edge_cost);
            addEdge(Node(i, j), Node(i + 1, j - 1), edge_cost);
            addEdge(Node(i, j), Node(i + 1, j), edge_cost);
            addEdge(Node(i, j), Node(i, j + 1), edge_cost);
            addEdge(Node(i, j), Node(i - 1, j + 1), edge_cost);
        }
    }
}

template<size_t N>
pair<char, bool> Graph<N>::get_winner() {
    initialize_dist();

    auto red_0 = get_all_nodes_of_red_from_same_row(red_nodes, 0);
    auto blue_0 = get_all_nodes_of_blue_from_same_column(blue_nodes, 0);

    for (auto it = red_0.begin(); it != red_0.end(); it++) {
        auto outcomes = shortestPath(*it, adj_red, dist_red, R_VALUE);
        if (outcomes) {
            return make_pair('R', true);
        }
    }

    for (auto it = blue_0.begin(); it != blue_0.end(); it++) {
        auto outcomes = shortestPath(*it, adj_blue, dist_blue, B_VALUE);
        if (outcomes) {
            return make_pair('B', true);
        }
    }

    return make_pair('N', false);
}

template<size_t N>
void Graph<N>::print_board(Board board) {
    cout << endl;

    int h = 0;
    int l = 1;
    for (int j = 0; j < V; j++) {
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
        for (; i < V; i++) {
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
        if (j == V - 1) {
            break;
        }

        // Print connections between nodes
        h += 2;
        cout << "\\ ";
        for (int i = 0; i < V * 2 - 2; i++) {
            cout << (i % 2 == 0 ? "/ " : "\\ ");
        }
        cout << endl;
        for (int j = 0; j < l + 1; j = j + 1)
            cout << " ";
        l += 2;
    }
    cout << endl;
}

template class Graph<7>;
template class Graph<11>;