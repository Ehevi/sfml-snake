# sfml-snake
obligatory project for my C++ course at AGH UST

1. https://www.sfml-dev.org/tutorials/2.5/start-linux.php

```
sudo apt-get install linsfml-dev
```

2. https://github.com/SFML/SFML/wiki/Tutorial:-Compile-and-Link-SFML-with-Qt-Creator

3. qtcreator-template-sfml from here:
https://github.com/maidis/qtcreator-template-sfml

4. running an app:
```
git clone https://github.com/Ehevi/sfml-snake sfml-snake
cd sfml-snake/snake
mkdir build
cd build
cmake ..
make
./snake
```

5. cleanup:
```
cd ..
rm -Rf build
# or if you wanna remove everything
# cd ../../..
# rm -Rf sfml-snake
```

