#ifndef GAME_HPP
#define GAME_HPP

#include "snakesection.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Game {
private:
    // Window
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    vector<SnakeSection> snake;

public:
    Game();

    void input();

    void draw();

    void newSnake();
    void addSnakeSection();

    // The main loop will be in the run function
    void run();

};


#endif //GAME_HPP
