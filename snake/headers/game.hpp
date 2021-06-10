#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque>
#include "../headers/snakesection.hpp"
#include "../headers/food.hpp"

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800
#define head snake[0]
#define snakeInitialPosition {Vector2f(100, 100), Vector2f(80, 100), Vector2f(60, 100)}

using namespace sf;
using namespace std;

class Game {
private:
    int currentGameState;
    int lastGameState; // the last state the game was in when pausing
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

public:
    Game();

    enum Direction {UP, DOWN, RIGHT, LEFT};
    enum GameState {MENU, OPTIONS, PLAYING, PAUSED, GAMEOVER, EXIT};
    
    void handleInput();
    void addDirection(int newDirection);
    void update();

    void draw();

    void newSnake();
    void addSnakeSection();

    void moveFood();

    void startGame();

    void handlePause();

    void run(); // main loop

};

#endif //GAME_HPP
