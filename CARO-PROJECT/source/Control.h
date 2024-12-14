#ifndef Control_h
#define Control_h

#include "thuvien.h"
#include "Draw.h"
#include "GameLogic.h"
using namespace std;
long long consecutiveScore(int len, int openEnds, bool currentTurn);
long long get_score(int a[], int player);
bool valid(int x, int y); // tọa độ có hợp lệ hay không
long long evaluation(int player); // trả về điểm trạng thái
long long minimax(int depth, long long alpha, long long beta, int player, int& x, int& y); // thuật minimax
void botMove(int& x, int& y); // nước đi của bot
void startGame(bool vsBot, bool isNewGame, int XX, int YY, string name1, string name2, vector<pair<int, int>> Data, string fileName, int Xscore, int Oscore);

#endif // !Control_h



