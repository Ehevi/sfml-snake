#include "../headers/game.hpp"
#include "../headers/utils.hpp"
#include "../headers/menu.hpp"
#include <set>

const sf::Time Menu::TimePerFrame = seconds(1.f/60.f);

Menu::Menu() {
    loadFont(font);
    resolution = Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
    window.create(VideoMode(resolution.x, resolution.y), "Snake", Style::Default);
    window.setFramerateLimit(FPS);

    menuState = MenuState::MAIN;
    
    // default settings
    initialSpeed = SPEED_SLOW;
    acceleration = true;
    wallsAround = false;
    wallGeneration = false;
}

void Menu::handleState() {
    while (true) {
        switch (menuState) {
            case MenuState::MAIN:
                displayMenu();
                break;
            case MenuState::SETTINGS:
                displaySettings();
                break;
            case MenuState::PLAYING:
                game.newGame(window, resolution, initialSpeed, acceleration, wallsAround, wallGeneration);
                menuState = MenuState::MAIN; // display main menu after the game ends
                break;
            case MenuState::EXIT:
                window.close();
                return;
            default:
                break;
        }
        sleep;
    }
}

void Menu::displayMenu() {
    title.setFont(font);
    title.setString("SFML Snake");
    title.setCharacterSize(LARGE_FONT_SIZE);
    centerHorizontally(title, 150);
    
    menuStrings[0].setString("Start");
    menuStrings[1].setString("Settings");
    menuStrings[2].setString("Exit");

    int i = 0;
    for (auto &ms : menuStrings) {
        ms.setFont(font);
        ms.setCharacterSize(MEDIUM_FONT_SIZE);
        centerHorizontally(ms, 250 + 50 * i);
        i++;
    }

    Event event;
    
    while (menuState == MenuState::MAIN) {
        Vector2f mouse(Mouse::getPosition(window));
        
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    menuState = MenuState::EXIT;
                    return;
                case Event::KeyPressed:
                    switch (event.key.code) {
                        case Keyboard::Escape:
                            menuState = MenuState::EXIT;
                            return;
                        case Keyboard::Up:
                            break;
                        case Keyboard::Down:
                            break;
                        case Keyboard::Space:
                            break;
                        default:
                            break;
                    }
                    break;
                case Event::MouseButtonReleased:
                    if (event.mouseButton.button == Mouse::Left) {
                        if (menuStrings[0].getGlobalBounds().contains(mouse))
                            menuState = MenuState::PLAYING;
                
                        if (menuStrings[1].getGlobalBounds().contains(mouse))
                            menuState = MenuState::SETTINGS;
                
                        if (menuStrings[2].getGlobalBounds().contains(mouse)) 
                            menuState = MenuState::EXIT;
                    }
                    break;
                default:
                    break;

            }
        }
        
        window.clear();

        window.draw(title);
        for (auto &ms : menuStrings) {
            highlightOnHover(ms, mouse);
            window.draw(ms);
        }
        
        window.display();
    }
}

void Menu::displaySettings() {
    _Settings.setString("Settings");
    _InitialSpeed.setString("Initial speed");
    _Acceleration.setString("Acceleration");
    _WallsAround.setString("Walls around");
    _RandomWallGeneration.setString("Random wall generation");
    _Back.setString("Back");
    _Slow.setString("Slow");
    _Fast.setString("Fast");
    _Ultrafast.setString("Ultrafast");
    
    std::set <size_t> mediumSet;
    int n = sizeof(mediumIndexes) / sizeof(mediumIndexes[0]);
    mediumSet.insert(mediumIndexes, mediumIndexes + n);
    for (size_t i = 0; i < SETTINGS_STRINGS_NO; i++) {
        settingsStrings[i].setFont(font);
        settingsStrings[i].setCharacterSize(mediumSet.find(i) != mediumSet.end()? MEDIUM_FONT_SIZE : SMALL_FONT_SIZE);
        centerHorizontally(settingsStrings[i], 100 + 80 * i);
    }

    _Settings.setCharacterSize(LARGE_FONT_SIZE);
    centerHorizontally(_Settings, 50);

    centerHorizontally(_Slow, _Fast, _Ultrafast, 205);
    
    initCheckBox(accelerationCheckBox, 300);
    initCheckBox(wallsAroundCheckBox, 380);
    initCheckBox(wallGenerationCheckBox, 460);
    
    Event event;

    while (menuState == MenuState::SETTINGS) {
        Vector2f mouse(Mouse::getPosition(window));
      
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::MouseButtonReleased:
                    if (event.mouseButton.button == Mouse::Left) {
                        if (_Back.getGlobalBounds().contains(mouse))
                            menuState = MenuState::MAIN;
                        
                        if (_Slow.getGlobalBounds().contains(mouse))
                            initialSpeed = SPEED_SLOW;
                    
                        if (_Fast.getGlobalBounds().contains(mouse))
                            initialSpeed = SPEED_FAST;
                    
                        if (_Ultrafast.getGlobalBounds().contains(mouse))
                            initialSpeed = SPEED_ULTRAFAST;

                        if (accelerationCheckBox.getGlobalBounds().contains(mouse))
                            acceleration = !acceleration;
                        
                        if (wallGenerationCheckBox.getGlobalBounds().contains(mouse))
                            wallGeneration = !wallGeneration;

                        if (wallsAroundCheckBox.getGlobalBounds().contains(mouse))
                            wallsAround = !wallsAround;

                    }
                    break;
                case Event::KeyPressed:
                    if (event.key.code == Keyboard::Escape)
                        menuState = MenuState::MAIN;
                    break;
                case Event::Closed:
                    menuState = MenuState::EXIT;
                    return;
                default:
                    break;
            }   
        }
      
        highlightOnHover(_Slow, mouse);
        highlightOnHover(_Fast, mouse);
        highlightOnHover(_Ultrafast, mouse);
        highlightOnHover(_Back, mouse);
        highlightOnHover(accelerationCheckBox, mouse);
        highlightOnHover(wallGenerationCheckBox, mouse);
        highlightOnHover(wallsAroundCheckBox, mouse);

        switch (initialSpeed) {
            case SPEED_SLOW:
                highlightChosen(_Slow);
                break;
            case SPEED_FAST:
                highlightChosen(_Fast);
                break;
            case SPEED_ULTRAFAST:
                highlightChosen(_Ultrafast);
                break;
            default:
                break;
        }

        handleCheckBoxSelection(accelerationCheckBox, acceleration);
        handleCheckBoxSelection(wallGenerationCheckBox, wallGeneration);
        handleCheckBoxSelection(wallsAroundCheckBox, wallsAround);
        
        window.clear();
      
        for (auto &s : settingsStrings)
            window.draw(s);
      
        window.draw(accelerationCheckBox);
        window.draw(wallGenerationCheckBox);
        window.draw(wallsAroundCheckBox);
      
        window.display();
    }
}
