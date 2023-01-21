// Copyright [2022] <Andrew Allman>




#include<math.h>
#include "./Sokoban.hpp"
#include "./Matrix.hpp"

using std::cin;
using std::cout;

auto convertGameClock = [](const sf::Clock& clock) {
    int total_seconds = clock.getElapsedTime().asSeconds();
    int minutes = total_seconds / 60, seconds = total_seconds % 60;

    return minutes < 10 ? seconds < 10 ?
            "0" + std::to_string(minutes) +
            ":" + "0" + std::to_string(seconds):
            "0" + std::to_string(minutes)
            + ":" + std::to_string(seconds):
        seconds < 10 ?
            std::to_string(minutes) +
            ":" + "0" + std::to_string(seconds):
            std::to_string(minutes)
            + ":" + std::to_string(seconds);
};

int main() {
    Sokoban sGame;
    cin >> sGame;
    cout << sGame;

    sf::Font font;
    sf::Clock clock;
    sf::Event event;
    sf::Text text;

    text.setFont(font);
    text.setPosition(70, 70);
    text.setFillColor(sf::Color::White);
    font.loadFromFile("SourceCodePro-ExtraLight.ttf");
    std::pair<size_t, size_t> gameGrid = sGame.gridSize();

    sf::RenderWindow window(
        sf::VideoMode(
            gameGrid.first * SPRITE_SIZE, gameGrid.second * SPRITE_SIZE),
                "Sokoban UI");

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        text.setString(convertGameClock(clock));
        window.clear();
        window.draw(sGame);
        window.draw(text);
        window.display();
    }
}
