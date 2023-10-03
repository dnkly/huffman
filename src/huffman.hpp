#pragma once

#include <fstream>
#include <vector>

class Huffman {
private:
    std::vector<int> freq;

    void count_freq(std::istream& is);
public:
    Huffman(): freq(128, 0) {}

    void encode(std::istream& is, std::ostream& os);
};
