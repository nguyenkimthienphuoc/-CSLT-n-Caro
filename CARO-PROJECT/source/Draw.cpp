#include "Draw.h"
#include "GameLogic.h"
#include "thuvien.h"
#include "Control.h"
#define co_theme 15,0
const int BOARD_SIZE = 15;
#define moveTo(x, y) gotoXY(status[x][y].X, status[x][y].Y)
extern _Point status[BOARD_SIZE + 5][BOARD_SIZE + 5];

void drawBoardMenu(int XX, int YY, int size, int b_color, string str = "") { // 3 * size, Menu Board
    setColor(co_theme);

    gotoXY(XX, YY); cout << char(201);
    for (int i = 0; i < size - 2; ++i) cout << char(205);
    cout << char(187);

    gotoXY(XX, YY + 1); cout << char(186);
    gotoXY(XX + size - 1, YY + 1); cout << char(186);

    gotoXY(XX, YY + 2); cout << char(200);
    for (int i = 0; i < size - 2; ++i) cout << char(205);
    cout << char(188);

    gotoXY(XX + 1, YY + 1);
    setColor(b_color, 0);  cout << str;
    setColor(co_theme);
}

void drawBoardAsk(int XX, int YY, int size, int height, int b_color, string str = "", char *key = nullptr){     //hàm in thông tin hỏi trước người dùng trước khi làm gì đó
    char localKey;  // Biến cục bộ dùng nếu `key` không được truyền
    if (!key) key = &localKey;
    if (height % 2 == 0) height++; //height là số lẻ để căn giữa văn bản
    ShowCur(0);
    setColor(co_theme);
    clearArea(XX, YY, size, height + 2);
    // Vẽ khung trên
    gotoXY(XX, YY); cout << char(201);
    for (int i = 0; i < size - 2; ++i) cout << char(205);
    cout << char(187);

    // Vẽ khung dọc với chiều cao tùy chỉnh
    for (int i = 1; i <= height; ++i) {
        gotoXY(XX, YY + i); cout << char(186);            // Cột trái
        gotoXY(XX + size - 1, YY + i); cout << char(186); // Cột phải
    }

    // Vẽ khung dưới
    gotoXY(XX, YY + height + 1); cout << char(200);
    for (int i = 0; i < size - 2; ++i) cout << char(205);
    cout << char(188);

    // In nội dung ở giữa bảng
    gotoXY(XX + 1, YY + (height / 2));  // Canh giữa bảng
    setColor(b_color, 0); cout << str << endl;      //str là văn bản cần ghi
    gotoXY(XX + (size / 2) - 10, YY + (height / 2) + 1); cout << endl;
    gotoXY(XX + (size / 2) - 10, YY + (height / 2) + 2);
    setColor(b_color, 0); cout << "Y - YES        N - NO";
    setColor(co_theme);

    while (true) {
        *key = _getch();
        if (*key == 'N' || *key == 'n' || *key == 'Y' || *key == 'y' || *key == '27') {
            clearArea(XX, YY, size, height + 2);
            break;
        }
    }
}


