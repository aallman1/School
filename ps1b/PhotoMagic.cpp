#include<bitset>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<string>
#include "FibLFSR.hpp"


//generates simple hash of alphanumeric passcode
//by summing up char values of passcode, and using
//the std bitset library to represent value as a binary string

std::string returnEasyHash(std::string passcode){
    int sum = 0;
    for(char& ch : passcode){
        sum += int(ch);
    }
    return std::bitset<16>(sum).to_string();
}


//uses the fibonacci register object's generate function,
//to return an 8 bit integer value, which is used to encrypt/decrypt
//pixel values via XOR
void transform(sf::Image& image, FibLFSR* fibReg)
{
    sf::Color p;
    for (unsigned int x = 0; x < image.getSize().x; x++) {
        for (unsigned int y = 0; y < image.getSize().y; y++) {
            p = image.getPixel(x, y);
            p.r = p.r ^ fibReg->generate(8);
            p.g = p.g ^ fibReg->generate(8);
            p.b = p.b ^ fibReg->generate(8);
            image.setPixel(x, y, p);
        }
    }
}

//The main process takes the following args from command line: input_file, outputfile, and alphanumeric passcode.
//The input image is transformed, and original and post-transformation images are displayed. The transformed image is 
//saved to the output file name.
int main(int argc, char* argv[])
{
    std::string input_file = argv[1], out_file = argv[2], seed = returnEasyHash(argv[3]);

	FibLFSR flfsr(seed);
	sf::Image image_unencrypted;

	if (!image_unencrypted.loadFromFile(input_file))
		return -1;

	sf::Image image_encrypted(image_unencrypted);

   	transform(image_encrypted, &flfsr);

	sf::Vector2u size = image_unencrypted.getSize();
	sf::RenderWindow window(sf::VideoMode(size.x, size.y), "Original");
	sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "After Transform");

	sf::Texture unencrypted_img_texture, encrypted_img_texture;
   	sf::Sprite unencrypted_img_sprite, encrypted_img_sprite;

	unencrypted_img_texture.loadFromImage(image_unencrypted);
	encrypted_img_texture.loadFromImage(image_encrypted);
	unencrypted_img_sprite.setTexture(unencrypted_img_texture);
	encrypted_img_sprite.setTexture(encrypted_img_texture);

	while (window.isOpen() && window2.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		while(window2.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window2.close();
		}

		window.clear(sf::Color::White);
		window2.clear(sf::Color::White);

		window.draw(unencrypted_img_sprite);
		window2.draw(encrypted_img_sprite);

		window.display();
		window2.display();
	}

	if (!image_encrypted.saveToFile(out_file))
		return -1;

	return 0;
}
