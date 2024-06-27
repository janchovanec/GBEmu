#include "renderer.h"
#include "cpu.h"
#include <iostream>


bool Renderer::handleInput(CPU& cpu) {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::KeyPressed:
				switch (event.key.code) {
					case sf::Keyboard::W:
						cpu.keyPressed(0b100); // Forwards
						break;
					case sf::Keyboard::A:
						cpu.keyPressed(0b10); // Left
						break;
					case sf::Keyboard::S:
						cpu.keyPressed(0b1000); // Backwards
						break;
					case sf::Keyboard::D:
						cpu.keyPressed(0b1); // Right
						break;
					case sf::Keyboard::J:
						cpu.keyPressed(0b10000); // A
						break;
					case sf::Keyboard::K:
						cpu.keyPressed(0b100000); // B
						break;
					case sf::Keyboard::Space:
						cpu.keyPressed(0b1000000); // Select
						break;
					case sf::Keyboard::LShift:
						cpu.keyPressed(0b10000000); // Start
						break;
					default:
						break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code) {
					case sf::Keyboard::W:
						cpu.keyReleased(0b100); // Forwards
						break;
					case sf::Keyboard::A:
						cpu.keyReleased(0b10); // Left
						break;
					case sf::Keyboard::S:
						cpu.keyReleased(0b1000); // Backwards
						break;
					case sf::Keyboard::D:
						cpu.keyReleased(0b1); // Right
						break;
					case sf::Keyboard::J:
						cpu.keyReleased(0b10000); // A
						break;
					case sf::Keyboard::K:
						cpu.keyReleased(0b100000); // B
						break;
					case sf::Keyboard::Space:
						cpu.keyReleased(0b1000000); // Select
						break;
					case sf::Keyboard::LShift:
						cpu.keyReleased(0b10000000); // Start
						break;
					default:
						break;
				}
				break;

			case sf::Event::Closed:
				window.close();
				return false;
			default:
				break;
		}
	}
	return true;
}

void Renderer::prepareScene() {
	window.clear();
}

void Renderer::presentScene() {
	window.display();
}

void Renderer::loadBitmap(const uint32_t screen_data[160 * 144])
{
	sf::Texture source;
	sf::Sprite sprite;

	source.create(160, 144);
	source.update((sf::Uint8*)screen_data);
	sprite.setTexture(source);

	window.draw(sprite);
}