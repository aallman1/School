// Copyright [2022] <Andrew Allman>



#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include<stdlib.h>
#include<memory>


using std::unique_ptr;

class Matrix {
 public:
    Matrix();
    Matrix(size_t height, size_t width);
    size_t size() const;
    size_t rSize() const;
    size_t cSize() const;
    char& operator()(size_t, size_t);
    const char& operator()(size_t, size_t) const;
    char& at(size_t, size_t);
    const char& at(size_t, size_t) const;

 private:
    size_t _rows;
    size_t _columns;
    unique_ptr<char[]> _state_matrix;
};

#endif  // MATRIX_HPP_
