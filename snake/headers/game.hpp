#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque>
#include "snakesection.hpp"
#include "food.hpp"
#include "utils.hpp"

#define head snake[0]
#define snakeInitialPosition {Vector2f(100, 100), Vector2f(80, 100), Vector2f(60, 100)}

using namespace sf;
using namespace std;

class Game {
private:
    int currentGameState;
    int prevGameState; // the last state the game was in when pausing
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    vector<SnakeSection> snake;

    int snakeDirection;
    deque<int> directionQueue; // queue for direction key presses
    int speed;
    int sectionsToAdd; // how many sections to add to the snake

    Food food;

    Time timeSinceLastMove;

    // Menu
    Font font;

    Text title;
    Text menuStrings[3];
    Text settingsStrings[7];
    Text score;
    Text gameTime;
    Text gameOverStrings[4];
    Text pauseString;

    bool generateWalls;
    bool borders;

    RectangleShape speedCheckBox;
    RectangleShape wallsCheckBox;
    RectangleShape bordersCheckBox;

    // Menu end

public:
    Game();

    enum Direction {UP, DOWN, RIGHT, LEFT};
    enum GameState {MENU, SETTINGS, PLAYING, PAUSED, GAMEOVER, EXIT};

    int getCurrentGameState() {
        return currentGameState;
    };

    void setCurrentGameState(int newState) {
        prevGameState = currentGameState;
        currentGameState = newState;
    }

    void handleInput();
    void addDirection(int newDirection);
    void update();

    void draw();

    void newSnake();
    void addSnakeSection();

    void moveFood();

    void startGame();
    void handleMenu();

    void handlePause();

    void run(); // main loop

    // menu
    void displayMenu();
    void displaySettings();
    // end menu

};

#endif //GAME_HPP
