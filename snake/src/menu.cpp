#include "../headers/game.hpp"
#include "../headers/utils.hpp"
#include "../headers/menu.hpp"
#include <set>

Menu::Menu() {
    loadFont(font);
    resolution = Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
    window.create(VideoMode(resolution.x, resolution.y), WINDOW_NAME, Style::Default);
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
    title.setString(TITLE);
    title.setCharacterSize(LARGE_FONT_SIZE);
    centerHorizontally(title, TITLE_Y);
    
    _Start.setString("Start");
    _Settings.setString("Settings");
    _Exit.setString("Exit");

    int i = 0;
    for (auto &ms : menuStrings) {
        ms.setFont(font);
        ms.setCharacterSize(MEDIUM_FONT_SIZE);
        centerHorizontally(ms, MAIN_MARGIN_TOP + MAIN_SPACE_BETWEEN * i);
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
                        if (_Start.getGlobalBounds().contains(mouse))
                            menuState = MenuState::PLAYING;
                
                        if (_Settings.getGlobalBounds().contains(mouse))
                            menuState = MenuState::SETTINGS;
                
                        if (_Exit.getGlobalBounds().contains(mouse)) 
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
    _SettingsTitle.setString("Settings");
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
        centerHorizontally(settingsStrings[i], SETTINGS_MARGIN_TOP + SETTINGS_SPACE_BETWEEN * i);
    }

    _SettingsTitle.setCharacterSize(LARGE_FONT_SIZE);
    centerHorizontally(_SettingsTitle, SETTINGS_MARGIN_TOP / 2);

    centerHorizontally(_Slow, _Fast, _Ultrafast, SPEED_OPTIONS_Y);
    
    initCheckBox(accelerationCheckBox, CHECKBOX_INITIAL_Y);
    initCheckBox(wallsAroundCheckBox, CHECKBOX_INITIAL_Y + SETTINGS_SPACE_BETWEEN);
    initCheckBox(wallGenerationCheckBox, CHECKBOX_INITIAL_Y + SETTINGS_SPACE_BETWEEN * 2);
    
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