void drawC(int XX, int YY) { // 6 * 8
    gotoXY(XX + 1, YY);
    setColor(0, 0); cout << "      ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(0, 0);  cout << "  ";
    setColor(co_theme);
    cout << char(201);
    for (int i = 1; i <= 4; ++i) cout << char(205);
    cout << char(188);

    gotoXY(XX, YY + 2);
    setColor(0, 0);  cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 3);
    setColor(0, 0);  cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 4);
    cout << char(200);
    setColor(0, 0);  cout << "      ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX + 1, YY + 5);
    cout << char(200);
    for (int i = 1; i <= 5; ++i) cout << char(205);
    cout << char(188);
}
void drawA(int XX, int YY) { // 6 * 8
    gotoXY(XX + 1, YY);
    setColor(0, 0); cout << "     ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201) << char(205) << char(205);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 2);
    setColor(0, 0); cout << "       ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 3);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201) << char(205) << char(205);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 4);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186) << "  ";
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 5);
    cout << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188);
}
void drawR(int XX, int YY) { // 6 * 8
    gotoXY(XX, YY);
    setColor(0, 0); cout << "      ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201) << char(205) << char(205);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 2);
    setColor(0, 0); cout << "      ";
    setColor(co_theme); cout << char(201) << char(188);

    gotoXY(XX, YY + 3);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201) << char(205) << char(205);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 4);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186) << "  ";
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 5);
    cout << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188);
}
void drawE(int XX, int YY) {  // 6 * 8
    gotoXY(XX, YY);
    setColor(0, 0); cout << "       ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201);
    for (int i = 0; i < 4; ++i) cout << char(205);
    cout << char(188);

    gotoXY(XX, YY + 2);
    setColor(0, 0); cout << "     ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 3);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201) << char(205) << char(205) << char(188);

    gotoXY(XX, YY + 4);
    setColor(0, 0); cout << "       ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 5);
    cout << char(200);
    for (int i = 0; i < 6; ++i) cout << char(205);
    cout << char(188);
}
void drawG(int XX, int YY) {  // 6 * 9
    gotoXY(XX + 1, YY);
    setColor(0, 0); cout << "      ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201);
    for (int i = 0; i < 4; ++i) cout << char(205);
    cout << char(188);

    gotoXY(XX, YY + 2);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186) << "  ";
    setColor(0, 0); cout << "   ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 3);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186) << "   ";
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 4);
    cout << char(200);
    setColor(0, 0); cout << "      ";
    setColor(co_theme); cout << char(201) << char(188);

    gotoXY(XX + 1, YY + 5);
    cout << char(200);
    for (int i = 0; i < 5; ++i) cout << char(205);
    cout << char(188);
}
void drawM(int XX, int YY) {  // 6 * 11
    gotoXY(XX, YY);
    setColor(0, 0); cout << "   ";
    setColor(co_theme); cout << char(187) << "   ";
    setColor(0, 0); cout << "   ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(0, 0); cout << "    ";
    setColor(co_theme); cout << char(187) << " ";
    setColor(0, 0); cout << "    ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 2);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201);
    setColor(0, 0); cout << "    ";
    setColor(co_theme); cout << char(201);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 3);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186) << char(200);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201) << char(188);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 4);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186) << " " << char(200) << char(205) << char(188) << " ";
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 5);
    cout << char(200) << char(205) << char(188) << "     " << char(200) << char(205) << char(188);
}
void drawL(int XX, int YY) {  // 6 * 8
    gotoXY(XX, YY);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(187);

    for (int i = 1; i <= 3; ++i) {
        gotoXY(XX, YY + i);
        setColor(0, 0); cout << "  ";
        setColor(co_theme); cout << char(186);
    }

    gotoXY(XX, YY + 4);
    setColor(0, 0); cout << "       ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 5);
    cout << char(200);
    for (int i = 0; i < 6; ++i) cout << char(205);
    cout << char(188);
}
void drawD(int XX, int YY) {  // 6 * 8
    gotoXY(XX, YY);
    setColor(0, 0); cout << "      ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201) << char(205) << char(205);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(187);

    for (int i = 2; i <= 3; ++i) {
        gotoXY(XX, YY + i);
        setColor(0, 0); cout << "  ";
        setColor(co_theme); cout << char(186) << "  ";
        setColor(0, 0); cout << "  ";
        setColor(co_theme); cout << char(186);
    }

    gotoXY(XX, YY + 4);
    setColor(0, 0); cout << "      ";
    setColor(co_theme); cout << char(201) << char(188);

    gotoXY(XX, YY + 5);
    cout << char(200);
    for (int i = 0; i < 5; ++i) cout << char(205);
    cout << char(188);
}
void drawP(int XX, int YY) {  // 6 * 8
    gotoXY(XX, YY);
    setColor(0, 0); cout << "      ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201) << char(205) << char(205);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 2);
    setColor(0, 0); cout << "      ";
    setColor(co_theme); cout << char(201) << char(188);

    gotoXY(XX, YY + 3);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201) << char(205) << char(205) << char(205) << char(188);

    gotoXY(XX, YY + 4);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 5);
    cout << char(200) << char(205) << char(188);
}
void drawT(int XX, int YY) { // 6 * 9
    gotoXY(XX, YY);
    setColor(0, 0);  cout << "        ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 1);
    cout << char(200) << char(205) << char(205);
    setColor(0, 0); cout << "  ";
    setColor(co_theme);  cout << char(201) << char(205) << char(205) << char(188);

    for (int i = 0; i < 3; ++i) {
        gotoXY(XX + 3, YY + 2 + i);
        setColor(0, 0); cout << "  ";
        setColor(co_theme); cout << char(186);
    }

    gotoXY(XX + 3, YY + 5);
    cout << char(200) << char(205) << char(188);
}
void drawH(int XX, int YY) {  // 6 * 8
    gotoXY(XX, YY);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(187) << "  ";
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186) << "  ";
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 2);
    setColor(0, 0); cout << "       ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 3);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201) << char(205) << char(205);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 4);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186) << "  ";
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 5);
    cout << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188);
}

