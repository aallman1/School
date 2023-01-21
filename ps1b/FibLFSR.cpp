#include<iostream>
#include<vector>
#include<iostream>
#include <SFML/Graphics.hpp>
#include"FibLFSR.hpp"

//class implementations

//helper function - to keep bitstring_data from scaling massively, 
//each call to step limits the bitstring_data by ANDing it's value
//by the maximum value of that size 111...1
int generate_limit(int size){
    int k = 0;
    for(int i = 0; i < size; i++){
        k = (k << 1) + 1;
    }
    return k;
}



//Constructor, creates a bit field object for representing bit string
//The field is initialized to zero, and bits are flipped as necessary while reading in
//characters from the seed
FibLFSR::FibLFSR(std::string seed) {
    _bit_string = new int [(seed.size() / (BYTES_PER_INT * BITS_PER_BYTE)) + 1]{0};
    _size = seed.size();
    for(int i = _size - 1; i >= 0; i--){
        switch(seed[i]){
            case '1':
            _bit_string[(_size - i - 1) / (BYTES_PER_INT * BITS_PER_BYTE)] |= (1 << (_size - i - 1) % (BYTES_PER_INT * BITS_PER_BYTE));
            break;
            default:
            break;
        }
    }
    _limit = generate_limit(_size);
}

//For indexing field
bool FibLFSR::at(const int index){
    return ((_bit_string[index / (BYTES_PER_INT * BITS_PER_BYTE)]) & (1  << (index % (BYTES_PER_INT * BITS_PER_BYTE))));
}
//returns limit
const int FibLFSR::getLimit(void)const{
    return _limit;
}
//Peforms a step, left shifts the field by 1, and sets the 0th bit to the XOR'd values of the taps and exiting bit
int FibLFSR::step() {
    int tProd = ((at(15) ^ at(13)) ^ at(12)) ^ at(10);
    *_bit_string <<= 1;
    *_bit_string &= _limit;
    switch (tProd)
    {
    case 1:
        set(0);
        break;
    default:
        unset(0);
        break;
    }
    return tProd;
}

//Built to set bits with bitwise operators - had I exercised more foresight I could've just subtracted one where necessary.
void FibLFSR::set(const int index){
    _bit_string[(index) / BITS_PER_BYTE] |= (1 << (index) % BITS_PER_BYTE);
}
//Built to unset bits with bitwise operators
void FibLFSR::unset(const int index){
    _bit_string[(index) / BITS_PER_BYTE] &= ~(1 << (index) % BITS_PER_BYTE);

}
//returns size
const int FibLFSR::getSize(void) const{
    return _size;
}

std::ostream& operator<<(std::ostream& out, FibLFSR& rhFib){
    for(int i = rhFib.getSize() - 1; i >= 0; i--){
        out << rhFib.at(i);
    }
    return out;
}

// Simulate k steps and return a k-bit integer
int FibLFSR::generate(int k) {
    int result = 0;
    for (int i = 0; i < k; i++) {
        result = (result << 1) + step();
    }
    return result;
}
