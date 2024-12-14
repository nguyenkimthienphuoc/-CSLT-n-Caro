#include "Control.h"
#include "Draw.h"
#include "thuvien.h"
#include "GameLogic.h"
#include "Feature.h"
#define F first
#define S second

#define moveTo(x, y) gotoXY(status[x][y].X, status[x][y].Y)
const int BOARD_SIZE = 15;
typedef pair<int, int> ii;

int Turn, maxDepth = 3;
_Point status[BOARD_SIZE + 5][BOARD_SIZE + 5];
vector<ii> Cache, winLine;
set<ii> Neighbor;

long long consecutiveScore(int len, int openEnds, bool currentTurn) // return the score of consecutive elements
{
    if (len < 5 && openEnds == 0) return 0;
    switch (len)
    {
    case 4:
        switch (openEnds)
        {
        case 1:
            if (currentTurn)
                return 10000000;
            return 50;
        case 2:
            if (currentTurn)
                return 10000000;
            return 10000000;
        }
        break;
    case 3:
        switch (openEnds)
        {
        case 1:
            if (currentTurn)
                return 7;
            return 5;
        case 2:
            if (currentTurn)
                return 10000;
            return 50;
        }
        break;
    case 2:
        switch (openEnds)
        {
        case 1:
            return 3;
        case 2:
            return 5;
        }
        break;
    case 1:
        switch (openEnds)
        {
        case 1:
            return 1;
        case 2:
            return 2;
        }
        break;
    default:
        switch (openEnds)
        {
        case 2:
            return (long long)1e10;
        case 1:
            return (long long)1e10 - (long long)1e9;
        case 0:
            return (long long)1e10 - (long long)2e9;
        }
        break;
    }
    return -1;
}

long long get_score(int a[], int player)
{
    int Size = BOARD_SIZE + 2;
    long long score = 0;
    for (int i = 1; i < Size - 1; i++) if (abs(a[i]) == 1) // get consecutive equal elements 
    {
        int j = i;
        while (j + 1 < Size - 1 && a[i] == a[j + 1]) j++;

        int len = j - i + 1;
        int openEnds = 2 - (a[i - 1] != 0) - (a[j + 1] != 0); // number of open cells
        score += 1ll * consecutiveScore(len, openEnds, player == a[i]) * a[i];
        i = j;
    }
    return score;
}

bool valid(int x, int y)
{
    return y > 0 && x > 0 && x <= BOARD_SIZE && y <= BOARD_SIZE;
}

long long evaluation(int player) // evaluate a status
{
    long long score = 0;
    int* b = new int[BOARD_SIZE + 2];
    for (int i = 1; i <= BOARD_SIZE; i++) // get a row
    {
        for (int k = 0; k < BOARD_SIZE + 2; k++)
        {
            if (valid(i, k))
                b[k] = status[i][k].opt;
            else
                b[k] = 2;
        }
        score += get_score(b, player);
        if (abs(score) >= 1e8)
        {
            winLine.clear();
            for (int k = 0; k < BOARD_SIZE + 2; k++)
                winLine.push_back({ i, k });
            return score;
        }
    }

    for (int j = 1; j <= BOARD_SIZE; j++) // get a column
    {
        for (int k = 0; k < BOARD_SIZE + 2; k++)
        {
            if (valid(k, j))
                b[k] = status[k][j].opt;
            else
                b[k] = 2;
        }
        score += get_score(b, player);
        if (abs(score) >= 1e8)
        {
            winLine.clear();
            for (int k = 0; k < BOARD_SIZE + 2; k++)
                winLine.push_back({ k, j });
            return score;
        }
    }

    for (int i = 0; i <= BOARD_SIZE; i++) // get a main diagonal
    {
        for (int k = 0; k < BOARD_SIZE + 2; k++)
        {
            if (valid(i + k, k))
                b[k] = status[i + k][k].opt;
            else
                b[k] = 2;
        }
        score += get_score(b, player);
        if (abs(score) >= 1e8)
        {
            winLine.clear();
            for (int k = 0; k < BOARD_SIZE + 2; k++)
                winLine.push_back({ i + k, k });
            return score;
        }
    }
    for (int j = 1; j <= BOARD_SIZE; j++) // get a main diagonal
    {
        for (int k = 0; k < BOARD_SIZE + 2; k++)
        {
            if (valid(k, j + k))
                b[k] = status[k][j + k].opt;
            else
                b[k] = 2;
        }
        score += get_score(b, player);
        if (abs(score) >= 1e8)
        {
            winLine.clear();
            for (int k = 0; k < BOARD_SIZE + 2; k++)
                winLine.push_back({ k, j + k });
            return score;
        }
    }

    for (int i = 1; i <= BOARD_SIZE + 1; i++) // get a secondary diagonal
    {
        for (int k = 0; k < BOARD_SIZE + 2; k++)
        {
            if (valid(i - k, k))
                b[k] = status[i - k][k].opt;
            else
                b[k] = 2;
        }
        score += get_score(b, player);
        if (abs(score) >= 1e8)
        {
            winLine.clear();
            for (int k = 0; k < BOARD_SIZE + 2; k++)
                winLine.push_back({ i - k, k });
            return score;
        }
    }
    for (int j = 1; j <= BOARD_SIZE; j++) // get a secondary diagonal
    {
        for (int k = 0; k < BOARD_SIZE + 2; k++)
        {
            if (valid(BOARD_SIZE + 1 - k, j + k))
                b[k] = status[BOARD_SIZE + 1 - k][j + k].opt;
            else
                b[k] = 2;
        }
        score += get_score(b, player);
        if (abs(score) >= 1e8)
        {
            winLine.clear();
            for (int k = 0; k < BOARD_SIZE + 2; k++)
                winLine.push_back({ BOARD_SIZE + 1 - k, j + k });
            return score;
        }
    }
    return score;
}

