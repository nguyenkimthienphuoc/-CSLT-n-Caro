#ifndef GameLogic_h
#define GameLogic_h
#include "thuvien.h"
using namespace std;
void fixConsoleWindow(int columns, int rows);
void getCharSize(int& charWidth, int& charHeight);
void gotoXY(int x, int y);
void setColor(int background_color, int text_color);
void draw_square(int i, int j, int x, int y, int color);
void ShowCur(bool CursorVisibility);
void curr_coordinate(int& x, int& y);
int nextMove(int& Turn);
int nextMoveMenu();
void decorate_draw(int x, int y, const string& nameFile);

#endif 