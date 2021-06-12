#include "../headers/snake.hpp"
#include "../headers/game.hpp"

void Snake::addSection() {
    Vector2f newSectionPosition = sections[sections.size() - 1].getPosition();
    sections.emplace_back(newSectionPosition);
}

void Snake::newSnake() {
    sections.clear();
    direction = Game::Direction::RIGHT;
    for (auto &s : snakeInitialPosition)
        sections.emplace_back(s);
}

int Snake::getDirection() {
    return direction;
}

void Snake::setDirection(int newDirection) {
    direction = newDirection;
}

bool Snake::intersects(const Rect<float> &rectangle) {
    for (auto &s : sections)
      if (s.getShape().getGlobalBounds().intersects(rectangle))
        return true;
    
    return false;
}

void Snake::update() {
    Vector2f thisSectionPosition = head.getPosition();
    Vector2f lastSectionPosition = thisSectionPosition;

    // update the head position
    switch (direction) {
        case Game::Direction::UP:
            head.setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - BLOCK));
            break;
        case Game::Direction::DOWN:
            head.setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + BLOCK));
            break;
        case Game::Direction::RIGHT:
            head.setPosition(Vector2f(thisSectionPosition.x + BLOCK, thisSectionPosition.y));
            break;
        case Game::Direction::LEFT:
            head.setPosition(Vector2f(thisSectionPosition.x - BLOCK, thisSectionPosition.y));
            break;
        default:
            break;
    }

    // update tail positions
    for (size_t s = 1; s < sections.size(); s++) {
        thisSectionPosition = sections[s].getPosition();
        sections[s].setPosition(lastSectionPosition);
        lastSectionPosition = thisSectionPosition;
    }

    // run snake section update function
    for (auto &s : sections)
        s.update();
}

bool Snake::ateSelf() {
    for (size_t s = 1; s <sections.size(); s++)
        if (head.getShape().getGlobalBounds().intersects(sections[s].getShape().getGlobalBounds()))
            return true;

    return false;
}

bool Snake::ate(const Rect<float> &rectangle) {
    return head.getShape().getGlobalBounds().intersects(rectangle);
}

void Snake::draw(RenderWindow &window) {
    for(auto &s : sections)
        window.draw(s.getShape());
}