void drawB(int XX, int YY) { // 6 * 8
    gotoXY(XX, YY);
    setColor(0, 0); for (int i = 0; i < 6; ++i) cout << " ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201) << char(205) << char(205);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 2);
    setColor(0, 0); for (int i = 0; i < 6; ++i) cout << " ";
    setColor(co_theme); cout << char(201) << char(188);

    gotoXY(XX, YY + 3);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(201) << char(205) << char(205);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 4);
    setColor(0, 0); for (int i = 0; i < 6; ++i) cout << " ";
    setColor(co_theme); cout << char(201) << char(188);

    gotoXY(XX, YY + 5);
    cout << char(200);
    for (int i = 0; i < 5; ++i) cout << char(205);
    cout << char(188);
}

void drawU(int XX, int YY) { // 6 * 9
    gotoXY(XX, YY);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(187) << "   ";
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186) << "   ";
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 2);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186) << "   ";
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 3);
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186) << "   ";
    setColor(0, 0); cout << "  ";
    setColor(co_theme); cout << char(186);

    gotoXY(XX, YY + 4);
    cout << char(200);
    setColor(0, 0); cout << "      ";
    setColor(co_theme); cout << char(201) << char(188);

    gotoXY(XX + 1, YY + 5);
    cout << char(200);
    for (int i = 1; i <= 5; ++i) cout << char(205);
    cout << char(188);
}

void drawABOUT(int XX, int YY) {
    drawA(XX, YY);
    drawB(XX + 8, YY);
    drawO(XX + 16, YY);
    drawU(XX + 25, YY);
    drawT(XX + 34, YY);
}

void drawCARO(int XX, int YY) {
    drawC(XX, YY);
    drawA(XX + 8, YY);
    drawR(XX + 16, YY);
    drawO(XX + 24, YY);
}

void drawNEW_GAME(int XX, int YY) {
    drawN(XX, YY);
    drawE(XX + 10, YY);
    drawW(XX + 18, YY);
    drawG(XX + 32, YY);
    drawA(XX + 41, YY);
    drawM(XX + 49, YY);
    drawE(XX + 60, YY);
}

void drawLOAD_GAME(int XX, int YY) {
    drawL(XX, YY);
    drawO(XX + 8, YY);
    drawA(XX + 17, YY);
    drawD(XX + 25, YY);
    drawG(XX + 37, YY);
    drawA(XX + 46, YY);
    drawM(XX + 54, YY);
    drawE(XX + 65, YY);
}

void drawOPTION(int XX, int YY) {
    drawO(XX, YY);
    drawP(XX + 10, YY);
    drawT(XX + 18, YY);
    drawI(XX + 28, YY);
    drawO(XX + 32, YY);
    drawN(XX + 42, YY);
}

