#include "Dijkstra.h"
#include "HexGamer.h"

int main() {
    // create the graph given in above figure
    int board_size = 5;
    Graph g(board_size);

    HexGamer hex_gamer = HexGamer(g);
    cout << "Next move: " << endl << hex_gamer.monte_carlo_move(5) << endl;


    // making above shown graph
    /*g.addEdge(Node(0, 0), Node(0, 1), 4);
    g.addEdge(Node(0, 0), Node(0, 7), 8);
    g.addEdge(Node(0, 1), Node(0, 2), 8);
    g.addEdge(Node(0, 1), Node(0, 7), 11);
    g.addEdge(Node(0, 2), Node(0, 3), 7);
    g.addEdge(Node(0, 2), Node(0, 8), 2);
    g.addEdge(Node(0, 2), Node(0, 5), 4);
    g.addEdge(Node(0, 3), Node(0, 4), 9);
    g.addEdge(Node(0, 3), Node(0, 5), 14);
    g.addEdge(Node(0, 4), Node(0, 5), 10);
    g.addEdge(Node(0, 5), Node(0, 6), 2);
    g.addEdge(Node(0, 6), Node(0, 7), 1);
    g.addEdge(Node(0, 6), Node(0, 8), 6);
    g.addEdge(Node(0, 7), Node(0, 8), 7);

    // Function call
    g.shortestPath(Node(0, 0));*/
}
