#include "huffman.hpp"

void Huffman::count_freq(std::istream& is) {
    char ch;

    while (!is.eof()) {
        is.read(&ch, sizeof(char));
        ++freq[ch];
    }
}

void Huffman::encode(std::istream& is, std::ostream& os) {
    count_freq(is);

    for (size_t i = 0; i < freq.size(); ++i) {
        if (freq[i] == 0) continue;
        os << "[" << static_cast<char>(i) << "]: " << freq[i] << std::endl;
    }
}
