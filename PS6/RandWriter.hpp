// Copyright 2022 Andrew Allman



#ifndef RANDWRITER_HPP_
#define RANDWRITER_HPP_

#include<string>
#include<unordered_map>
#include<vector>
#include<numeric>
#include<algorithm>
#include<iostream>
#include<utility>
#include<random>

using std::string;
using std::ostream;
using std::unordered_map;
using std::pair;
using std::cout;
using std::copy;
using std::vector;
using std::make_pair;
using std::sort;
using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::endl;

const char ASCII_MAX = 127;
vector<pair<char, int>>* initSymbolTable();

class RandWriter {
 public:
    RandWriter(string text, int k);
    int orderK() const;
    int freq(string kgram) const;
    int freq(string kgram, char c) const;
    char kRand(string kgram);
    friend ostream& operator<<(ostream& out, RandWriter& r);
    string generate(string kgram, int L);
    ~RandWriter();
 private:
    std::random_device rand_dev;
    unordered_map<string, vector<pair<char, int>>*> SymbolTableMap;
    int _k;
};

#endif  // RANDWRITER_HPP_
