//
// Created by kelvin cervan ruiz on 12/06/24.
//

#ifndef NODE_H
#define NODE_H

#include <iostream>

struct Node {
    // Positions
    int x;
    int y;

    Node(int x, int y): x{x}, y{y} {
    }

    friend std::ostream &operator<<(std::ostream &out, const Node node) {
        out << "(" << node.x << ", " << node.y << ")";
        return out;
    }

    bool operator==(const Node &n1) const {
        return x == n1.x && y == n1.y;
    }
};

template<>
struct std::hash<Node> {
    std::size_t operator()(const Node &node) const noexcept {
        std::size_t h1 = std::hash<int>{}(node.x);
        std::size_t h2 = std::hash<int>{}(node.y);
        return h1 ^ (h2 << 1);
    }
};

#endif //NODE_H
