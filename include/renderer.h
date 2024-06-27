#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class CPU;

/**
 * @brief Class to render the physics engine using SFML
 */
class Renderer {
public:
	Renderer(int screenWidth, int screenHeight) : screen_width(screenWidth), screen_height(screenHeight) {
		window.create(sf::VideoMode(screenWidth, screenHeight), "Gameboy Emulator");
		window.setFramerateLimit(60);
	}

	/**
	 * @brief Handle user input
	 * @param world World to handle input for
	 */
	bool handleInput(CPU& cpu);

	/**
	 * @brief Prepare the scene for rendering
	 */
	void prepareScene();

	/**
	 * @brief Render the scene
	 */
	void presentScene();

	void loadBitmap(const uint32_t screen_data[160 * 144]);

	inline int getScreenWidth() const { return screen_width; }
	inline int getScreenHeight() const { return screen_height; }
private:
	int screen_width;
	int screen_height;
	sf::RenderWindow window;
};