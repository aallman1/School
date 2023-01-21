// Copyright 2022 Andrew Allman




#include<fstream>
#include<sstream>

#include "./RandWriter.hpp"

using std::ifstream;
using std::stringstream;
using std::cin;
using std::stoi;

int main(int argc, char* argv[]) {
    string inp_text;
    stringstream buffer;
    int k = stoi(argv[1]), L = stoi(argv[2]);

    while (cin >> inp_text) {
        for (char c : inp_text) {
            if (c < 0 || c > ASCII_MAX) { continue; }
        }
        buffer << string(inp_text + " ");
    }
    string seed = buffer.str().substr(0, k);
    RandWriter rw(buffer.str(), k);
    std::cout << rw.generate(seed, L) << endl;
}
