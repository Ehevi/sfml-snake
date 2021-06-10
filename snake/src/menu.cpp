#include "../headers/game.hpp"
#include "../headers/utils.hpp"

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
    speed = 2;
    borders = false;
    generateWalls = false;
    
    _Settings.setString("Settings");
    _InitialSpeed.setString("Initial speed");
    _Acceleration.setString("Acceleration");
    _RoundWorld.setString("Round world");
    _RandomWallGeneration.setString("Random wall generation");
    _Back.setString("Back");
    _Slow.setString("Slow");
    _Fast.setString("Fast");
    _Ultrafast.setString("Ultrafast");
    
    int i = 0;
    for(auto &s : settingsStrings) {
        s.setFont(font);
        s.setCharacterSize(40);
        centerHorizontally(s, 100 + 100 * i);
        i++;
    }

    _Settings.setCharacterSize(80);
    centerHorizontally(_Settings, 50);

    centerHorizontally(_Slow, _Fast, _Ultrafast, 240);
    
    setCheckBox(bordersCheckBox, 350);
    setCheckBox(wallsCheckBox, 450);
    
    Event event;

    while(currentGameState == Game::SETTINGS) {
        Vector2f mouse(Mouse::getPosition(window));
      
        while(window.pollEvent(event)) {
            switch (event.type) {
                case Event::MouseButtonReleased:
                    // "Back" in settings
                    if(settingsStrings[4].getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left)
                        setCurrentGameState(GameState::MENU);
                    
                    // set snake slow
                    if(settingsStrings[5].getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left && speed > 2)
                        speed = 2;
                    
                    // set snake fast
                    if(settingsStrings[6].getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left && speed == 2)
                        speed = 5;
                    
                    // borders flag
                    if(bordersCheckBox.getGlobalBounds().contains(mouse)) {
                        borders = !borders;
                    }

                    // wall generation flag
                    if (wallsCheckBox.getGlobalBounds().contains(mouse)) {
                        generateWalls = !generateWalls;
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
      
        if(settingsStrings[4].getGlobalBounds().contains(mouse)) //Change 'Back' string color to green on mouse hover
            settingsStrings[4].setFillColor(Color::Green);
        else
            settingsStrings[4].setFillColor(Color::White);
      
        //Highlight string on mouse hover when it is not choosen (yellow)
        if(settingsStrings[5].getGlobalBounds().contains(mouse) && speed > 2)
            settingsStrings[5].setFillColor(Color::Green);
        else
            settingsStrings[5].setFillColor(Color::White);
      
      //Same as before
        if(settingsStrings[6].getGlobalBounds().contains(mouse) && speed == 2)
            settingsStrings[6].setFillColor(Color::Green);
        else
            settingsStrings[6].setFillColor(Color::White);
      
        //Highlight choosen option in Snake speed
        speed == 2 ? settingsStrings[5].setFillColor(Color::Yellow) : settingsStrings[6].setFillColor(Color::Yellow);
      
        // mark or unmark checkboxes
        bordersCheckBox.setFillColor(borders ? Color::Yellow : Color::Black);
        wallsCheckBox.setFillColor(generateWalls ? Color::Yellow : Color::Black);
      
        window.clear();
      
        for (auto &s : settingsStrings)
            window.draw(s);
      
        window.draw(bordersCheckBox);
        window.draw(wallsCheckBox);
      
        window.display();
    }
}
