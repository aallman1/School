# PS1: PhotoMagic

## Contact
Name: Andrew Allman
Section: 202
Time to Complete: 4 hrs

## Description
This project implements a Fibonacci linear feedback shift register to encrypt and decrypt an image.

### Features
The original design used a vector with very easy to implement class methods. Implementation of the LFSR as a bitfield object was 
a decision I made to simulate the system at a lower level. This made the build more space conscious, but a bit more tedious to write.
Uses passcode as input for seeding the LFSR.

### Issues
Haven't seen any problems.

### Extra Credit
Implementation takes an alphanumeric passcode instead of a seed. To generate a seed from the passcode, I summed the 
characters of the passcode, and leveraged the std bitset library to convert the integer into a bitstring.

## Acknowledgements
-Notes on Makefile. 
-Quiz on Makefile.
-Boost documentation
-CPPReference.com

