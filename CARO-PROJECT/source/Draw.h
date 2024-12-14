#ifndef Draw_h
#define Draw_h
#include "thuvien.h"
using namespace std;
struct _Point
{
	int X, Y, opt; // tọa độ x, y trên màn hình và opt = 1 nếu là x, opt = -1 nếu là o
};
void drawX(int XX, int YY, int co_txt = 0);
void drawO(int XX, int YY, int co_txt = 0);
void drawI(int XX, int YY, int co_txt = 0);
void drawN(int XX, int YY, int co_txt = 0);
void drawW(int XX, int YY, int co_txt = 0);
void drawX_WIN(int XX, int YY);
void drawO_WIN(int XX, int YY);
void drawC(int XX, int YY);
void drawA(int XX, int YY);
void drawR(int XX, int YY);
void drawE(int XX, int YY);
void drawG(int XX, int YY);
void drawM(int XX, int YY);
void drawL(int XX, int YY);
void drawD(int XX, int YY);
void drawP(int XX, int YY);
void drawT(int XX, int YY);
void drawH(int XX, int YY);
void drawB(int XX, int YY);
void drawU(int XX, int YY);

void drawCARO(int XX, int YY);
void drawNEW_GAME(int XX, int YY);
void drawLOAD_GAME(int XX, int YY);
void drawOPTION(int XX, int YY);
void drawABOUT(int XX, int YY);
void drawHELP(int XX, int YY);
void drawEXIT(int XX, int YY);
void drawIN_MATCH(int XX, int YY);
void getConsoleSize(int& width, int& height);
void clearArea(int XX, int YY, int width, int height);
void drawDRAW(int XX, int YY);
void drawBoard(string name1, string name2, int Xscore, int Oscore, string fileName);
void drawBoardMenu(int XX, int YY, int size, int b_color, string str);
void drawBoardAsk(int XX, int YY, int size, int height, int b_color, string str, char *key);
void drawPopUp(int XX, int YY, int h, int w);
void drawStatus(int XX, int YY, int opt);
void drawName_Board(int XX, int YY, string fileName);

#endif
