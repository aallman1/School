// Copyright [2022] <Andrew Allman>





#include<string>
#include<iostream>
#include<SFML/System.hpp>

#include "./EDistance.hpp"

int main() {
    string source, target;
    if (!(std::cin >> source)) {
        throw std::runtime_error("Invalid file data.");
    }
    if (!(std::cin >> target)) {
        throw std::runtime_error("Invalid file data.");
    }
    sf::Clock c;
    EDistance e(source, target);
    std::cout << "Edit distance = " << e.optDistance() << std::endl;
    std::cout << e.alignment([](char src, char trg, char pen) {
            string retString = "";
            retString += src;
            retString += " ";
            retString += trg;
            retString += " ";
            retString += pen;
            retString += "\n";
            return retString;
        });
    std::cout << c.getElapsedTime().asSeconds() << std::endl;
}