void drawHELP(int XX, int YY) {
    drawH(XX, YY);
    drawE(XX + 8, YY);
    drawL(XX + 16, YY);
    drawP(XX + 24, YY);
}

void drawEXIT(int XX, int YY) {
    drawE(XX, YY);
    drawX(XX + 8, YY);
    drawI(XX + 16, YY);
    drawT(XX + 24, YY);
}

void drawIN_MATCH(int XX, int YY) {
    drawI(XX, YY);
    drawN(XX + 3, YY);
    drawM(XX + 17, YY);
    drawA(XX + 28, YY);
    drawT(XX + 36, YY);
    drawC(XX + 45, YY);
    drawH(XX + 53, YY);
}

void drawX(int XX, int YY, int co_txt) {  // 6 * 8
    gotoXY(XX, YY);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(187) << "  ";
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(187);

    gotoXY(XX, YY + 1);
    cout << char(200);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(187);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(201) << char(188);

    gotoXY(XX, YY + 2);
    cout << " " << char(200);
    setColor(co_txt, 0); cout << "   ";
    setColor(15, co_txt); cout << char(201) << char(188);

    gotoXY(XX, YY + 3);
    cout << " ";
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(201);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(187);

    gotoXY(XX, YY + 4);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(201) << char(188) << " ";
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(187);

    gotoXY(XX, YY + 5);
    cout << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188);
    setColor(co_theme);
}


void drawO(int XX, int YY, int co_txt) { // 6 * 9
    gotoXY(XX + 1, YY);
    setColor(co_txt, 0); cout << "      ";
    setColor(15, co_txt); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(201) << char(205) << char(205) << char(205);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(187);

    gotoXY(XX, YY + 2);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186) << "   ";
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 3);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186) << "   ";
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 4);
    cout << char(200);
    setColor(co_txt, 0); cout << "      ";
    setColor(15, co_txt); cout << char(201) << char(188);

    gotoXY(XX + 1, YY + 5);
    cout << char(200);
    for (int i = 1; i <= 5; ++i) cout << char(205);
    cout << char(188);
    setColor(co_theme);
}
void getConsoleSize(int& width, int& height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void drawI(int XX, int YY, int co_txt) {  // 6 * 3
    gotoXY(XX, YY);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 2);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 3);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 4);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 5);
    cout << char(200) << char(205) << char(188);
}

void drawN(int XX, int YY, int co_txt) {  // 6 * 10
    gotoXY(XX, YY);
    setColor(co_txt, 0); cout << "   ";
    setColor(15, co_txt); cout << char(187) << "   ";
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(co_txt, 0); cout << "    ";
    setColor(15, co_txt); cout << char(187) << "  ";
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 2);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(201);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(187) << " ";
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 3);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186) << char(200);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(187);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 4);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186) << " " << char(200);
    setColor(co_txt, 0); cout << "    ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 5);
    cout << char(200) << char(205) << char(188) << "  " << char(200);
    for (int i = 0; i < 3; ++i) cout << char(205);
    cout << char(188);
}
void drawW(int XX, int YY, int co_txt) {  // 6 * 10
    gotoXY(XX, YY);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(187) << "    ";
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(187);

    gotoXY(XX, YY + 1);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186) << "    ";
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 2);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186) << " ";
    setColor(co_txt, 0); cout << " ";
    setColor(15, co_txt); cout << char(187) << " ";
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 3);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);
    setColor(co_txt, 0); cout << "   ";
    setColor(15, co_txt); cout << char(187);
    setColor(co_txt, 0); cout << "  ";
    setColor(15, co_txt); cout << char(186);

    gotoXY(XX, YY + 4);
    setColor(15, co_txt); cout << char(200);
    setColor(co_txt, 0); cout << "   ";
    setColor(15, co_txt); cout << char(201);
    setColor(co_txt, 0); cout << "   ";
    setColor(15, co_txt); cout << char(201) << char(188);

    gotoXY(XX + 1, YY + 5);
    cout << char(200) << char(205) << char(205) << char(188) << char(200) << char(205) << char(205) << char(188);
}

