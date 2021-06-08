#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../headers/snakesection.hpp"
#include <vector>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

using namespace sf;
using namespace std;

class Game {
private:
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    vector<SnakeSection> snake;

public:
    Game();

    void enableClose();

    void draw();

    void run();

    void newSnake();
    void addSnakeSection();
};

#endif //GAME_HPP
