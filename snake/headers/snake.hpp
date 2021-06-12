#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "snakesection.hpp"
// #include "game.hpp"

#define snakeInitialPosition {Vector2f(100, 100), Vector2f(80, 100), Vector2f(60, 100)}
#define head sections[0]

using namespace sf;
using namespace std;

class Snake {
private:
    vector<SnakeSection> sections;
    int direction;

public:
    Snake() {};
    
    // SnakeSection head();
    int getDirection();
    void setDirection(int direction);
    void addSection();
    void newSnake();
    bool intersects(const Rect<float> &rectangle);
    bool ateSelf();
    bool ate(const Rect<float> &rectangle);
    // bool ateApple(const Rect<float> &rectangle);
    // bool eats(const Rect<float> &rectangle);
    // bool intersects(FloatRect<float>(float x, float y, float a, float b));

    void update();
    //bool eats(const Rect<float> &rectangle);
    void draw(RenderWindow &window);
};

#endif //SNAKE_HPP