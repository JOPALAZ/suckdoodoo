
#include <iostream>
#include<chrono>
unsigned char sudoku[9][9] = {
{ 8, 0, 0,       0, 9, 3,        0, 2, 1 },
{ 0, 0, 0,       2, 0, 0,        0, 0, 0 },
{ 0, 5, 0,       0, 0, 0,        0, 6, 0 },

{ 9, 0, 0,       0, 1, 7,        0, 0, 3 },
{ 0, 0, 0,       0, 4, 0,        0, 0, 0 },
{ 0, 0, 8,       0, 0, 0,        9, 0, 0 },

{ 7, 0, 0,       4, 0, 0,        0, 0, 0 },
{ 0, 0, 6,       0, 7, 2,        0, 1, 0 },
{ 0, 0, 0,       8, 0, 0,        0, 0, 2 } };

bool isOkInCol(unsigned char col, unsigned char num) {
    if (num == 0)
        return false;
    for (unsigned char i{}; i < 9; ++i) {
        if (sudoku[i][col] == num)
            return false;
    }
    return true;
}
bool isOkInRow(unsigned char row, unsigned char num) {
    if (num == 0)
        return false;
    for (unsigned char i{}; i < 9; ++i) {
        if (sudoku[row][i] == num)
            return false;
    }
    return true;
}
bool isOkInBox(unsigned char x_, char y_, char num) {
    if (num == 0)
        return false;
    unsigned char startX = x_ / 3 * 3; //я не шизофреник, это операции с целыми числами, например 5/3*3 =1*3=3. 
    unsigned char startY = y_ / 3 * 3; // и получаем что начало квардратика в котором есть точка 5 5 это 3 3, все верно.
    for (unsigned char i{ startX }; i < startX + 3; ++i)
    {
        for (unsigned char j{ startY }; j < startY + 3; ++j)
        {
            if (sudoku[i][j] == num) return false;
        }
    }
    return true;
}
bool isAllOk(unsigned char x_, unsigned char y_, unsigned char num) {
    return isOkInBox(x_, y_, num) && isOkInCol(y_, num) && isOkInRow(x_, num);
}
bool calculateSudoku(unsigned char posx, unsigned char posy)
{
    while (sudoku[posx][posy]!=0)
    {
        posx++;
        if (posx == 9) {
            posy++;
            posx = 0;
        }
        if (posy == 9)
            return true;
    }
    for (unsigned char i{ 1 }; i < 10; ++i) {
        if (isAllOk(posx, posy, i)) {
            sudoku[posx][posy] = i;
            if (calculateSudoku(posx, posy)) {
                return true;
            }
            else {
                sudoku[posx][posy] = 0;
            }
        }
    }
    return false;



}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    calculateSudoku(0, 0);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) std::cout << ' ';
            std::cout << (unsigned short)sudoku[i][j] << ' ';
        }
        if ((i+1) % 3 == 0 && i != 0) std::cout << '\n';
        std::cout << '\n';
    }
    std::cout << "TIME ELAPSED (nanoseconds) "<< duration.count();
}
