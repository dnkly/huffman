#include "huffman.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    std::ifstream ifs(argv[1], std::ios::binary);

    Huffman h;
    h.encode(ifs, std::cout);

    return 0;
}
