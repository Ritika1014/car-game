# Car Game

A small Windows console game written in C++. Move your car left and right to
avoid the oncoming cars and increase your score.

## Requirements

- Windows
- A C++ compiler with MinGW support, such as `g++`

This program uses Windows-specific console APIs (`conio.h` and `windows.h`), so
it is intended to be built and run on Windows.

## Build

Open Command Prompt or PowerShell in this folder and run:

```powershell
g++ -std=c++11 -Wall -Wextra -pedantic car_game.cpp -o car_game.exe
```

## Run

```powershell
.\car_game.exe
```

## Controls

- Choose `1` in the menu to start the game.
- Press `A` to move left.
- Press `D` to move right.
- Press `Esc` during gameplay to return to the menu.
- Choose `2` to view the in-game instructions or `3` to quit.
