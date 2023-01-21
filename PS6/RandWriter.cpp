// Copyright 2022 Andrew Allman



#include "./RandWriter.hpp"

vector<pair<char, int>>* initSymbolTable() {
    vector<pair<char, int>>* symbol_table =
    new vector<pair<char, int>>(ASCII_MAX);

    for (char i = 0; i < ASCII_MAX; ++i) {
        symbol_table->at(i) = make_pair(i, 0);
    }
    return symbol_table;
}

RandWriter::RandWriter(string text, int k) : _k(k) {
    char c;
    string tsub;
    for (size_t i = 0; i < text.length() - _k - 1; i++) {
        c = text[i + _k];
        tsub = text.substr(i, _k);
        if (SymbolTableMap.find(tsub) == SymbolTableMap.end()) {
            SymbolTableMap[tsub] = initSymbolTable();
        }
        ++SymbolTableMap[tsub]->at(c).second;
        tsub.clear();
    }
    for (auto& itm : SymbolTableMap) {
        sort((*itm.second).begin(), (*itm.second).end(), [](
            pair<char, int> a, pair<char, int> b) {
            return a.second > b.second;
        });
    }
}

int RandWriter::orderK() const {
    return _k;
}

int RandWriter::freq(string kgram) const {
    if (SymbolTableMap.find(kgram) == SymbolTableMap.end()) {
        throw std::runtime_error("No such kgram found: " + kgram);
    }

    return std::accumulate((*SymbolTableMap.at(kgram)).begin(),
    (*SymbolTableMap.at(kgram)).end(), 0, [](
        int sum, pair<char, int> a) { return sum + a.second; });
}

int RandWriter::freq(string kgram, char c) const {
    if (kgram.length() != _k) {
        throw std::runtime_error("Provided kgram incorrect size.");
    }

    if (SymbolTableMap.find(kgram) == SymbolTableMap.end()) {
        throw std::runtime_error("No such kgram found: " + kgram);
    }

    for (size_t i = 0; i < (*SymbolTableMap.at(kgram)).size(); ++i) {
        if ((*SymbolTableMap.at(kgram)).at(i).first == c) {
            return (*SymbolTableMap.at(kgram)).at(i).second;
        }
    }
    return 0;
}

char RandWriter::kRand(string kgram) {
    if (kgram.length() != _k) {
        throw("Invalid kgram length. Does not match k");
    }
    std::default_random_engine rand_engine(rand_dev());
    std::uniform_int_distribution<int> rand_dist(0, freq(kgram));
    int rnd_input = rand_dist(rand_engine);
    for (auto& pr : (*SymbolTableMap[kgram])) {
        rnd_input -= pr.second;
        if (rnd_input <= 0) {
            return pr.first;
        }
    }
    return ' ';
}

ostream& operator<<(ostream& out, RandWriter& r) {
    for (auto& itm : r.SymbolTableMap) {
        out << "K-Gram: " << itm.first << endl;
        for (auto& pr : *itm.second) {
            out << "Char: "
            << pr.first
            << " | Frequency: "
            << pr.second
            << std::endl;
        }
    } return out;
}
string RandWriter::generate(string kgram, int L) {
    if (kgram.length() != _k) {
        throw std::runtime_error("Provided seed doesn't match k-length.");
    }
    while (kgram.length() != L) {
        if (_k > 0)
            kgram += kRand(kgram.substr(kgram.length() - _k));
        else
            kgram += kRand("");
    }
    return  kgram;
}

RandWriter::~RandWriter() {
    for (auto& itm : SymbolTableMap) {
        delete itm.second;
    }
}
