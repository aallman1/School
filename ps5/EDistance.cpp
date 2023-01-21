// Copyright [2022] <Andrew Allman>



#include "./EDistance.hpp"


EDistance::EDistance(const string& source, const string& target) :
_source(source),
_target(target),
 _dTable(new Matrix(_source.length() + 1, _target.length() + 1)) {}


int EDistance::penalty(char a, char b) {
    return a == b ? 0 : 1;
}

int EDistance::min(int a, int b, int c) {
    return a < b ? a < c ? a : c : b < c ? b : c;
}

int EDistance::optDistance() {
    int source_length = _source.length(), target_length = _target.length();
    for (int i = source_length; i >= 0; i--) {
        for (int j = target_length; j >= 0; j--) {
            if (i >= source_length && j >= target_length) {
                (*_dTable)(i, j) = 0;
            } else if (j >= target_length) {
                (*_dTable)(i, j) = (*_dTable)(i + 1, j) + 2;
            } else if (i >= source_length) {
                (*_dTable)(i, j) = (*_dTable)(i, j + 1) + 2;
            } else {
                (*_dTable)(i, j) = min(
                    (*_dTable)(i + 1, j + 1) + penalty(_source[i], _target[j]),
                    (*_dTable)(i + 1, j) + 2,
                    (*_dTable)(i, j+ 1) + 2);
            }
        }
    }
    return (*_dTable)(0, 0);
}


const string EDistance::alignment(
    string (*formatReturnString)(char, char, char)) const {
    int i = 0, j = 0, mininimum;
    string retString = "";
    char src, trg, pen;

    while (i < _source.length() || j < _target.length()) {
        if (_source[i] == _target[j]) {
            src = _source[i];
            trg = _target[j];
            i += 1;
            j += 1;
            pen = '0';
        } else if ((*_dTable)(i + 1, j + 1) == (*_dTable)(i, j) - 1) {
            src = _source[i];
            trg = _target[j];
            i += 1;
            j += 1;
            pen = '1';
        } else if ((*_dTable)(i + 1, j)  == (*_dTable)(i, j) - 2) {
            src = _source[i];
            trg = '-';
            i += 1;
            pen = '2';
        } else {
            src = '-';
            trg = _target[j];
            j += 1;
            pen = '2';
        }
        retString += formatReturnString(src, trg, pen);
    }
    return retString;
}

EDistance::~EDistance() { delete _dTable; }
