#include "huffman.hpp"
#include "hufftree.hpp"

void Huffman::count_freq(std::istream& is) {
    char ch;

    while (!is.eof()) {
        is.read(&ch, sizeof(char));
        ++freq[ch];
    }
}

void Huffman::encode(std::istream& is, std::ostream& os) {
    count_freq(is);

    HuffTree htree(freq);
    auto code_table = htree.to_map();

    for (auto [key, value] : code_table) {
        os << "[" << key << "]  " << freq[key] << "  ";
        for (auto b : value) os << b;
        os << std::endl;
    }
}
