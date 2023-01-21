// Copyright [2022] <Andrew Allman>




#include"./Matrix.hpp"

Matrix::Matrix(): _rows(0), _columns(0) {}

Matrix::Matrix(size_t height, size_t width):
_rows(height),
_columns(width),
_state_matrix(unique_ptr<char[]>(new char[height * width])) {
    for (size_t i = 0, size = height * width; i < size; i++) {
        _state_matrix[i] = '|';
    }
}

char& Matrix::operator()(size_t row, size_t column) {
    return _state_matrix[row * _columns + column];
}

const char& Matrix::operator()(size_t row, size_t column) const {
    return _state_matrix[row * _columns + column];
}

char& Matrix::at(size_t row, size_t column) {
    return _state_matrix[row * _columns + column];
}

const char& Matrix::at(size_t row, size_t column) const {
    return _state_matrix[row * _columns + column];
}

size_t Matrix::size() const {
    return _rows * _columns;
}

size_t Matrix::rSize() const {
    return _rows;
}

size_t Matrix::cSize() const {
    return _columns;
}
