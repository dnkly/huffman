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
        ("decode,d", "decode data")
        ("file,f", po::value<std::string>(), "input file")
        ("output,o", po::value<std::string>(), "output file");

    po::positional_options_description pos;
    pos.add("file", -1);

    try {
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(pos).run(), vm);
        po::notify(vm);

        bool incorrect_options = !vm.count("file")
            || (vm.count("encode") && vm.count("decode"))
            || (!vm.count("encode") && !vm.count("decode"));

        if (incorrect_options) {
            std::cout << desc;
            return 1;
        }

        Huffman h;
        std::filesystem::path filepath(vm["file"].as<std::string>());
        std::ifstream ifs(filepath, std::ios::binary);

        if (!ifs.is_open())
            throw std::system_error(errno, std::generic_category());

        std::string extension;

        if (vm.count("encode")) {
            extension = ".hff";
        } else {
            uint8_t extension_length;
            ifs.read(reinterpret_cast<char*>(&extension_length), sizeof(char));

            extension.resize(extension_length);
            ifs.read(extension.data(), extension_length);
        }

        std::string output = vm.count("output")
            ? vm["output"].as<std::string>()
            : (filepath.parent_path() / filepath.stem()).string() + extension;

        std::ofstream ofs(output, std::ios::binary);

        if (vm.count("encode")) {
            extension = filepath.extension().string();
            uint8_t extension_length = extension.size();

            ofs.write(reinterpret_cast<char*>(&extension_length), sizeof(char));
            ofs.write(extension.c_str(), extension_length);

            h.encode(ifs, ofs);
        } else {
            h.decode(ifs, ofs);
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
