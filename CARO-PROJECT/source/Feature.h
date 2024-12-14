#ifndef Feature_h
#define Feature_h
#include "thuvien.h"
#include "Control.h"
#include "Draw.h"
#include "GameLogic.h"
using namespace std;

#define F first
#define S second
typedef pair<int, int> ii;
bool putname(int XX, int YY, string& str);
void newGame(int XX, int YY);
void mode_vsBot(int XX, int YY);
void mode_PvP(int XX, int YY);
void loadGame(int XX, int YY);
void saveGame(int XX, int YY, vector<ii> Cache, int Xscore, int Oscore, string name1, string name2, string& nameFile, bool vsBot);
void loadFromFile(string nameFile, vector<ii>& Cache, int& Xscore, int& Oscore, string& name1, string& name2, bool& vsBot);
void pullList();
void pushList();
void deleteFile(string nameFile);
void option(int Xi, int Yi);
void help(int Xi, int Yi);
void about(int Xi, int Yi);

#endif // !Feature_h

