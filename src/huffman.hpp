#pragma once

#include <fstream>
#include <array>

class Huffman {
private:
    std::array<int, 256> freq;

    void count_freq(std::istream& is);
public:
    Huffman(): freq({0}) {}

    void encode(std::istream& is, std::ostream& os);
};
