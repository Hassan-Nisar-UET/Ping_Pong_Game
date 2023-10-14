#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
using namespace std;
char line[1][5] = {{'_', '_', '_', '_', '_'}};
char board[20][25];
int scox = 10;
int scoy = 54;
int locx = 18;
int locy = 8;
int num;
int ballx = 14;
int bally = 10;
int count = 0;
bool gameOver = false;
bool flag = false;
bool flag1 = false;
bool flag2 = false;
bool flag3 = false;
bool flag4 = true;
bool flag5 = false;
bool flag6 = false;
bool flag7 = false;
bool flag8 = false;
bool flag9 = true;
bool f = false;
bool f1 = false;
string currentDirection;
int playerscore = 0;
void gotoxy(short x, short y);
void moveLeft();
void moveRight();
bool isWin(char player);
void makeBoard();
void showBoard();
void showLine();
void storeLine();
void score();
void removeLine();
void gameName();
void generateRandom();
void putRandomNum();
void moveBall();

void upRight()
{
    ballx--;
    bally++;
    currentDirection = "UR";
}
void downRight()
{
    ballx++;
    bally++;
    currentDirection = "DR";
}
void upLeft()
{
    if (ballx >= 0 && bally >= 0)
    {
        ballx--;
        bally--;
        currentDirection = "UL";
    }
}
void downLeft()
{
    ballx++;
    bally--;
    currentDirection = "DL";
}

void gotoxy(short x, short y)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {x, y};
    SetConsoleCursorPosition(hStdout, position);
}

int main()
{
    generateRandom();

    int gameRunning = true;
    // showLine();
    makeBoard();

    //storeLine();

    while (gameRunning)
    { //ascii codee for escape
        system("cls");
        showBoard();
        gameName();
        putRandomNum();

        moveBall();
        if (gameOver == true)
        {
            break;
        }
        score();
        if (GetAsyncKeyState(VK_LEFT))
        { //ascii LEFT arrow
            moveLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        { //ascii right arrow
            moveRight();
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gameRunning = false;
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            // Code Here
        }
        Sleep(200);
    }
    cout << "Game Over" << endl;
    return 0;
}
void moveBall()
{
    playerscore++;
    if (ballx == 19)
    {
        gameOver = true;
    }

    if (board[ballx][bally] == '0' && count == 0 && bally > 1 && ballx > 1)
    {
        // cout<<"start direction from here"<<endl;
        board[ballx][bally] = ' ';
        upLeft();
        board[ballx][bally] = '0';
        cout << bally;
    }

    /**********left slide or wall***********/
    else if ((bally == 1 && currentDirection == "UL") || (ballx != 0 && flag == true)) // upleft
    {
        count++;
        flag = true;

        if (ballx == 2)
        {
            flag = false;
        }
        board[ballx][bally] = ' ';
        upRight();
        board[ballx][bally] = '0';
    }

    else if ((bally == 1 && currentDirection == "DL") || (bally != 24 && flag8 == true))
    {
        flag8 = true;
        //  cout<<"left side wala"<<endl;
        if (bally == 23)
        {
            flag8 = false;
            f1 = false;
        }

        if (flag9)
        {
            if (ballx != 18)
            {
                board[ballx][bally] = ' ';
                downRight();
                board[ballx][bally] = '0';
            }
        }

        /*************precausion for slit hit ***********/
        if ((ballx == 17 && board[18][bally] == '_') || f1 == true)
        {
            f1 = true;
            flag9 = false;
            board[ballx][bally] = ' ';
            upRight();
            board[ballx][bally] = '0';
        }
        else if (ballx == 18)
        {
            gameOver = true;
        }
    }

    /*********************roof*****************/
    else if ((ballx == 1 && currentDirection == "UR") || (bally != 24 && flag1 == true)) //upright
    {
        flag1 = true;
        //    cout<<"roof wala"<<bally<<endl<<ballx<<endl;
        if (bally == 23)
        {
            flag1 = false;
            f = false;
        }
        if (flag4)
        {

            if (ballx != 18)
            {
                board[ballx][bally] = ' ';
                downRight();
                board[ballx][bally] = '0';
            }
        }

        /*************precausion for slit hit ***********/
        if ((ballx == 17 && board[18][bally] == '_') || f == true)
        {
            f = true;
            flag4 = false;

            board[ballx][bally] = ' ';
            upRight();
            board[ballx][bally] = '0';
            cout << ballx << endl
                 << bally << endl;
        }
        else if (ballx == 18)
        {
            gameOver = true;
        }
    }
    else if ((ballx == 1 && currentDirection == "UL") || (flag6 == true && bally != 1)) //down left
    {
        flag6 = true;
        // cout<<"roof "<<endl;
        if (bally == 2)
        {
            flag6 = false;
        }
        board[ballx][bally] = ' ';
        downLeft();
        board[ballx][bally] = '0';
    }

    else if ((bally == 23 && currentDirection == "UR") || (flag5 == true && ballx != 1))
    { //upleft
        flag5 = true;
        // cout<<"up right "<<endl;

        if (ballx == 2)
        {
            flag5 = false;
        }
        board[ballx][bally] = ' ';
        upLeft();
        board[ballx][bally] = '0';
    }
    /************right side**********/
    else if ((bally == 24 && currentDirection == "DR") || (ballx != 20 && flag2))
    { //downright
        flag2 = true;
        // cout<<"side wala down right"<<endl;
        if (ballx == 18 && board[18][bally] == '_')
        {
            flag2 = false;
            board[ballx][bally] = ' ';
            upRight();
            board[ballx][bally] = '0';
        }
        else
        {
            board[ballx][bally] = ' ';
            downLeft();
            board[ballx][bally] = '0';
        }
    }
}

void putRandomNum()
{
    if (board[ballx][bally] == ' ')
    {
        board[ballx][bally] = '0';
        cout << board[ballx][bally];
    }
}

void generateRandom()
{

    srand(time(0));
    num = rand() % 100;
    num = 'O';
}
void gameName()
{

    gotoxy(scoy, scox - 3);

    cout << " PING PONG GAME  " << endl;
}
void makeBoard()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if (i == 0 || i == 19)
            {
                board[i][j] = '_';
            }
            else
            {
                if (j == 0 || j == 24)
                {
                    board[i][j] = '|';
                }
                else
                {
                    board[i][j] = ' ';
                }
            }
        }
    }
}
void storeLine()
{

    for (int j = 0; j < 5; j++)
    {
        board[locx][locy + j] = line[0][j];
    }
}
void removeLine()
{

    for (int j = 0; j < 5; j++)
    {

        board[locx][locy + j] = ' ';
    }
}

void showBoard()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
}
void moveLeft()
{
    if (locy > 1)
    {
        removeLine();
        locy--;
        storeLine();
    }
}
void moveRight()
{
    if (locy < 19)
    {
        removeLine();
        locy++;
        storeLine();
    }
}
void score()
{
    gotoxy(scoy, scox);
    cout << "your score is .." << playerscore << endl;
}
