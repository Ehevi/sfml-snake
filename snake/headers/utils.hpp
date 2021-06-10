#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

#define _Settings settingsStrings[0]
#define _InitialSpeed settingsStrings[1]
#define _Acceleration settingsStrings[2]
#define _RoundWorld settingsStrings[3]
#define _RandomWallGeneration settingsStrings[4]
#define _Back settingsStrings[5]
#define _Slow settingsStrings[6]
#define _Fast settingsStrings[7]
#define _Ultrafast settingsStrings[8]
#define _CheckBoxSize Vector2f(20,20)

using namespace sf;

void centerHorizontally(Text &text, int y);

void centerHorizontally(RectangleShape &shape, int y);

void centerHorizontally(Text &text1, Text &text2, Text &text3, int y);

void setCheckBox(RectangleShape &checkBox, int y);

#endif //UTILS_HPP
