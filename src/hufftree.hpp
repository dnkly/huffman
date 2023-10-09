#pragma once

#include <memory>
#include <vector>
#include <map>

struct Node {
    char ch_;
    int count_;
    bool visited_;
    std::shared_ptr<Node> left_;
    std::shared_ptr<Node> right_;

    Node(char ch, int count = 0):
        ch_(ch), count_(count), visited_(false), left_(nullptr), right_(nullptr) {}
};

class HuffTree {
private:
    std::shared_ptr<Node> root_;
    std::shared_ptr<Node> current_;

    void build_tree(const std::vector<int>& freq);
public:
    HuffTree(const std::vector<int>& freq): root_(nullptr) {
        build_tree(freq);
        current_ = root_;
    }

    std::map<char, std::vector<bool>> to_map() const;
    char next(bool b);
};
