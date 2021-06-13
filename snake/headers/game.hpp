#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque>
#include "snakesection.hpp"
#include "food.hpp"
#include "utils.hpp"
#include "wall.hpp"
#include "snake.hpp"

using namespace sf;
using namespace std;

class Game {
private:
    int currentGameState;
    int prevGameState; // the last state the game was in when pausing
    
    Vector2f resolution;

    deque<int> directionQueue; // queue for direction key presses

    int initialSpeed;
    int speed;
    int sectionsToAdd; // how many sections to add to the snake
    int score;

    Food food;
    Snake snake;
    vector<Wall> walls;

    Time timeSinceLastMove;
    Time pausedSince;
    Time totalPausedTime;
    Clock gameClock;

    Font font;
    
    Text scoreText;
    Text gameTimeText;
    Text pauseText;
    Text gameOverText;

    bool acceleration;
    bool wallsAround;
    bool wallGeneration;

public:
    Game() {};

    enum Direction {UP, DOWN, RIGHT, LEFT};
    enum GameState {RUNNING, PAUSED, GAMEOVER, EXIT};

    void handleInput(RenderWindow &window);
    void addDirection(int newDirection);
    void update();

    void draw(RenderWindow &window);

    void moveFood();

    void buildWallsAround();
    void generateRandomWall();

    void newGame(RenderWindow &window, Vector2f gameResolution, int newInitialSpeed, bool accelerationWanted, bool wallsAround, bool wallGenerationWanted);

    void handlePause();

    void run(RenderWindow &window); // main loop

};

#endif //GAME_HPP
