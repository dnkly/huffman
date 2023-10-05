#include "hufftree.hpp"

#include <queue>
#include <stack>

void HuffTree::build_tree(const std::vector<int>& freq) {
    auto cmp = [](std::shared_ptr<Node> p1, std::shared_ptr<Node> p2) {
        return p1->count_ > p2->count_;
    };

    std::priority_queue<std::shared_ptr<Node>,
        std::vector<std::shared_ptr<Node>>, decltype(cmp)> p_queue(cmp);

    for (size_t i = 0; i < freq.size(); ++i) {
        if (freq[i] == 0) continue;
        p_queue.push(std::make_shared<Node>(i, freq[i]));
    }

    while (p_queue.size() > 1) {
        auto left = p_queue.top();
        p_queue.pop();
        auto right = p_queue.top();
        p_queue.pop();

        auto node = std::make_shared<Node>(0, left->count_ + right->count_);
        node->left_ = left;
        node->right_ = right;

        p_queue.push(node);
    }

    root_ = p_queue.top();
}

std::map<char, std::vector<bool>> HuffTree::to_map() const {
    std::map<char, std::vector<bool>> code_table;
    std::vector<bool> code;

    std::stack<std::shared_ptr<Node>> stack;
    std::shared_ptr<Node> current = root_;

    if (current) stack.push(current);

    while (!stack.empty()) {
        if (current->left_ && !current->left_->visited_) {
            stack.push(current);
            code.push_back(0);
            current = current->left_;
        } else if (current->right_ && !current->right_->visited_) {
            stack.push(current);
            code.push_back(1);
            current = current->right_;
        } else {
            if (current->ch_ != 0)
                code_table[current->ch_] = std::vector<bool>(code);

            current->visited_ = true;
            current = stack.top();
            stack.pop();
            code.pop_back();
        }
    }

    return code_table;
}
