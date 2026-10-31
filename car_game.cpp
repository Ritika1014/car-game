#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <conio.h> // For getch()
#include <windows.h> // For Sleep

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

using namespace std; 

int enemyY[3] = {0};
int enemyX[3] = {0};
bool enemyFlag[3] = {false};

char car[4][4] = {
    ' ', '#', '#', ' ', 
    '#', '#', '#', '#', 
    ' ', '#', '#', ' ',
    '#', '#', '#', '#' 
}; 

int carPos = WIN_WIDTH / 2;
int score = 0; 

void clearScreen() {
    system("cls");
}

void gotoxy(int x, int y) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD CursorPosition;
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void drawBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(0, i); cout << "|";
        gotoxy(WIN_WIDTH, i); cout << "|";
    }
}

void genEnemy(int ind) {
    enemyX[ind] = 17 + rand() % (33);  
}

void drawEnemy(int ind) {
    if (enemyFlag[ind]) {
        gotoxy(enemyX[ind], enemyY[ind]);
        cout << "****";  
        gotoxy(enemyX[ind], enemyY[ind] + 1); cout << " ** "; 
        gotoxy(enemyX[ind], enemyY[ind] + 2); cout << "****"; 
        gotoxy(enemyX[ind], enemyY[ind] + 3); cout << " ** ";  
    } 
}

void eraseEnemy(int ind) {
    if (enemyFlag[ind]) {
        gotoxy(enemyX[ind], enemyY[ind]); cout << "    ";  
        gotoxy(enemyX[ind], enemyY[ind] + 1); cout << "    "; 
        gotoxy(enemyX[ind], enemyY[ind] + 2); cout << "    "; 
        gotoxy(enemyX[ind], enemyY[ind] + 3); cout << "    "; 
    } 
}

void resetEnemy(int ind) {
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void drawCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carPos, i + 22); cout << car[i][j];
        }
    }
}

void eraseCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carPos, i + 22); cout << " ";
        }
    }
}

int collision() {
    for (int i = 0; i < 2; i++) {
        if (enemyFlag[i]) {
            if (enemyY[i] + 4 >= 23) {
                // Check horizontal overlap between car and enemy
                int enemyLeft = enemyX[i];
                int enemyRight = enemyX[i] + 3; // enemy width 4 chars (0-based)
                int carLeft = carPos;
                int carRight = carPos + 3; // car width 4 chars (0-based)
                if (!(carRight < enemyLeft || carLeft > enemyRight)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void gameover() {
    clearScreen();
    cout << endl;
    cout << "\t\t--------------------------" << endl;
    cout << "\t\t-------- Game Over -------" << endl;
    cout << "\t\t--------------------------" << endl << endl;
    cout << "\t\tPress any key to go back to menu.";
    getch();
}

void updateScore() {
    gotoxy(WIN_WIDTH + 7, 5); cout << "Score: " << score << endl;
}

void instructions() {
    clearScreen();
    cout << "Instructions\n";
    cout << "----------------\n";
    cout << "Avoid Cars by moving left or right.\n";
    cout << "Press 'a' to move left\n";
    cout << "Press 'd' to move right\n";
    cout << "Press Esc to return to the menu\n";
    cout << "\nPress any key to go back to menu";
    getch();
}

void play() {
    carPos = WIN_WIDTH / 2 - 1;
    score = 0;
    enemyFlag[0] = true;
    enemyFlag[1] = false;
    enemyY[0] = enemyY[1] = 1;

    // Remove clearScreen call here to avoid flickering
    // clearScreen(); 
    drawBorder(); 
    updateScore();
    genEnemy(0);
    genEnemy(1);
    
    gotoxy(WIN_WIDTH + 7, 2); cout << "Car Game";
    gotoxy(WIN_WIDTH + 6, 4); cout << "----------";
    gotoxy(WIN_WIDTH + 7, 12); cout << "Control ";
    gotoxy(WIN_WIDTH + 7, 13); cout << "-------- ";
    gotoxy(WIN_WIDTH + 2, 14); cout << " A Key - Left";
    gotoxy(WIN_WIDTH + 2, 15); cout << " D Key - Right"; 
    
    gotoxy(18, 5); cout << "Press any key to start";
    getch();
    gotoxy(18, 5); cout << "                      ";
    
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'a' || ch == 'A') {
                if (carPos > 16) {  // Adjusted boundary to 16
                    eraseCar();  // Erase before moving
                    carPos -= 4;
                }
            }
            if (ch == 'd' || ch == 'D') {
                if (carPos < 52) {  // Adjusted boundary to 52
                    eraseCar();  // Erase before moving
                    carPos += 4;
                }
            } 
            if (ch == 27) { // Escape key
                break;
            }
        } 
        
        drawCar(); 
        drawEnemy(0); 
        drawEnemy(1); 
        if (collision() == 1) {
            gameover();
            return;
        } 
        Sleep(50);
        eraseEnemy(0);
        eraseEnemy(1);   
        
        if (enemyY[0] == 10 && enemyFlag[1] == false) {
            enemyFlag[1] = true;
        }
        
        if (enemyFlag[0]) {
            enemyY[0]++;
        }
        
        if (enemyFlag[1]) {
            enemyY[1]++;
        }
         
        if (enemyY[0] > SCREEN_HEIGHT - 4) {
            resetEnemy(0);
            score++;
            updateScore();
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4) {
            resetEnemy(1);
            score++;
            updateScore();
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); 
     
    while (true) {
        clearScreen();
        gotoxy(10, 5); cout << " -------------------------- "; 
        gotoxy(10, 6); cout << " |        Car Game        | "; 
        gotoxy(10, 7); cout << " --------------------------";
        gotoxy(10, 9); cout << "1. Start Game";
        gotoxy(10, 10); cout << "2. Instructions";     
        gotoxy(10, 11); cout << "3. Quit";
        gotoxy(10, 13); cout << "Select option: ";
        char op = _getch();
        
        if (op == '1') play();
        else if (op == '2') instructions();
        else if (op == '3') exit(0);
    }
    
    return 0;
}