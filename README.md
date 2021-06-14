# SFML snake :snake:
obligatory project for my C++ course at AGH UST

## General idea
### About the game
### How to play
### Settings

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
- [snake/font/Poppins-Regular.otf](https://github.com/Ehevi/sfml-snake/blob/main/snake/font/Poppins-Regular.otf) ([see the license file](https://github.com/Ehevi/sfml-snake/blob/main/snake/font/SIL-Open-Font-License.txt))
