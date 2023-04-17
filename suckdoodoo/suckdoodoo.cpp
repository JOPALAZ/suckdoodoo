
#include <iostream>
int sudoku[9][9] = {
{ 5, 3, 0, 0, 7, 0, 0, 0, 0 },
{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },
{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
{ 4, 0, 0, 8, 0, 3, 0, 0, 1 },
{ 7, 0, 0, 0, 2, 0, 0, 0, 6 },
{ 0, 6, 0, 0, 0, 0, 2, 8, 0 },
{ 0, 0, 0, 4, 1, 9, 0, 0, 5 },
{ 0, 0, 0, 0, 8, 0, 0, 7, 9 } };
bool isOkInCol(int col, int num) {
    if (num == 0)
        return false;
    for (int i{}; i < 9; ++i) {
        if (sudoku[i][col] == num)
            return false;
    }
    return true;
}
bool isOkInRow(int row, int num) {
    if (num == 0)
        return false;
    for (int i{}; i < 9; ++i) {
        if (sudoku[row][i] == num)
            return false;
    }
    return true;
}
bool isOkInBox(int x_, int y_, int num) {
    if (num == 0)
        return false;
    int startX = x_ / 3 * 3; //я не шизофреник, это операции с целыми числами, например 5/3*3 =1*3=3. 
    int startY = y_ / 3 * 3; // и получаем что начало квардратика в котором есть точка 5 5 это 3 3, все верно.
    for (int i{ startX }; i < startX + 3; ++i) 
    {
        for (int j{ startY }; j < startY + 3; ++j) 
        {
            if (sudoku[i][j] == num) return false;
        }
    }
    return true;
}
bool isAllOk(int x_, int y_, int num) {
    return isOkInBox(x_, y_, num) && isOkInCol(y_, num) && isOkInRow(x_, num);
}
bool calculateSudoku(int posx, int posy) 
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
    for (int i{ 1 }; i < 10; ++i) {
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
    calculateSudoku(0, 0);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) std::cout << ' ';
            std::cout << sudoku[i][j] << ' ';
        }
        if ((i+1) % 3 == 0 && i != 0) std::cout << '\n';
        std::cout << '\n';
    }
}
