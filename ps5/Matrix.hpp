// Copyright [2022] <Andrew Allman>



#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include<stdlib.h>
#include<memory>
#include <iostream>
#include<algorithm>

using std::unique_ptr;


class Matrix {
 public:
    Matrix();
    Matrix(size_t height, size_t width);
    size_t size() const;
    size_t rSize() const;
    size_t cSize() const;
    int& operator()(int, int);
    const int operator()(int, int) const;
    int& at(int, int);
    const int& at(int, int) const;
 private:
    int _rows;
    int _columns;
    unique_ptr<int[]> _state_matrix;
};

#endif  // MATRIX_HPP_