void drawX_WIN(int XX, int YY) {
    drawX(XX, YY, 4);
    drawW(XX - 1, YY + 7, 4);
    drawI(XX + 2, YY + 13, 4);
    drawN(XX - 1, YY + 19, 4);
}
void drawO_WIN(int XX, int YY) {
    drawO(XX - 1, YY, 1);
    drawW(XX - 1, YY + 7, 1);
    drawI(XX + 2, YY + 13, 1);
    drawN(XX - 1, YY + 19, 1);
}

void drawDRAW(int XX, int YY) {
    drawD(XX, YY);
    drawR(XX, YY + 6);
    drawA(XX, YY + 12);
    drawW(XX - 1, YY + 18);
}

void drawBoard(string name1, string name2, int Xscore, int Oscore, string fileName) {
    int consoleWidth, consoleHeight;
    getConsoleSize(consoleWidth, consoleHeight);

    int BOARD_WIDTH = 4 * BOARD_SIZE; // Bề ngang của bảng cờ
    int BOARD_HEIGHT = 2 * BOARD_SIZE; // Chiều cao của bảng cờ

    int Xi = (consoleWidth - BOARD_WIDTH) / 2 + 31;
    int Yi = (consoleHeight - BOARD_HEIGHT) / 2 + 2;

    int XX = Xi - 31, YY = Yi - 2;

    setColor(co_theme);

    for (int y = 0; y <= 2 * BOARD_SIZE; ++y) {
        for (int x = 0; x <= 4 * BOARD_SIZE; ++x) {
            gotoXY(XX + x, YY + y);

            if (x == 0 && y == 0) cout << char(201);
            else if (x == 0 && y == 2 * BOARD_SIZE) cout << char(200);
            else if (x == 4 * BOARD_SIZE && y == 0) {
                cout << char(203);
                for (int i = 0; i < 20; ++i) cout << char(205);
                cout << char(187);
            }
            else if (x == 4 * BOARD_SIZE && y == 2 * BOARD_SIZE) {
                cout << char(202);
                for (int i = 0; i < 20; ++i) cout << char(205);
                cout << char(188);
            }
            else if (x % 4 == 0 && y == 0) cout << char(209);
            else if (x % 4 == 0 && y == 2 * BOARD_SIZE) cout << char(207);
            else if (x == 0 && y % 2 == 0) cout << char(199);
            else if (x == 4 * BOARD_SIZE && y % 2 == 0) cout << char(182);
            else if (x % 4 == 0 && y % 2 == 0) cout << char(197);
            else if (x % 4 == 0) {
                if (x == 0 || x == 4 * BOARD_SIZE) cout << char(186);
                else cout << char(179);
            }
            else if (y % 2 == 0) {
                if (y == 0 || y == 2 * BOARD_SIZE) cout << char(205);
                else cout << char(196);
            }
            else cout << " ";
        }

        if (y != 0 && y != 2 * BOARD_SIZE)
            cout << "                    " << char(186);

        if (y != 0 && y != 2 * BOARD_SIZE) {
            gotoXY(XX - 21, YY + y);  // Di chuyển vị trí để vẽ cột bên trái
            cout << char(186);
        }
        gotoXY(XX - 21, YY);  // Góc trên bên trái
        cout << char(201);

        for (int i = 60; i < 20 + 4 * BOARD_SIZE; ++i) cout << char(205);  // Đường ngang trên
        cout << char(203);  // Nối góc trên với bàn cờ
        gotoXY(XX - 21, YY + 2 * BOARD_SIZE);  // Góc dưới bên trái
        cout << char(200);
        for (int i = 60; i < 20 + 4 * BOARD_SIZE; ++i) cout << char(205);  // Đường ngang dưới
        cout << char(202);

    }

    

    /*--------------------------- Update status --------------------------------*/
    for (int y = 1; y <= BOARD_SIZE; ++y)
        for (int x = 1; x <= BOARD_SIZE; ++x) {
            status[y][x].Y = YY + (y - 1) * 2 + 1;
            status[y][x].X = XX + (x - 1) * 4 + 2;
            status[y][x].opt = 0;
        }

    /*---------------------- Information in Board ------------------------------*/
    setColor(11, 0);
    gotoXY(XX + 4 * BOARD_SIZE + 10 - ((int)name1.size() + 1) / 2, YY + 2); cout << " " << name1 << " ";
    gotoXY(XX - 11 - ((int)name2.size() + 1) / 2, YY + 2); cout << " " << name2 << " ";

    gotoXY(XX + 4 * BOARD_SIZE + 7, YY + 12);
    cout << "Score: " << Xscore;
    gotoXY(XX - 1 * BOARD_SIZE + 1, YY + 12);
    cout << "Score: " << Oscore;
}

