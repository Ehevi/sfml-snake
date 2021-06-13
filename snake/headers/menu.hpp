#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "game.hpp"

using namespace sf;

class Menu {
private:
    Game game; //
    
    int menuState; //

    Vector2f resolution; //
    RenderWindow window; //
    const unsigned int FPS = 60; //
    static const Time TimePerFrame; //

    Font font; //

    Text title;
    Text menuStrings[MENU_STRINGS_N0];
    Text settingsStrings[SETTINGS_STRINGS_NO];
    Text score;
    Text gameTime;
    Text pauseText;
    Text gameOverText;

    int initialSpeed;
    bool acceleration;
    bool wallsAround;
    bool wallGeneration;

    RectangleShape accelerationCheckBox;
    RectangleShape wallsAroundCheckBox;
    RectangleShape wallGenerationCheckBox;

public:
    Menu();

    enum MenuState {MAIN, SETTINGS, PLAYING, EXIT};
    
    // void start(); // init?
    void handleState();//int gameState, RenderWindow window);
    void displayMenu();
    void displaySettings();
    // void draw();
    // void newGame();
    // explicit Wall(Vector2f Position);

    // Vector2f getPosition();
    // RectangleShape getShape();

};

#endif //MENU_HPP