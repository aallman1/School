#include<iostream>
#include <SFML/Graphics.hpp>

//global consts for system independence 32/64
const int BITS_PER_BYTE = 8;
const int BYTES_PER_INT = sizeof(int);

class FibLFSR{
public:
    FibLFSR(std::string seed);
    int step(void);
    int generate(int k);
    void set(const int index);
    void unset(const int index);
    bool at(int index);
    const int getSize(void)const;
    const int getLimit(void)const;
    ~FibLFSR(){delete [] _bit_string;}
private:
    int* _bit_string;
    int _size;
    int _limit;
};

std::ostream& operator<<(std::ostream& out,  FibLFSR& FibLFSR);
