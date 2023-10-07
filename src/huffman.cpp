#include "huffman.hpp"
#include "hufftree.hpp"

#include <bitset>
#include <climits>

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
    uint8_t table_size = code_table.size();
    os.write(reinterpret_cast<char*>(&table_size), sizeof(char));

    for (auto [key, value] : code_table) {
        os.write(&key, sizeof(char));
        os.write(reinterpret_cast<char*>(&freq_[key]), sizeof(int));
        code_length += freq_[key] * value.size();
    }

    uint8_t module = (code_length % CHAR_BIT) != 0 ? (code_length % CHAR_BIT) : CHAR_BIT;
    os.write(reinterpret_cast<char*>(&module), sizeof(char));

    char ch;
    uint8_t idx = 0;
    std::bitset<CHAR_BIT> bs;

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

void Huffman::decode(std::istream& is, std::ostream& os) {
    uint8_t table_size;
    is.read(reinterpret_cast<char*>(&table_size), sizeof(char));

    for (uint8_t i = 0; i < table_size; ++i) {
        char ch;
        is.read(&ch, sizeof(char));
        is.read(reinterpret_cast<char*>(&freq_[ch]), sizeof(int));
    }

    uint8_t module;
    is.read(reinterpret_cast<char*>(&module), sizeof(char));

    size_t pos = is.tellg();

    is.seekg(0, std::ios::end);
    size_t data_size = static_cast<size_t>(is.tellg()) - pos;

    is.clear();
    is.seekg(pos, std::ios::beg);

    HuffTree htree(freq_);
    std::bitset<CHAR_BIT> bs;
    uint8_t n_bits = bs.size();

    while (is.read(reinterpret_cast<char*>(&bs), sizeof(char))) {
        if (--data_size == 0)
            n_bits = module;

        for (uint8_t i = 0; i < n_bits; ++i) {
            char ch = htree.next(bs[i]);

            if (ch != 0)
                os.write(&ch, sizeof(char));
        }
    }
}
