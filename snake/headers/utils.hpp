#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

#define MENU_STRINGS_N0 3
#define SETTINGS_STRINGS_NO 9
#define _Settings settingsStrings[0]
#define _InitialSpeed settingsStrings[1]
#define _Acceleration settingsStrings[2]
#define _WallsAround settingsStrings[3]
#define _RandomWallGeneration settingsStrings[4]
#define _Back settingsStrings[5]
#define _Slow settingsStrings[6]
#define _Fast settingsStrings[7]
#define _Ultrafast settingsStrings[8]
#define _CheckBoxSize Vector2f(20,20)

#define SPEED_SLOW 2
#define SPEED_FAST 7
#define SPEED_ULTRAFAST 15

using namespace sf;

const int size40Indexes[] = {5, 6, 7, 8};

void centerHorizontally(Text &text, int y);

void centerHorizontally(RectangleShape &shape, int y);

void centerHorizontally(Text &text1, Text &text2, Text &text3, int y);

void initCheckBox(RectangleShape &checkBox, int y);

void handleSpeedSelection();

void highlightOnHover(Text &text, Vector2f mouse);

void highlightChosenOption();

#endif //UTILS_HPP
