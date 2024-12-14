#include "Feature.h"
#include "Control.h"
#include "Draw.h"
#include "GameLogic.h"
vector<string> fileNames;
const int BOARD_SIZE = 15;
#define co_theme 15,0
#define _CRT_SECURE_NO_WARNINGS
bool putname(int XX, int YY, string& str) {
	int sz = 0, Xi = XX, Yi = YY;	// [Xi, Yi] is located of pointer in head line
	string tmp = str;				// tmp is a origin name

	setColor(15, 8);
	gotoXY(Xi, Yi);
	cout << str;

	while (true) {
		char ch = _getch();
		if ((int)ch < 0) {			// If input is arrow, we must getchar one more
			ch = _getch();
			continue;
		}

		if (ch == 13) break;		// If input is "enter" then exit with putname = 1

		if (ch == 27) return 0;		// If input is "esc" then back to menu with putname = 2

		if (ch == '\b' && sz) {		// If input is "backspace" then delete last char
			str.pop_back(); --sz;
			--XX; gotoXY(XX, YY); cout << " ";
			gotoXY(XX, YY);

			if (sz == 0) {
				str = tmp;
				setColor(15, 8);
				gotoXY(Xi, Yi);
				cout << str;
			}

		}
		else if ((('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || isdigit(ch)) && sz < 10) {  // Length of name is less than or equal 10
			if (sz == 0) {
				str = "";
				setColor(15, 0);
				gotoXY(Xi, Yi);
				cout << "          ";
			}

			str.push_back(ch); ++sz;
			gotoXY(XX, YY);
			cout << ch; ++XX;
		}
	} return 1;
}

void newGame(int XX, int YY) {
	struct _aboutMenuNewgame {
		int X1 = 0, Y1 = 0, size1 = 0, b_color1 = 0;
		string str1 = "";

		_aboutMenuNewgame() = default;

		_aboutMenuNewgame(int x, int y, int s, int b, string st)
			: X1(x), Y1(y), size1(s), b_color1(b), str1(st) {}

		void draw() {
			drawBoardMenu(X1, Y1, size1, b_color1, str1);
		}
	};

	_aboutMenuNewgame s1[2], s2[2];  // s1: unselect  ;  s2: select
	s1[0] = { XX, YY + 1, 21, 15, "     1 PLAYER      " };
	s1[1] = { XX, YY + 4, 21, 15, "     2 PLAYERS     " };

	s2[0] = { XX, YY + 1, 21, 14, ">>   1 PLAYER    <<" };
	s2[1] = { XX, YY + 4, 21, 14, ">>   2 PLAYERS   <<" };

	system("cls");
	int S = 0;  // pointer in menu

	while (true) {
		/*------------------ DECOR ---------------------------*/
		for (int i = 0; i < 2; ++i)
			s1[i].draw();
		s2[S].draw();
		/*----------------------------------------------------*/

		/*------------- Menu Newgame selection ---------------*/
		int _in1 = nextMoveMenu();
		if (_in1 == 1 || _in1 == 3) S ^= 1;       // Move
		else if (_in1 == 0) {					  // Enter
			if (S == 0) mode_vsBot(XX - 2, YY);		  // Mode: 1 player
			else if (S == 1) mode_PvP(XX - 3, YY);  // Mode: 2 player
			else assert(false);
			break;
		}
		else if (_in1 == 5)					  // Exit
			break;
		/*----------------------------------------------------*/
	}
}

void mode_vsBot(int XX, int YY) {
	/*------------------ DECOR ---------------------------*/
	system("cls");

	/*----------------------------------------------------*/

	/*----------------- Import Name  ---------------------*/
	string name;
	drawBoardMenu(XX, YY, 27, 15, " NAME PLAYER:   ");
	if (!putname(XX + 15, YY + 1, name = "[player]")) return;       // Name of player
	startGame(true, true, -1, 3, name, "BOT", {}, "", 0, 0);
	/*----------------------------------------------------*/
}

void mode_PvP(int XX, int YY) {
	/*------------------ DECOR ---------------------------*/

	system("cls");

	/*----------------------------------------------------*/

	/*----------------- Import Name  ---------------------*/
	string name1, name2;
	drawBoardMenu(XX, YY, 29, 15, " NAME PLAYER 1: ");
	if (!putname(XX + 17, YY + 1, name1 = "[player1]")) return;   // Name of player 1

	drawBoardMenu(XX, YY + 3, 29, 15, " NAME PLAYER 2: ");
	if (!putname(XX + 17, YY + 4, name2 = "[player2]")) return;   // Name of player 2

	startGame(false, true, -1, 3, name1, name2, {}, "", 0, 0);
	/*----------------------------------------------------*/
}

void loadGame(int XX, int YY) {
	
	struct _aboutMenuLoadgame {
		int X2 = 0, Y2 = 0, size2 = 0, b_color2 = 0;
		string str2 = "";

		_aboutMenuLoadgame() = default;

		_aboutMenuLoadgame(int x, int y, int s, int b, string st)
			: X2(x), Y2(y), size2(s), b_color2(b), str2(st) {}

		void draw() {
			drawBoardMenu(X2, Y2, size2, b_color2, str2);
		}
	};

	/*------------------ DECOR ---------------------------*/
	pullList();
	int sz = min((int)fileNames.size() - 1, 14);
	_aboutMenuLoadgame s1[15], s2[15];
	for (int i = 0; i < 15; ++i) {
		s1[i] = { XX - 30 + 30 * (i / 5), YY + (i % 5) * 3, 20, 12, "      EMPTY       " };
		s2[i] = { XX - 30 + 30 * (i / 5), YY + (i % 5) * 3, 20, 14, "" };

		if (i <= sz) {
			string tmp = fileNames[i];
			int siz = 14 - (int)tmp.size();

			for (int j = 1; 2 * j <= siz; ++j)
				tmp = ' ' + tmp + ' ';
			if (siz & 1) tmp += ' ';

			s1[i].str2 = "  " + tmp + "  ";
			s2[i].str2 = ">>" + tmp + "<<";
			s1[i].b_color2 = 15;
		}
	}

	system("cls");

drawLOAD_GAME(XX - 26, YY - 12);
//	drawPopUp(XX - 33, YY - 1, 20, 86);
	/*----------------------------------------------------*/

	int S = min(0, sz);		// Pointer
	while (true) {
		for (int i = 0; i < 15; ++i)
			s1[i].draw();
		if (S != -1) s2[S].draw();

		setColor(co_theme);
		gotoXY(XX - 29, YY + 15); cout << "                                                                               ";
		gotoXY(XX - 29, YY + 16); cout << "                                                                               ";
		gotoXY(XX - 29, YY + 17); cout << "                                                                               ";
		gotoXY(XX - 3, YY + 19); setColor(14, 0);
		cout << " << Press ESC to exit >> ";
		setColor(co_theme);

		int _in = nextMoveMenu();
		if (_in == 5) break;			// Esc
		else if (S == -1) continue;		// No files were saved

		if (_in == 0) {
			_aboutMenuLoadgame s3[3], s4[3];	// s3: unselect, s4: select
			s3[0] = { XX - 12, YY + 15, 16, 15, "     PLAY     " };
			s3[1] = { XX + 8, YY + 15, 16, 15,  "    DELETE    " };
			s3[2] = { XX + 28, YY + 15, 16, 15, "    RENAME    " };

			s4[0] = { XX - 12, YY + 15, 16, 14, ">>   PLAY   <<" };
			s4[1] = { XX + 8, YY + 15, 16, 14,  ">>  DELETE  <<" };
			s4[2] = { XX + 28, YY + 15, 16, 14, ">>  RENAME  <<" };

			// Display: choose the operation
			s1[S].draw();
			gotoXY(XX - 30, YY + 16); setColor(co_theme);
			cout << "                                                                                 ";
			gotoXY(XX - 24, YY + 16); setColor(11, 0); cout << " Choose: ";

			int Sj = 0;
			while (true) {
				// Display: choose the operation
				gotoXY(XX - 30, YY + 16); setColor(co_theme);
				cout << "                                                                                 ";
				gotoXY(XX - 24, YY + 16); setColor(11, 0); cout << " Choose: ";

				for (int j = 0; j < 3; ++j)
					s3[j].draw();
				s4[Sj].draw();

				int _in = nextMoveMenu();
				if (_in == 5) break;					// Esc
				else if (_in == 2) Sj = (Sj + 2) % 3;	// Left
				else if (_in == 4) Sj = (Sj + 1) % 3;	// Right
				else if (_in == 0) {					// Enter
					if (Sj == 0) {		// Load file and play
						vector<ii> Cache;
						int Xscore, Oscore;
						string name1, name2;
						bool vsBot;

						loadFromFile(fileNames[S], Cache, Xscore, Oscore, name1, name2, vsBot);
						startGame(vsBot, 0, -1, 3, name1, name2, Cache, fileNames[S], Xscore, Oscore);
						return;
					}

					if (Sj == 1) {		// Delete file
						deleteFile(fileNames[S]);
						for (int t = S + 1; t <= sz; ++t) {
							fileNames[t - 1] = fileNames[t];
							s1[t - 1].str2 = s1[t].str2;
							s2[t - 1].str2 = s2[t].str2;
						}

						fileNames.pop_back();
						s1[sz].str2 = "      EMPTY       ";
						s1[sz].b_color2 = 12;
						s2[sz].str2 = "";
						--sz;  S = min(S, sz);

					}
					else {			// Rename file
						setColor(co_theme);
						gotoXY(XX - 29, YY + 15); cout << "                                                                               ";
						gotoXY(XX - 29, YY + 16); cout << "                                                                               ";
						gotoXY(XX - 29, YY + 17); cout << "                                                                               ";

						// Import new name
					renameFile:
						string tmp;
						gotoXY(XX - 24, YY + 16); cout << " New Name:                                                         ";
						if (!putname(XX - 13, YY + 16, tmp = fileNames[S])) continue;

						// Check the same name
						bool checkSame = 0;
						for (int t = 0; t <= sz; ++t)
							if (t != S && fileNames[t] == tmp)
								checkSame = 1;

						if (checkSame) {
							gotoXY(XX - 24, YY + 16); cout << ">> It already exists, do you want to change another name? Press Y/N";
							while (true) {
								char key = _getch();
								if (key == 'N' || key == 'n') break;
								else if (key == 'Y' || key == 'y') goto renameFile;
							} break;
						}

						// Process rename
						string old_name = fileNames[S] + ".txt";
						string new_name = tmp + ".txt";
						(void)rename(old_name.c_str(), new_name.c_str());

						fileNames[S] = tmp;
						int siz = 14 - (int)tmp.size();

						for (int t = 1; 2 * t <= siz; ++t)
							tmp = ' ' + tmp + ' ';
						if (siz & 1) tmp += ' ';

						s1[S].str2 = "  " + tmp + "  ";
						s2[S].str2 = ">>" + tmp + "<<";
					}
					pushList();
					break;
				}
			} if (S != -1) s2[S].draw();

		}
		else {
			int col = S / 5, nxt_S = -1;
			if (_in == 1) nxt_S = (S + 4) % 5 + col * 5;		// Up
			else if (_in == 2) nxt_S = (S + 10) % 15;			// Left
			else if (_in == 3) nxt_S = (S + 1) % 5 + col * 5;	// Down
			else if (_in == 4) nxt_S = (S + 5) % 15;			// Right
			if (nxt_S >= 0 && nxt_S <= sz) S = nxt_S;		// The pointer mustn't be out of stock
		}
	}
}

void saveGame(int XX, int YY, vector<ii> Cache, int Xscore, int Oscore, string name1, string name2, string& nameFile, bool vsBot)
{
	if (nameFile == "") {
	insertName:
		drawStatus(XX - 13, YY, 2);
		if (!putname(XX - 1, YY, nameFile)) {
			drawStatus(XX - 13, YY, 1);
			return;
		} else if (nameFile == "") goto insertName;
	}

	bool checkSame = 0;
	for (string tmp : fileNames)
		if (tmp == nameFile) checkSame = 1;

	if (checkSame) {
		drawStatus(XX - 13, YY, 3);
		while (true) {
			char key = _getch();
			if (key == 'N' || key == 'n') {
				drawStatus(XX - 13, YY, 4);
				goto insertName;
			}
			else if (key == 'Y' || key == 'y') {
				drawStatus(XX - 13, YY, 4);
				goto push;
			}
		}
	}

	else {
		while ((int)fileNames.size() >= 15)
			fileNames.erase(fileNames.begin());
		fileNames.push_back(nameFile);
	}

push:
	drawName_Board(XX - 16, YY, nameFile);
	pushList();

	// Save game to PC

	nameFile += ".txt";
	FILE* file = fopen(nameFile.c_str(), "w");
	if (file == nullptr) return;

	fprintf(file, "%d %d %d\n", vsBot, Xscore, Oscore);
	fprintf(file, "%s %s\n", name1.c_str(), name2.c_str());
	for (const auto& tmp : Cache) {
		fprintf(file, "%d %d\n", tmp.first, tmp.second);
	}fclose(file);
	ShowCur(1);
}

void loadFromFile(string nameFile, vector<ii>& Cache, int& Xscore, int& Oscore, string& name1, string& name2, bool& vsBot) {	// Load data from file is saved
	Cache.clear();
	nameFile += ".txt";
	FILE* file = fopen(nameFile.c_str(), "r");
	if (file == nullptr) return;

	int vsBotInt;
	char name1Buffer[256], name2Buffer[256];

	if (fscanf(file, "%d %d %d", &vsBotInt, &Xscore, &Oscore) != 3) {
		fclose(file);
		return;
	}
	vsBot = static_cast<bool>(vsBotInt); //chuyển int thành bool rồi gán cho vsBot

	if (fscanf(file, "%255s %255s", name1Buffer, name2Buffer) != 2) {
		fclose(file);
		return;
	}
	name1 = name1Buffer;
	name2 = name2Buffer;

	int x, y;
	while (fscanf(file, "%d %d", &x, &y) == 2) {
		Cache.emplace_back(x, y);
	}

	fclose(file);
}

void pullList() { // Update list of file names from "source/ListFiles.txt"
	fileNames.clear();

	FILE* file = fopen("source/ListFiles.txt", "r");
	char buffer[256]; // Bộ đệm tạm để lưu từng dòng hoặc từng tên file
	while (fscanf(file, "%255s", buffer) == 1) {
		fileNames.emplace_back(buffer);
	}
	fclose(file);
}

void pushList() {		// Update list file is saved in fileNames to PC
	FILE* file = fopen("source/ListFiles.txt", "w");
	for (const string& s : fileNames) {
		fprintf(file, "%s\n", s.c_str()); 
	}
	fclose(file);
}

void deleteFile(string nameFile) {	// Delete File
	nameFile += ".txt";
	remove(nameFile.c_str());
}

void option(int Xi, int Yi) {
	system("cls");

	struct _option {
		int X = 0, Y = 0, size = 0, b_color = 0;
		string str = "";

		_option() = default;

		_option(int x, int y, int s, int b, string st)
			: X(x), Y(y), size(s), b_color(b), str(st) {
		}

		void draw() {
			drawBoardMenu(X, Y, size, b_color, str);
		}
	};

	drawOPTION(Xi - 15, Yi - 15);

	int XX = Xi - 27, YY = Yi - 5; //vẽ khung
	int h = 20, w = 76;
	drawPopUp(XX, YY, h, w);

	setColor(co_theme);
	gotoXY(XX + 7, YY + 6);
	cout << "Background Music";

	gotoXY(XX + 7, YY + 12);
	cout << "Sound Effect";

	setColor(14, 0);
	gotoXY(XX + 26, YY + 21); cout << "<< Press ESC to exit >>";
	setColor(co_theme);

	_option s1[4], s2[4];  // s1: unselect  ;  s2: select
	s1[0] = { XX + 25, YY + 5, 11, 15, "   ON   " };
	s1[1] = { XX + 45, YY + 5, 11, 15, "   OFF   " };
	s1[2] = { XX + 25, YY + 11, 11, 15, "   ON   " };
	s1[3] = { XX + 45, YY + 11, 11, 15, "   OFF   " };

	s2[0] = { XX + 25, YY + 5, 11, 12, "   ON   " };
	s2[1] = { XX + 45, YY + 5, 11, 12, "   OFF   " };
	s2[2] = { XX + 25, YY + 11, 11, 12, "   ON   " };
	s2[3] = { XX + 45, YY + 11, 11, 12, "   OFF   " };

	int S = 0;

	while (true) {
		for (int i = 0; i < 4; ++i)
			s1[i].draw();
		s2[S].draw();

		ShowCur(0);
		int _in = nextMoveMenu();

		if (_in == 1) { // Up
			if (S >= 2) S -= 2; // Nếu đang ở hàng dưới, lên hàng trên
		}
		else if (_in == 3) { // Down
			if (S <= 1) S += 2; // Nếu đang ở hàng trên, xuống hàng dưới
		}
		else if (_in == 2) { // Left
			if (S % 2 == 1) S -= 1; // Nếu đang ở cột phải, sang cột trái
		}
		else if (_in == 4) { // Right
			if (S % 2 == 0) S += 1; // Nếu đang ở cột trái, sang cột phải
		}
		else if (_in == 0) { // Enter
			if (S == 0) {
				clearArea(XX + 25, YY + 16, 30, 1);
				setColor(co_theme);
				gotoXY(XX + 25, YY + 16);
				cout << "Background Music is enabled.";

			}
			if (S == 1) {
				clearArea(XX + 25, YY + 16, 30, 1);
				setColor(co_theme);
				gotoXY(XX + 25, YY + 16);
				cout << "Background Music is disabled.";

			}
			if (S == 2) {
				clearArea(XX + 25, YY + 16, 30, 1);
				setColor(co_theme);
					gotoXY(XX + 25, YY + 16);
					std::cout << "Sound Effect is enabled.";


			}
			if (S == 3) {
				clearArea(XX + 25, YY + 16, 30, 1);
				setColor(co_theme);
				gotoXY(XX + 25, YY + 16);
				cout << "Sound Effect is disabled.";

			}
		}
		else if (_in == 5) break;
	}

}

void help(int Xi, int Yi) 
{
	system("cls");
	drawHELP(Xi - 5, Yi - 15);

	int XX = Xi - 27, YY = Yi - 1;
	int h = 20, w = 76;

	setColor(co_theme);
	for (int i = - 5; i < h - 3; ++i) {
		gotoXY(XX + 37, YY + i);
		cout << "|";
	}

	setColor(12, 15);
	gotoXY(XX - 5, YY - 5);
	cout << "KEYBOARD GUIDE";

	gotoXY(XX + 63, YY - 5);
	cout << "RULES";

	setColor(11, 0);
	gotoXY(XX - 15, YY - 2);
	cout << "2 players:                           ";

	setColor(11, 0);
	gotoXY(XX - 15, YY + 7);
	cout << "1 player:                            ";
	
	//hướng dẫn chơi 
	setColor(co_theme);
	
	gotoXY(XX - 1, YY); 
	cout << "Player 1    Player 2";
	gotoXY(XX - 9, YY + 1);
	cout << "Go up:     W           " << char(30);
	gotoXY(XX - 9, YY + 2);
	cout << "Go left:   A           " << char(17);
	gotoXY(XX - 9, YY + 3);
	cout << "Go down:   S           "<< char(31);
	gotoXY(XX - 9, YY + 4);
	cout << "Go right:  D           " << char(16);

	gotoXY(XX - 1, YY + 9);
	cout << "Player 1";
	gotoXY(XX - 9, YY + 11);
	cout << "Go up:     " << char(30);
	gotoXY(XX - 9, YY + 12);
	cout << "Go left:   " << char(17);
	gotoXY(XX - 9, YY + 13);
	cout << "Go down:   " << char(31);
	gotoXY(XX - 9, YY + 14);
	cout << "Go right:  " << char(16);
	gotoXY(XX - 15, YY + 16);
	cout << " Please turn off any Vietnamese typing ";
	gotoXY(XX - 15, YY + 17);
	cout << "software for the best gaming experience.";

	gotoXY(XX + 48, YY - 2);
	cout << "  1. Two players take turns.";
	gotoXY(XX + 48, YY);
	cout << "  2. The goal is to create a straight line ";
	gotoXY(XX + 48, YY + 1);
	cout << "of five marks (X or O) in any direction: ";
	gotoXY(XX + 48, YY + 2);
	cout << "horizontal, vertical, or diagonal.";
	gotoXY(XX + 48, YY + 4);
	cout << "  3. Players alternate turns placing their";
	gotoXY(XX + 48, YY + 5);
	cout << "mark (X or O) on an empty spot.";
	gotoXY(XX + 48, YY + 7);
	cout << "  4. The first player to form an unbroken";
	gotoXY(XX + 48, YY + 8);
	cout << "line of five marks wins.";
	gotoXY(XX + 48, YY + 10);
	cout << "  5. If the board is full and no player has ";
	gotoXY(XX + 48, YY + 11);
	cout << "formed a line of five, the game ends in a";
	gotoXY(XX + 48, YY + 12);
	cout << "draw.";

	setColor(14, 0);
	gotoXY(XX + 27, YY + 19); cout << "<< Press ESC to exit >>";
	setColor(co_theme);

	while (nextMoveMenu() != 5);
}

void about(int Xi, int Yi) {
	system("cls");
	drawABOUT(Xi - 10, Yi - 15);

	int XX = Xi - 27, YY = Yi - 1;
	int h = 25, w = 90;

	drawPopUp(XX - 9, YY - 6, h, w);
	setColor(12, 0);
	gotoXY(XX + 24, YY -  4);  cout << "HCMUS - 24C09 - Group 4";
	setColor(11, 0);
	gotoXY(XX + 21, YY + 16); cout << "Advisor: Dr.Truong Toan Thinh";

	setColor(14, 0);
	gotoXY(XX + 24, YY + 21); cout << "<< Press ESC to exit >>";
	setColor(co_theme);

	setColor(co_theme); 
	gotoXY(XX + 5, YY);  cout << "Vu Viet Huy";
	gotoXY(XX + 7, YY + 1); cout << "24127406";

	setColor(co_theme);
	gotoXY(XX + 30, YY);  cout << "Nguyen Le Sang";
	gotoXY(XX + 33, YY + 1); cout << "24127231";

	setColor(co_theme); 
	gotoXY(XX + 55, YY);  cout << "Chau Phung My"; 
	gotoXY(XX + 56, YY + 1); cout << "24127453"; 
	
	setColor(co_theme); 
	gotoXY(XX + 13, YY + 7);  cout << "Nguyen Kim Thien Phuoc"; 
	gotoXY(XX + 20, YY + 8); cout << "24127510"; 
	
	setColor(co_theme); 
	gotoXY(XX + 45, YY + 7);  cout << "Pham Minh Thu"; 
	gotoXY(XX + 47, YY + 8); cout << "24127550"; 
	
	while (nextMoveMenu() != 5);
}
