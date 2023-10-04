#include "huffman.hpp"
#include "hufftree.hpp"

#include <bitset>

void Huffman::count_freq(std::istream& is) {
    char ch;

    while (is.read(&ch, sizeof(char))) {
        ++freq_[ch];
    }

    is.clear();
    is.seekg(std::ios::beg);
}

void Huffman::encode(std::istream& is, std::ostream& os) {
    count_freq(is);

    HuffTree htree(freq_);
    auto code_table = htree.to_map();

    size_t code_length = 0;
    size_t count = code_table.size();
    os.write(reinterpret_cast<char*>(&count), sizeof(char));

    for (auto [key, value] : code_table) {
        os.write(&key, sizeof(char));
        os.write(reinterpret_cast<char*>(&freq_[key]), sizeof(int));
        code_length += freq_[key] * value.size();
    }

    size_t module = code_length % 8;
    os.write(reinterpret_cast<char*>(&module), sizeof(char));

    char ch;
    size_t idx = 0;
    std::bitset<8> bs;

    while (is.read(&ch, sizeof(char))) {
        for (auto b : code_table[ch]) {
            if (idx == bs.size()) {
                os.write(reinterpret_cast<char*>(&bs), sizeof(char));
                bs.reset();
                idx = 0;
            }

            bs[idx++] = b;
        }
    }

    os.write(reinterpret_cast<char*>(&bs), sizeof(char));
}
