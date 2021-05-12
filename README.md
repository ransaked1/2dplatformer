# 2D Platformer
A basic 2D plartformer in C++

## Getting Started

### Prerequisites
To run the game you will need the SFML library, you can download by typing:
```
sudo apt-get install libsfml-dev
```
Source: https://www.sfml-dev.org/tutorials/2.5/start-linux.php

Also, to build the game you need the G++ compiler:
```
sudo apt-get install g++
```
&nbsp;
### Installing
Build the project in the project root folder:
```
make
```
Running the game:
```
./game
```
&nbsp;
### Additional build options
Delete the .obj files generated:
```
make clean
```
Keep only the initial project files:
```
make fclean
```
Rebuild the project (If you made changes to the code):
```
make re
```
&nbsp;
### Potential Issues
* SFML uses the X11 server for display. If you are running the app on a Windows 10 Ubuntu Subsystem, you will need to download and setup Xming in Windows: https://xming.en.softonic.com/. Then export the window path in your Ubuntu environment and run the game:
```
export DISPLAY=:0.0
```
* If the game won't open on your Linux or MacOS machine you may be missing the X11 server packages. You can download them by typing:
```
sudo apt-get install xorg openbox
```
And export the windows path:
```
export DISPLAY=:0.0
```
&nbsp;
## Game Controls

W, Up Arrow - Jump

A, Left Arrow - Left

D, Right Arrow - Right

&nbsp;
## Built With
* [SFML 2.5.1](https://www.sfml-dev.org/documentation/2.5.1/) - The graphical library used.
