// Copyright [2022] <Andrew Allman>




#include"./Matrix.hpp"

Matrix::Matrix(): _rows(0), _columns(0) {}

Matrix::Matrix(size_t height, size_t width):
_rows(height),
_columns(width),
_state_matrix(unique_ptr<int[]>(new int[height * width])) {
    for (int i = 0, size = height * width; i < size; i++) {
        _state_matrix[i] = '0';
    }
}

int& Matrix::operator()(int row, int column) {
    return _state_matrix[row * _columns + column];
}

const int Matrix::operator()(int row, int column) const {
    return _state_matrix[row * _columns + column];
}

int& Matrix::at(int row, int column) {
    return _state_matrix[row * _columns + column];
}

const int& Matrix::at(int row, int column) const {
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

