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

using namespace sf;
using namespace std;

class Game {
private:
    enum GameState {MENU, OPTIONS, PLAYING, OVER, EXIT};
    GameState gameState;
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
    
    void handleInput();
    void addDirection(int newDirection);
    void update();

    void draw();

    void newSnake();
    void addSnakeSection();

    void moveFood();

    void run(); // main loop

};

#endif //GAME_HPP