void clearArea(int XX, int YY, int width, int height) {
    for (int i = 0; i < height; ++i) {
        gotoXY(XX, YY + i);
        for (int j = 0; j < width; ++j) {
            cout << " "; // Ghi đè bằng khoảng trắng
        }
    }
}

void drawPopUp(int XX, int YY, int h, int w) {			// Pop Up Board
    setColor(co_theme);

    gotoXY(XX + 2, YY);
    cout << char(201);
    for (int i = 0; i < w - 6; ++i) cout << char(205);
    cout << char(187);

    gotoXY(XX + 1, YY + 1); cout << char(201) << char(188);
    for (int i = 2; i < w - 4; ++i) cout << " ";
    cout << char(200) << char(187);

    gotoXY(XX, YY + 2); cout << char(201) << char(188);
    for (int i = 3; i < w - 1; ++i) cout << " ";
    cout << char(200) << char(187);

    for (int i = 0; i < h - 6; ++i) {
        gotoXY(XX, YY + 3 + i); cout << char(186);
        for (int j = 1; j < w - 1; ++j) cout << " ";
        cout << char(186);
    }

    gotoXY(XX, YY + h - 3); cout << char(200) << char(187);
    for (int i = 3; i < w - 1; ++i) cout << " ";
    cout << char(201) << char(188);

    gotoXY(XX + 1, YY + h - 2); cout << char(200) << char(187);
    for (int i = 2; i < w - 4; ++i) cout << " ";
    cout << char(201) << char(188);

    gotoXY(XX + 2, YY + h - 1);
    cout << char(200);
    for (int i = 0; i < w - 6; ++i) cout << char(205);
    cout << char(188);
}

void drawStatus(int XX, int YY, int opt) { 
    gotoXY(XX - 3, YY);
    setColor(11, 0);
    switch (opt) {
    case 1:
        cout << ">> Playing";
        setColor(15, 0);
        cout << "        | 'L'- Save  | 'U'- Undo  | 'Esc'- Exit  |  ";
        ShowCur(1);
        break;
    case 2:
        cout << ">> File's name:";
        setColor(15, 0);
        cout << "          ";
        ShowCur(1);
        break;
    case 3:
        cout << ">> It already exists, do you want to replace it? Press Y/N";
        ShowCur(0);
        break;
    default:
        setColor(15, 0);
        cout << "                                                                ";
        break;
    }
    setColor(15, 0);
}

void drawName_Board(int XX, int YY, string fileName) {	// Hiển thị tên của ván chơi
    gotoXY(XX, YY);
    setColor(0, 15);  cout << ">> BOARD NAME: ";
    if ((int)fileName.size() == 0) fileName = "[NULL]";
    while ((int)fileName.size() <= 10) fileName.push_back(' ');
    cout << fileName;
    cout << "<<";
    setColor(15, 0);
}