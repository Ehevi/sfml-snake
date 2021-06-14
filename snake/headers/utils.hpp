#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>

#define WINDOW_NAME "Snake"

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

#define FramesPerSecond 60

#define BLOCK 20

#define MENU_STRINGS_N0 3
#define TITLE "SFML Snake"
#define _Start menuStrings[0]
#define _Settings menuStrings[1]
#define _Exit menuStrings[2]

#define TITLE_Y 150
#define MAIN_MARGIN_TOP 250
#define MAIN_SPACE_BETWEEN 50

#define SETTINGS_STRINGS_NO 9
#define _SettingsTitle settingsStrings[0]
#define _InitialSpeed settingsStrings[1]
#define _Acceleration settingsStrings[2]
#define _WallsAround settingsStrings[3]
#define _RandomWallGeneration settingsStrings[4]
#define _Back settingsStrings[5]
#define _Slow settingsStrings[6]
#define _Fast settingsStrings[7]
#define _Ultrafast settingsStrings[8]
#define _CheckBoxSize Vector2f(BLOCK, BLOCK)

#define SETTINGS_MARGIN_TOP 100
#define SETTINGS_SPACE_BETWEEN 80

#define SPEED_OPTIONS_Y 205
#define CHECKBOX_INITIAL_Y 300

#define MESSAGE_LINES_NO 2

#define GAME_TEXT_MARGIN 30

#define _Paused pauseText[0]
#define _PressSpace pauseText[1]
#define _GameOver gameOverText[0]
#define _PressAny gameOverText[1]

#define SPEED_SLOW 2
#define SPEED_FAST 7
#define SPEED_ULTRAFAST 15

#define LARGE_FONT_SIZE 80
#define MEDIUM_FONT_SIZE 40
#define SMALL_FONT_SIZE 25

#define sleep sleep(microseconds(2))

using namespace sf;

const int mediumIndexes[] = {5, 6, 7, 8};

void loadFont(Font &font);

void center(Text &text);

void centerHorizontally(Text &text, int y);
void centerHorizontally(RectangleShape &shape, int y);
void centerHorizontally(Text &text1, Text &text2, Text &text3, int y);

void initCheckBox(RectangleShape &checkBox, int y);
void handleCheckBoxSelection(RectangleShape &checkBox, bool predicate);

void highlightOnHover(Text &text, Vector2f mouse);
void highlightOnHover(RectangleShape &shape, Vector2f mouse);

void highlightChosen(Text &text);

#endif //UTILS_HPP
