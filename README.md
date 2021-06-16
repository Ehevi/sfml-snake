# SFML snake :snake:
## About the game
This game is just like life - there is no way to go through it without ending up dead. The player has longings and desires that reality cannot fulfil; they require meaning in a meaningless world. Perhaps fulfilment could be found if one seeks pleasure in materialistic goods...? And so, despite the inherent meaninglessness of the digital snake's life, the player attempts to eat apples by running into them with its head - creating a metaphor for man's ability to make up personal meaning in a hollow life the only real purpose of which is to end eventually.

Quite ironically, the snake's length increases with each apple consumed, making the player attempts to avoid collision progressively more difficult.

And no matter how much one already ate, apples keep appearing, every next one more tempting. There never comes a point of complete satisfaction - one only wants more and more. At least until the crazy pursuit for a substitute of happiness leads them either to crash into a wall or to start devouring themselves, as the game ends when the snake hits a wall or its own body.

Defeat resulting in death is the only possible outcome of the game.

### How to play
Choose the settings you are interested in (explained below) and click `Start`. Control the snake using keyboard arrows. Just move around until you die. And if you lack moral standards, you can also use the space button to pause the game.

Some people feel the need of bragging about their achievements, so you can find the score field in the upper left corner. Now you can compare yourself to others and prove them your superiority as you've wasted more time playing that game. Your mother would be proud.

### Settings
You can choose the initial speed of the snake: `Slow` / `Fast` / `Ultrafast`, which I believe is self-explanatory.

If the `Acceleration` checkbox is marked, snake not only becomes longer, but also moves faster with each apple eaten.

`Walls around` option frames the board with a border fence, so that now with every try of escape you will get yourself killed. It is rather just an visualization of you psychic inprisonment than a real obstacle. I mean, when you unmark this option, you don't really have _that much_ more space for yourself. And you can't break free anyway, the game will place you back at the opposite side of the board. Just decide what gives you more pain, barbed wire suicide or the conscious existence itself.

`Random wall generation` will award you with an additional wall each time you eat an apple.
#### Default settings:

| _Initial speed:_ | `Slow` |
|----------|-------------|
- [x] Acceleration
- [ ] Walls around
- [ ] Random wall generation

## Running an app
### Prerequisites
#### Make sure you will be able to compile the project
`g++` compiler, `cmake` etc. are needed. Most likely you already have them installed, but if you feel like it, run these commands just in case :see_no_evil:
```shell
sudo snap install cmake --classic
sudo apt-get update
sudo apt-get install build-essential g++ cmake libjpeg-dev libfreetype6-dev libglew-dev libxrandr-dev libopenal-dev libsndfile-dev libgl1-mesa-dev libxcb-image0-dev libudev-dev
```
#### SFML installation
```shell
sudo apt-get install libsfml-dev
```

### Running the game
```
git clone https://github.com/Ehevi/sfml-snake sfml-snake
cd sfml-snake/snake
mkdir build
cd build
cmake ..
make
./snake
```

### Cleanup :broom:
##### soft version
```
cd ..
rm -Rf build
```

##### ...or if following the steps above was the greatest mistake of your life :broken_heart:
```
cd ../../..
rm -Rf sfml-snake
```

## Files I am not the author of:
- [snake/cmake/FindSFML.cmake](https://github.com/Ehevi/sfml-snake/blob/main/snake/cmake/FindSFML.cmake) file comes from [SFML Game Development Book](https://github.com/SFML/SFML-Game-Development-Book/blob/master/CMake/FindSFML.cmake) ([see the license file](https://github.com/SFML/SFML-Game-Development-Book/blob/master/License.txt))
- [snake/font/Poppins-Regular.otf](https://github.com/Ehevi/sfml-snake/blob/main/snake/font/Poppins-Regular.otf) ([see the license file](https://github.com/Ehevi/sfml-snake/blob/main/snake/font/SIL%20Open%20Font%20License.txt))
