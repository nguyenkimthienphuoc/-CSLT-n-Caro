#include "GameLogic.h"
#include "Control.h"
#include "thuvien.h"

// Hàm tính kích thước ký tự hiện tại trong console
void getCharSize(int& charWidth, int& charHeight) {
	CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
	charWidth = cfi.dwFontSize.X;  // Chiều rộng ký tự
	charHeight = cfi.dwFontSize.Y; // Chiều cao ký tự
}

// Hàm điều chỉnh console theo kích thước người dùng mong muốn
void fixConsoleWindow(int columns, int rows) {
	system("COLOR f0");
	HWND consoleWindow = GetConsoleWindow();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Loại bỏ nút phóng to và viền dày
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style &= ~(WS_MAXIMIZEBOX | WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);

	// Tính kích thước ký tự
	int charWidth, charHeight;
	getCharSize(charWidth, charHeight);

	// Tính kích thước cửa sổ dựa trên số cột và dòng
	int windowWidth = columns * charWidth;
	int windowHeight = rows * charHeight;

	// Lấy kích thước màn hình làm việc
	RECT screenRect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &screenRect, 0);

	// Đảm bảo kích thước không vượt quá màn hình
	windowWidth = min(windowWidth, screenRect.right - screenRect.left);
	windowHeight = min(windowHeight, screenRect.bottom - screenRect.top);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	// Đặt kích thước bộ đệm trước khi điều chỉnh cửa sổ
	COORD bufferSize;
	bufferSize.X = static_cast<SHORT>(screenRect.right - screenRect.left);
	bufferSize.Y = static_cast<SHORT>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1); // Keep the height as it is
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	// Đặt kích thước cửa sổ
	SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(columns - 1), static_cast<SHORT>(rows - 1) };
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

	// Điều chỉnh kích thước vật lý của cửa sổ console
	SetWindowPos(consoleWindow, NULL, screenRect.left, screenRect.top,
		windowWidth, windowHeight, SWP_NOZORDER | SWP_NOACTIVATE);
}

void gotoXY(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int BG_color, int Text_color)
{
	HANDLE Mau = GetStdHandle(STD_OUTPUT_HANDLE);
	int color_code = BG_color * 16 + Text_color;
	SetConsoleTextAttribute(Mau, color_code);
}

void draw_square(int i, int j, int x, int y, int color) {
	x = (x - 1) * 2 + 1;
	gotoXY(x + i, y + j);
	setColor(color, color);
	cout << "  ";
	setColor(15, 15);
}

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void curr_coordinate(int& x, int& y)
{
	CONSOLE_SCREEN_BUFFER_INFO curr;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curr);
	x = curr.dwCursorPosition.X;
	y = curr.dwCursorPosition.Y;
}
int nextMove(int& Turn) {   // Get operation from keyboard
	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (Turn == 1) {
				if (c == 13) return 0;	// Enter
				if (c == 27) return 5;				// Exit

				if (c == -32) {						// Arrow
					c = _getch();

					if (c == 72) return 1;			// Up
					if (c == 75) return 2;			// Left
					if (c == 80) return 3;			// Down
					if (c == 77) return 4;			// Right
				}

				if (c == 'U' || c == 'u') return 6;	// Undo
				if (c == 'L' || c == 'l') return 7;	// Save
			}
			if (Turn == -1) {
				if (c == ' ') return 0;				// Space
				if (c == 27) return 5;				// Exit

				if (c == 'W' || c == 'w') return 1;	// Up
				if (c == 'A' || c == 'a') return 2;	// Left
				if (c == 'S' || c == 's') return 3;	// Down
				if (c == 'D' || c == 'd') return 4;	// Right

				if (c == 'U' || c == 'u') return 6;	// Undo
				if (c == 'L' || c == 'l') return 7;	// Save
			}
			
		}
	}
}
int nextMoveMenu() {   // Get operation from keyboard
	while (true) {
		if (_kbhit()) {
			char c = _getch();

			if (c == 13 || c == ' ') return 0;	// Enter
			if (c == 27) return 5;				// Exit

			if (c == -32) {						// Arrow
				c = _getch();

				if (c == 72) return 1;			// Up
				if (c == 75) return 2;			// Left
				if (c == 80) return 3;			// Down
				if (c == 77) return 4;			// Right
			}

			if (c == 'W' || c == 'w') return 1;	// Up
			if (c == 'A' || c == 'a') return 2;	// Left
			if (c == 'S' || c == 's') return 3;	// Down
			if (c == 'D' || c == 'd') return 4;	// Right
			if (c == 'U' || c == 'u') return 6;	// Undo
			if (c == 'L' || c == 'l') return 7;	// Save
		}
	}
}
void decorate_draw(int x, int y, const string& nameFile) {
	ifstream file(nameFile.c_str());
	string s;
	int i = 0;
	while (getline(file, s))
	{
		i++;
		stringstream ss(s);
		int j = 0;
		while (!ss.eof())
		{
			j++;
			int color;
			ss >> color;
			draw_square(x, y, j, i, color);
		}
	}
}