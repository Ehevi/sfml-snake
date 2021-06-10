#include "../headers/game.hpp"

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
    menuStrings[0].setString("Start");
    menuStrings[1].setString("Settings");
    menuStrings[2].setString("Exit");

    int i = 0;
    for (auto &ms : menuStrings) {
        ms.setFont(font);
        ms.setCharacterSize(40);
        ms.setPosition(SCREEN_WIDTH / 2 - ms.getGlobalBounds().width / 2, 250 + 50 * i);
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
    
    int i = 0;
    for(auto &s : settingsStrings) {
        s.setFont(font);
        s.setCharacterSize(40);
        s.setPosition(SCREEN_WIDTH / 2 - s.getGlobalBounds().width / 2, 100 + 100 * i);
        i++;
    }
    settingsStrings[0].setString("SETTINGS");
    settingsStrings[1].setString("Snake speed");
    settingsStrings[2].setString("Can walk through border");
    settingsStrings[3].setString("Random wall generation");
    settingsStrings[4].setString("Back");
    settingsStrings[5].setString("Slow");
    settingsStrings[6].setString("Fast");
    
    settingsStrings[0].setCharacterSize(80);
    settingsStrings[0].setPosition(SCREEN_WIDTH / 2 - settingsStrings[0].getGlobalBounds().width / 2, 50);

    
    //Set 'Slow' string
    settingsStrings[5].setCharacterSize(40);
    settingsStrings[5].setPosition(SCREEN_WIDTH / 2 - settingsStrings[5].getGlobalBounds().width, 240);
    
    //Set 'Fast' string
    settingsStrings[6].setCharacterSize(40);
    settingsStrings[6].setPosition(SCREEN_WIDTH / 2 + settingsStrings[5].getGlobalBounds().width / 4, 240);
    
    //Set checkboxes
    bordersCheckBox.setSize(Vector2f(20,20));
    bordersCheckBox.setOutlineColor(Color::Red);
    bordersCheckBox.setFillColor(Color::Black);
    bordersCheckBox.setOutlineThickness(5);
    bordersCheckBox.setPosition(SCREEN_WIDTH / 2, 350);
    
    wallsCheckBox.setSize(Vector2f(20,20));
    wallsCheckBox.setOutlineColor(Color::Red);
    wallsCheckBox.setFillColor(Color::Black);
    wallsCheckBox.setOutlineThickness(5);
    wallsCheckBox.setPosition(SCREEN_WIDTH / 2, 450);
    
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
                        setSpeed(2);
                    
                    // set snake fast
                    if(settingsStrings[6].getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left && getSpeed() == 2)
                        setSpeed(5);
                    
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
      if(settingsStrings[5].getGlobalBounds().contains(mouse) && getSpeed() > 2)
          settingsStrings[5].setFillColor(Color::Green);
      else
          settingsStrings[5].setFillColor(Color::White);
      
      //Same as before
      if(settingsStrings[6].getGlobalBounds().contains(mouse) && getSpeed() == 2)
          settingsStrings[6].setFillColor(Color::Green);
      else
          settingsStrings[6].setFillColor(Color::White);
      
      //Highlight choosen option in Snake speed
      if(getSpeed() == 2)
          settingsStrings[5].setFillColor(Color::Yellow);
      else
          settingsStrings[6].setFillColor(Color::Yellow);
      
      
      //Mark or unmark checkbox
      if(borders)
          bordersCheckBox.setFillColor(Color::Yellow);
      else
          bordersCheckBox.setFillColor(Color::Black);
      
      if(generateWalls)
          wallsCheckBox.setFillColor(Color::Yellow);
      else
          wallsCheckBox.setFillColor(Color::Black);
          
      
      window.clear();
      
      for(int i = 0; i < 7; i++)
          window.draw(settingsStrings[i]);
      
      window.draw(bordersCheckBox);
      window.draw(wallsCheckBox);
      
      window.display();
   }
}