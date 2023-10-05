#include "huffman.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "display help message")
        ("encode,e", "encode data")
        ("file,f", po::value<std::string>(), "input file")
        ("output,o", po::value<std::string>(), "output file");

    po::positional_options_description pos;
    pos.add("file", -1);

    try {
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(pos).run(), vm);
        po::notify(vm);

        if (!vm.count("file")) {
            std::cout << desc;
            return 0;
        }

        Huffman h;
        std::filesystem::path filepath(vm["file"].as<std::string>());

        if (vm.count("encode")) {
            std::ifstream ifs(vm["file"].as<std::string>(), std::ios::binary);

            if (!ifs.is_open())
                throw std::system_error(errno, std::generic_category());

            std::string output = vm.count("output")
                ? vm["output"].as<std::string>()
                : (filepath.parent_path() / filepath.stem()).string() + ".hff";

            std::ofstream ofs(output, std::ios::binary);
            h.encode(ifs, ofs);
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
