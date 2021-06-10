#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

using namespace sf;

void centerHorizontally(Text &text, int y);

void centerHorizontally(RectangleShape &shape, int y);

#endif //UTILS_HPP
