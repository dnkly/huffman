# huffman

Yet another file compressor using Huffman coding.

## Prerequisites

- Compiler with C++17 support
- Cmake 3.25 or later
- Boost (program_options)

## Build

```
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```

## Usage

```
$ ./huffman --help
Options:
  -h [ --help ]         display help message
  -e [ --encode ]       encode data
  -d [ --decode ]       decode data
  -f [ --file ] arg     input file
  -o [ --output ] arg   output file
```

### Example

```
$ ./huffman -e -o encoded.hff test.txt
$ ./huffman -d -o decoded.txt encoded.hff
```