long long minimax(int depth, long long alpha, long long beta, int player, int& x, int& y)
{
    long long val = evaluation(player); // get the score of the current state if is the "player"'s turn.
    if (depth == 0 || abs(val) >= 1e8) // deepest depth or one of the two players wins.
        return val; // return the score

    // Max is the X player
    if (player == 1)
    {
        long long maxEval = (long long)-1e11;
        vector<ii> a(Neighbor.begin(), Neighbor.end());
        for (const ii& tmp : a)
        {
            int i = tmp.F, j = tmp.S;
            if (status[i][j].opt == 0)
            {
                status[i][j].opt = 1; // try to put X into cell i, j
                long long eval = minimax(depth - 1, alpha, beta, -1, x, y); // minimax recursion
                status[i][j].opt = 0;
                if (maxEval < eval)
                {
                    maxEval = eval;
                    if (depth == maxDepth) x = i, y = j;
                }
                if (alpha < eval) alpha = eval;
                if (beta <= alpha) // alpha-beta pruning
                    break;
            }
        }
        return maxEval;
    }
    else // Min is the O player (bot)
    {
        long long minEval = (long long)1e11;
        vector<ii> a(Neighbor.begin(), Neighbor.end());
        for (const ii& tmp : a)
        {
            int i = tmp.F, j = tmp.S;
            if (status[i][j].opt == 0)
            {
                status[i][j].opt = -1;
                long long eval = minimax(depth - 1, alpha, beta, 1, x, y);
                status[i][j].opt = 0;
                if (minEval > eval)
                {
                    minEval = eval;
                    if (depth == maxDepth) x = i, y = j;
                }
                if (beta > eval) beta = eval;
                if (beta <= alpha)
                    break;
            }
        }
        return minEval;
    }
}
void botMove(int& x, int& y)
{
    ShowCur(0);
    if (Cache.size() == 1) // bot's first move is random
    {
        int dx[] = { -1, 1, 0, 0, -1, 1, 1, -1 };
        int dy[] = { 0, 0, -1, 1, 1, -1, 1, -1 };
        int r = rand() % 8;
        while (!valid(x + dx[r], y + dy[r])) r = rand() % 4;
        x += dx[r];
        y += dy[r];
    }
    else minimax(maxDepth = (Neighbor.size() <= 110 ? 3 : 2), (long long)-1e11, (long long)1e11, -1, x, y);
    if (status[x][y].opt != 0) // if the algorithm is incorrect then go for a random move
    {
        int dx[] = { -1, 1, 0, 0, -1, 1, 1, -1 };
        int dy[] = { 0, 0, -1, 1, 1, -1, 1, -1 };
        int r = rand() % 8;
        while (!valid(x + dx[r], y + dy[r]) && status[x][y].opt != 0) r = rand() % 4;
        x += dx[r];
        y += dy[r];
    }
    ShowCur(1);
}

