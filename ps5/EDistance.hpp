// Copyright [2022] <Andrew Allman>

#ifndef EDISTANCE_HPP_
#define EDISTANCE_HPP_


#include <stdlib.h>

#include<iostream>
#include<string>
#include<cstddef>
#include<algorithm>

#include "./Matrix.hpp"

using std::string;
using std::size_t;

class EDistance {
 public:
    EDistance(const string& source, const string& target);
    static int penalty(char a, char b);
    static int min(int a, int b, int c);
    int optDistance();
    const string alignment(
      string (*formatReturnString)(char, char, char)) const;
    ~EDistance();
 private:
    string _source;
    string _target;
    Matrix* _dTable;
};

#endif  // EDISTANCE_HPP_
