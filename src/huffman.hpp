#pragma once

#include <fstream>
#include <vector>

class Huffman {
private:
    std::vector<int> freq_;

    void count_freq(std::istream& is);
public:
    Huffman(): freq_(128, 0) {}

    void encode(std::istream& is, std::ostream& os);
    void decode(std::istream& is, std::ostream& os);
};
