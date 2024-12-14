#include "GameLogic.h"
#include "Draw.h"
#include "thuvien.h"
#include "Control.h"
#include "Feature.h"

void exit(int XX, int YY) {
    system("cls");
    char* key = new char;
    drawBoardAsk(XX - 20, YY - 2, 57, 3, 15, "               Do you want to exit game? ", key);

    while (true) {

        if (*key == 'N' || *key == 'n') {
            ShowCur(1);                        // Hiển thị lại con trỏ
            break;
        }

        else if (*key == 'Y' || *key == 'y') exit(0);
    }
    delete key;
} //hiện tại chưa có thông bảo hỏi trước khi thoát

void drawMenu(int XX, int YY) {
    struct _aboutMenu {
        int X = 0, Y = 0, size = 0, b_color = 0;
        string str = "";

        _aboutMenu() = default;

        _aboutMenu(int x, int y, int s, int b, string st)
            : X(x), Y(y), size(s), b_color(b), str(st) {}

    void draw(){
            drawBoardMenu(X, Y, size, b_color, str);
        }
    };

    _aboutMenu s1[6], s2[6];  // s1: unselect  ;  s2: select
    s1[0] = { XX, YY, 20, 15, "     NEW GAME     " }; 
    s1[1] = { XX, YY + 3, 20, 15, "     LOAD GAME    " }; 
    s1[2] = { XX, YY + 6, 20, 15, "      OPTION      " };
    s1[3] = { XX, YY + 9, 20, 15, "       HELP       " }; 
    s1[4] = { XX, YY + 12, 20, 15, "       ABOUT      " }; 
    s1[5] = { XX, YY + 15, 20, 15, "     EXIT GAME    " }; 
    
    s2[0] = { XX, YY, 20, 14, ">>   NEW GAME   <<" }; 
    s2[1] = { XX, YY + 3, 20, 14, ">>   LOAD GAME  <<" }; 
    s2[2] = { XX, YY + 6, 20, 14, ">>    OPTION    <<" }; 
    s2[3] = { XX, YY + 9, 20, 14, ">>     HELP     <<" }; 
    s2[4] = { XX, YY + 12, 20, 14, ">>     ABOUT    <<" }; 
    s2[5] = { XX, YY + 15, 20, 14, ">>   EXIT GAME  <<" }; 
    
    int S = 0;   // pointer in menu 

    while (true) {
        drawCARO(XX - 6, YY - 9);
        for (int i = 0; i < 6; ++i)
            s1[i].draw();
        s2[S].draw();

        ShowCur(0);
        int _in = nextMoveMenu();
        if (_in == 1) S = (S - 1 + 6) % 6;        // Up
        else if (_in == 3) S = (S + 1) % 6;   // Down
        else if (_in == 5) exit(XX, YY);
        else if (_in == 0) {				  // Enter
            if (S == 0) newGame(XX, YY);
            else if (S == 1) loadGame(XX, YY);
            else if (S == 2) option(XX, YY);
            else if (S == 3) help(XX, YY);
            else if (S == 4) about(XX, YY); 
            else if (S == 5) exit(XX, YY);

            else assert(false);
            system("cls");
        }
    }
}


int32_t main(){
    fixConsoleWindow(141, 46);
    SetConsoleTitle(L"Game CARO");
    ShowCur(0);
    drawMenu(59, 20);
    return 0;
}
