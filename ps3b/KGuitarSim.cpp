// Copyright [2022] <Andrew Allman>

#include<string>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include "./KGuitarSim.hpp"
#include "./sprites.hpp"
#include "./CircularBuffer.hpp"



using std::string;
using std::vector;

int main() {
    sf::Event event;
    double frequency;
    sf::SoundBuffer buffer;
    sf::Sprite background;
    vector<sf::Int16> sVector;
    sf::Texture background_texture;
    SWITCH sInstr(sf::Vector2f(1065, 640));
    vector<sf::Sound> gsSounds(NOTE_COUNT);
    vector<vector<sf::Int16>> gsNotes(NOTE_COUNT);
    vector<sf::SoundBuffer> gsBuffers(NOTE_COUNT);
    CircularBuffer<std::pair<sf::Sound*, sf::SoundBuffer*>> poly_kill_queue(5);

    sf::RenderWindow window(
        sf::VideoMode(1200, 800),
        "Super Mini - FM Synthesizer");

    window.setKeyRepeatEnabled(false);

    vector<FX_KNOB*> fx_knobs = {
        new FX_KNOB (50, 1000, sf::Vector2f(220, 350), 0.25),
        new FX_KNOB (0, 120000, sf::Vector2f(490, 350), 0.25),
        new FX_KNOB (0, 100, sf::Vector2f(735, 350), 0),
        new FX_KNOB (0, 10000, sf::Vector2f(980, 350), 0.5),
        new FX_KNOB (0, 120000, sf::Vector2f(330, 630), 0),
        new FX_KNOB (0.25, 8, sf::Vector2f(620, 630), 0.5),
        new FX_KNOB (0.47, 0.495, sf::Vector2f(875, 630), 1)
    };

    vector<sf::Drawable*> components = {
        &background,
        &sInstr,
        fx_knobs[M_PITCH],
        fx_knobs[MOD_FREQ],
        fx_knobs[OSC_I_GAIN],
        fx_knobs[DECAY],
        fx_knobs[MOD_GAIN],
        fx_knobs[OSC_II_PITCH],
        fx_knobs[OSC_II_GAIN]
    };


    background_texture.loadFromFile("loading_screen.png");
    background.setTexture(background_texture);
    window.draw(background);
    window.display();

    for (size_t i = 0; i < fx_knobs.size(); i++) {
        fx_knobs[i]->update();
    }

    for (int i = 0; i < NOTE_COUNT; i++) {
        StringSound note(CONCERT_A * pow(2.0, (i - 24)/ 12.0));
        note.pluck();
        gsNotes[i] = makeSamples(note);

        if (!gsBuffers[i].loadFromSamples(gsNotes[i].data(),
            gsNotes[i].size(), 2, SAMPLING_RATE)) {
            throw std::runtime_error(
                "sf::SoundBuffer: failed to load from samples.");
        }

        gsSounds[i].setBuffer(gsBuffers[i]);
    }

    background_texture.loadFromFile("background_synth.png");
    background.setTexture(background_texture);


    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (static_cast<string>(keys).find(getKey(
                        event.text.unicode)) !=
                            std::string::npos) {
                        int index = static_cast<string>(keys).find(
                            getKey(event.text.unicode));

                        frequency = (fx_knobs[M_PITCH]->getValue() *
                            pow(2.0, (index - 24)/ 12.0));

                        if (sInstr.getValue()) {
                            auto sf_pair =
                            std::pair<sf::Sound*, sf::SoundBuffer*>
                            (new sf::Sound, new sf::SoundBuffer);

                            SynthSound note(
                                frequency,
                                fx_knobs[MOD_FREQ]->getValue(),
                                fx_knobs[OSC_I_GAIN]->getValue(),
                                fx_knobs[DECAY]->getValue(),
                                fx_knobs[MOD_GAIN]->getValue(),
                                fx_knobs[OSC_II_PITCH]->getValue(),
                                fx_knobs[OSC_II_GAIN]->getValue());

                            sVector = makeSamples(note);

                            if (!sf_pair.second->loadFromSamples(
                                sVector.data(), sVector.size(),
                                 2, SAMPLING_RATE)) {
                                throw std::runtime_error(
                            "sf::SoundBuffer: failed to load from samples.");
                            }

                            sf_pair.first->setBuffer(*sf_pair.second);
                            sf_pair.first->play();
                            poly_kill_queue.enqueue(sf_pair);

                            if (poly_kill_queue.isFull()) {
                                auto pair = poly_kill_queue.dequeue();
                                delete pair.first;
                                delete pair.second;
                            }
                        } else { gsSounds[index].play(); }
                    } break;

                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        for (size_t i = 0; i < fx_knobs.size(); i++) {
                            if (fx_knobs[i]->hasMouseHover(
                                    static_cast<sf::Vector2f>(
                                        sf::Mouse::getPosition(window)))) {
                                fx_knobs[i]->adjust(
                                    static_cast<sf::Vector2f>(
                                        sf::Mouse::getPosition(window)));
                            } else if (sInstr.hasMouseHover(
                                static_cast<sf::Vector2f>(
                                    sf::Mouse::getPosition(window)))) {
                                        sInstr.flip();
                            }
                        }
                    } break;
                default:
                    break;
            }
        }

        window.clear();
        drawScreen(window, components);
        window.display();
    }

    while (!poly_kill_queue.isEmpty()) {
        auto pair = poly_kill_queue.dequeue();
        delete pair.first;
        delete pair.second;
    }

    for (size_t i = 0; i < fx_knobs.size(); i++) {
        delete fx_knobs[i];
    }
}

char getKey(uint32_t uc) {
    if (uc <= 26) {
        return uc + 97;
    } else if (uc < 36) {
        return (uc % 26) + 48;
    } else {
        switch (uc) {
        case 46:
            return '[';
        case 48:
            return ';';
        case 49:
            return ',';
        case 50:
            return '.';
        case 51:
            return 39;
        case 52:
            return 47;
        case 55:
            return '=';
        case 56:
            return '-';
        default:
            return '~';
            break;
        }
    }
}

void drawScreen(sf::RenderWindow& window, vector<sf::Drawable*>& components) {
    for (auto& component : components) {
        window.draw(*component);
    }
}

vector<sf::Int16> makeSamples(StringSound& gs) {
    std::vector<sf::Int16> samples;

    gs.pluck();
    for (int i= 0; i < SAMPLING_RATE * MAX_DURATION; i++) {
        gs.tick();
        samples.push_back(gs.sample());
    }

    return samples;
}


vector<sf::Int16> makeSamples(SynthSound& ss) {
    std::vector<sf::Int16> samples;

    ss.set();
    for (int i = 0; i < SAMPLING_RATE * MAX_DURATION; i++) {
        ss.tick();
        samples.push_back(ss.sample());
    }

    return samples;
}