void addNeighbor(int x, int y) // add some adjective cells for calculations
{
    if (Neighbor.count({ x, y })) Neighbor.erase({ x, y });
    int radius = 3;

    int Upx = x - radius, Upy = y - radius, Lowx = x + radius, Lowy = y + radius;
    for (int i = Upx; i <= Lowx; i++)
        for (int j = Upy; j <= Lowy; j++)
        {
            if (valid(i, j) && status[i][j].opt == 0)
                Neighbor.insert({ i, j });
        }
}

void makeMove(int Turn, int x, int y) // make a move
{
    status[x][y].opt = Turn;

    moveTo(x, y);

    if (Turn == 1)
    {
        setColor(15, 4);
        cout << 'X';
    }
    else if (Turn == -1)
    {
        setColor(15, 1);
        cout << 'O';
    }
    else
    {
        setColor(15, 15);
        cout << " ";
    }
    moveTo(x, y);
}

void updateNeighbor()
{
    Neighbor.clear();
    for (int i = 1; i <= BOARD_SIZE; i++)
        for (int j = 1; j <= BOARD_SIZE; j++)
            if (status[i][j].opt != 0) addNeighbor(i, j);
}

void displayWinLine() // Bold the winning line
{
#define getVal(i) status[winLine[i].F][winLine[i].S].opt

    for (int i = 0; i < winLine.size(); i++)
    {
        if (abs(getVal(i)) == 1)
        {
            int j = i;
            while (j + 1 < (int)winLine.size() - 1 && getVal(i) == getVal(j + 1)) j++;
            int len = j - i + 1;
            if (len >= 5)
            {
                for (int T = 0; T < 3; T++) // 3 times
                {
                    for (int k = i; k <= j; k++)
                    {
                        int XX = status[winLine[k].F][winLine[k].S].X;
                        int YY = status[winLine[k].F][winLine[k].S].Y;
                        gotoXY(XX - 1, YY);
                        setColor(getVal(k) == 1 ? 4 : 1, 15);
                        cout << " " << (getVal(k) == 1 ? 'X' : 'O') << " ";
                    }
                    Sleep(500);
                    for (int k = i; k <= j; k++)
                    {
                        int XX = status[winLine[k].F][winLine[k].S].X;
                        int YY = status[winLine[k].F][winLine[k].S].Y;
                        gotoXY(XX - 1, YY);
                        setColor(15, getVal(k) == 1 ? 4 : 1);
                        cout << " " << (getVal(k) == 1 ? 'X' : 'O') << " ";
                    }
                    Sleep(300);
                }
                return;
            }
        }
    }
}

