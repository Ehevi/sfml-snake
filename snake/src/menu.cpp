#include "../headers/game.hpp"
#include "../headers/utils.hpp"
#include <set>

void Game::handleMenu() {
    while(1) {
        switch(currentGameState) {
            case GameState::MENU:
                displayMenu();
                break;
            case GameState::SETTINGS:
                displaySettings();
                break;
            case GameState::PLAYING:
                startGame();
                return;
            case GameState::EXIT:
                window.close();
                return;
            default:
                break;
        }
        sleep(microseconds(2));
    }
}

void Game::displayMenu() {
    title.setFont(font);
    title.setString("SFML Snake");
    title.setCharacterSize(80);
    centerHorizontally(title, 150);
    
    menuStrings[0].setString("Start");
    menuStrings[1].setString("Settings");
    menuStrings[2].setString("Exit");

    int i = 0;
    for (auto &ms : menuStrings) {
        ms.setFont(font);
        ms.setCharacterSize(40);
        centerHorizontally(ms, 250 + 50 * i);
        i++;
    }

    Event event;
    
    while(currentGameState == Game::MENU) {
        Vector2f mouse(Mouse::getPosition(window));
        
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    currentGameState = GameState::EXIT;
                    return;
                case Event::KeyPressed:
                    switch (event.key.code) {
                        case Keyboard::Escape:
                            currentGameState = GameState::EXIT;
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
                        if(menuStrings[0].getGlobalBounds().contains(mouse))
                            startGame();
                
                        if(menuStrings[1].getGlobalBounds().contains(mouse)) {
                            displaySettings();
                            currentGameState = GameState::SETTINGS;
                        }
                
                        if(menuStrings[2].getGlobalBounds().contains(mouse)) 
                            currentGameState = GameState::EXIT;
                    }
                    break;
                default:
                    break;

            }
        }
        
        window.clear();

        window.draw(title);
        for(auto &ms : menuStrings) {
            window.draw(ms);
            ms.getGlobalBounds().contains(mouse)? ms.setFillColor(Color::Green) : ms.setFillColor(Color::White);
        }
            
        window.display();
    }
}

void Game::displaySettings() {
    // default settings
    speed = SPEED_SLOW;
    acceleration = true;
    wallGeneration = false;
    wallsAround = false;
    
    _Settings.setString("Settings");
    _InitialSpeed.setString("Initial speed");
    _Acceleration.setString("Acceleration");
    _WallsAround.setString("Walls around");
    _RandomWallGeneration.setString("Random wall generation");
    _Back.setString("Back");
    _Slow.setString("Slow");
    _Fast.setString("Fast");
    _Ultrafast.setString("Ultrafast");
    
    
    std::set <size_t> size40;
    int n = sizeof(size40Indexes) / sizeof(size40Indexes[0]);
    size40.insert(size40Indexes, size40Indexes + n);
    //for (size_t i = 0; i < SETTINGS_STRINGS_NO; i++) {
    int i =0;
    for(auto &s : settingsStrings) {
        //Text s = settingsStrings[i];
        s.setFont(font);
        // index ??
        // settingsStrings[i].setCharacterSize(size40.find(i) != size40.end()? 40 : 25);
        // size40.find(i) != size40.end() ? settingsStrings[i].setCharacterSize(40) : settingsStrings[i].setCharacterSize(25);
        // i == _Slow.index ||
        // s == _Slow || s == _Fast || s == _Ultrafast || s == _Back ? s.setCharacterSize(40) : s.setCharacterSize(25);
        s.setCharacterSize(25);
        centerHorizontally(s, 100 + 80 * i);
        i++;
    }

    _Settings.setCharacterSize(80);
    centerHorizontally(_Settings, 50);

    centerHorizontally(_Slow, _Fast, _Ultrafast, 205);
    _Slow.setCharacterSize(40);
    _Fast.setCharacterSize(40);
    _Ultrafast.setCharacterSize(40);
    _Back.setCharacterSize(40);
    
    initCheckBox(accelerationCheckBox, 300);
    initCheckBox(wallGenerationCheckBox, 400);
    initCheckBox(wallsAroundCheckBox, 500);
    
    Event event;

    while(currentGameState == Game::SETTINGS) {
        Vector2f mouse(Mouse::getPosition(window));
      
        while(window.pollEvent(event)) {
            switch (event.type) {
                case Event::MouseButtonReleased:
                    if(_Back.getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left)
                        setCurrentGameState(GameState::MENU);
                    
                    if(_Slow.getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left)
                        speed = SPEED_SLOW;
                    
                    if(_Fast.getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left)
                        speed = SPEED_FAST;
                    
                    if(_Ultrafast.getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left)
                        speed = SPEED_ULTRAFAST;
                    
                    if(accelerationCheckBox.getGlobalBounds().contains(mouse)) {
                        acceleration =! acceleration;
                    }

                    // wallGeneration flag
                    if(wallGenerationCheckBox.getGlobalBounds().contains(mouse)) {
                        wallGeneration = !wallGeneration;
                    }

                    // wall generation flag
                    if (wallsAroundCheckBox.getGlobalBounds().contains(mouse)) {
                        wallsAround = !wallsAround;
                    }

                    break;
                case Event::KeyPressed:
                    if (event.key.code == Keyboard::Escape)
                        setCurrentGameState(GameState::MENU);
                    break;
                case Event::Closed:
                    setCurrentGameState(GameState::EXIT);
                    return;
                default:
                    break;
            }   
        }
      
        highlightOnHover(_Slow, mouse);
        highlightOnHover(_Fast, mouse);
        highlightOnHover(_Ultrafast, mouse);
        highlightOnHover(_Back, mouse);
        
        // TODO : handle selection

        /*
        //Highlight choosen option in Snake speed
        speed == 2 ? settingsStrings[5].setFillColor(Color::Yellow) : settingsStrings[6].setFillColor(Color::Yellow);
      
        */
        // mark or unmark checkboxes
        wallGenerationCheckBox.setFillColor(wallGeneration ? Color::Yellow : Color::Black);
        wallsAroundCheckBox.setFillColor(wallsAround ? Color::Yellow : Color::Black);
      
        window.clear();
      
        for (auto &s : settingsStrings)
            window.draw(s);
      
        window.draw(accelerationCheckBox);
        window.draw(wallGenerationCheckBox);
        window.draw(wallsAroundCheckBox);
      
        window.display();
    }
}