void startGame(bool vsBot, bool isNewGame, int XX, int YY, string name1, string name2, vector<ii> Data, string fileName, int Xscore, int Oscore)
{
playAgain:
    srand(static_cast<unsigned int>(time(0))); //ép kiểu cho time để tránh bị mất data
    system("cls");

    int x, y;
    Cache.clear();
    ShowCur(1);
    drawBoard(name1, name2, Xscore, Oscore, fileName);
    
    if (isNewGame) // if it is a new game then reset everything
    {
        Turn = 1;
        x = 8, y = 8;
        moveTo(x, y);
    }
    else { // if not, use the previous data for the game
        Turn = 1;
        for (ii tmp : Data) {
            makeMove(Turn, tmp.F, tmp.S);
            Turn *= -1;
        }

        Cache = Data;
        if (Data.empty()) x = y = 8;
        else {
            x = Data.back().F;
            y = Data.back().S;
        }
    }

    while (abs(evaluation(1)) < 1e8) // while the game is not over then keep playing
    {   
        drawStatus(XX + 34, YY + 1, 1);
        updateNeighbor();
        if (Turn == 1) {
            drawX(XX + 47 + 4 * BOARD_SIZE, YY + 7, 4);
            drawO(XX - 34 + 4 * BOARD_SIZE, YY + 7, 8);
        }
        else {
            drawO(XX - 34 + 4 * BOARD_SIZE, YY + 7, 1);
            drawX(XX + 47 + 4 * BOARD_SIZE, YY + 7, 8);
        } 
        moveTo(x, y);

        if (Turn == -1 && vsBot) botMove(x, y);
        else
        {
            while (true)
            {
                int Key = nextMove(Turn);
                if (Key == 0 && status[x][y].opt == 0) break;
                if (Key == 1 && x > 1) x -= 1;
                if (Key == 2 && y > 1) y -= 1;
                if (Key == 3 && x < BOARD_SIZE) x += 1;
                if (Key == 4 && y < BOARD_SIZE) y += 1;
                if (Key == 5) { // exit game
                    char* key = new char;
                    drawStatus(XX + 34, YY + 1, 4);
                    drawBoardAsk(XX + 42, YY - 2, 57, 3, 15, " Do you want to exit? Press Y/N (Remember to save game)", key);

                    while (true) {

                        if (*key == 'N' || *key == 'n') {
                            drawStatus(XX + 34, YY + 1, 1);
                            ShowCur(1);                        // Hiển thị lại con trỏ
                            moveTo(x, y);
                            break;
                        }

                        else if (*key == 'Y' || *key == 'y') return; // Kết thúc trò chơi
                    }
                    delete key;
                }
                if (Key == 6) // Undo
                {
                    for (int i = 0; i < (vsBot ? 2 : 1); i++) if (!Cache.empty())
                    {
                        x = Cache.back().F;
                        y = Cache.back().S;
                        Cache.pop_back();
                        makeMove(0, x, y);
                        Turn *= -1;
                        if (Turn == 1) {
                            drawX(XX + 47 + 4 * BOARD_SIZE, YY + 7, 4);
                            drawO(XX - 34 + 4 * BOARD_SIZE, YY + 7, 8);
                        }
                        else {
                            drawO(XX - 34 + 4 * BOARD_SIZE, YY + 7, 1);
                            drawX(XX + 47 + 4 * BOARD_SIZE, YY + 7, 8);
                        }
                        moveTo(x, y);
                    }
                }
                if (Key == 7) { //Save game
                    char* key = new char;
                    drawBoardAsk(XX + 42, YY - 2, 57, 3, 15, "           Do you want to SAVE GAME? Press Y/N", key);
                    while (true) {

                        if (*key == 'N' || *key == 'n') {
                            drawStatus(XX + 34, YY + 1, 1);
                            ShowCur(1);                        // Hiển thị lại con trỏ
                            moveTo(x, y);
                            break;
                        }

                        else if (*key == 'Y' || *key == 'y') {
                            drawStatus(XX + 34, YY + 1, 1);
                            saveGame(XX + 35, YY + 35, Cache, Xscore, Oscore, name1, name2, fileName, vsBot); // Kết thúc trò chơi
                            break;
                        }
                    }
                    delete key;
                }
                moveTo(x, y);
            }
        }
        Cache.push_back({ x, y });
        makeMove(Turn, x, y);
        Turn *= -1;

        if (Cache.size() == BOARD_SIZE * BOARD_SIZE) {
            Turn = 0;
            break;
        }
    }

    ShowCur(0);
    displayWinLine();

    
    
    if (Turn == -1) {
        Xscore++;
        drawStatus(XX + 34, YY + 1, 4);
        clearArea((XX - 34 + 4 * BOARD_SIZE) - 6, YY + 4, 20, 29);
        drawX_WIN(XX - 34 + 4 * BOARD_SIZE, YY + 7);        // X Wins
        gotoXY(XX + 52, YY + 1);
        setColor(15, 4); cout << "<< Press Y to continue or N to exit >>";
        setColor(15, 0);
    }                                           
    else if (Turn == 1) {
        Oscore++;
        drawStatus(XX + 34, YY + 1, 4);
        clearArea((XX + 47 + 4 * BOARD_SIZE) - 6, YY + 4, 20, 29);
        drawO_WIN(XX + 47 + 4 * BOARD_SIZE, YY + 7);    // O Wins
        gotoXY(XX + 52, YY + 1);
        setColor(15, 1); cout << "<< Press Y to continue or N to exit >>";
        setColor(15, 0);
    }
    else {
        drawStatus(XX + 34, YY + 1, 4);
        clearArea((XX - 34 + 4 * BOARD_SIZE) - 6, YY + 4, 20, 29);
        clearArea((XX + 47 + 4 * BOARD_SIZE) - 6, YY + 4, 20, 29);            // Draw
        drawDRAW(XX - 34 + 4 * BOARD_SIZE, YY + 7);
        drawDRAW(XX + 47 + 4 * BOARD_SIZE, YY + 7);
        gotoXY(XX + 52, YY + 1);
        setColor(15, 0); cout << "<< Press Y to continue or N to exit >>";

    }


    // Check player want to play again
    while (true) {
        char key = _getch();
        if (key == 'N' || key == 'n') break;
        else if (key == 'Y' || key == 'y') {
            isNewGame = 1;
            goto playAgain;
        }
    }
}
