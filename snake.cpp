#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
using namespace std;

// ��������������� �����������/����������� ������� Windows
// https://habr.com/ru/articles/545330/

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoXY(int x, int y); // ����������� ������� � �������� �����
void mainMenu(); // ������� ���� ����
void setColor(int text, int background); // ������� �����
void loadLevel(int n); // �������� ���������� ������ � ������
void editor(); // �������� �������
void game(bool career); // ����� ����
void addApple(); // ���������� ������
void line(int n, char s); // ������ ����� ������������ ����� � �������
void showLevelNumber(int n); // ����� �������� ������
void addDiz(int k); // ��������� ��������� ����� ��������������
void addLife(); // ��������� ����� �� ������� ����
void addSuperSpeed(int k); // ��������� ������������� �� ������� ����

enum directions { UP, RIGHT, DOWN, LEFT }; // ������������ �����������
enum color {
	BLACK, DARKBLUE, DARKGREEN, DARKCYAN, DARKRED, DARKPURPLE, DARKYELLOW,
	LOWWHITE, GREY, BLUE, GREEN, CYAN, RED, PURPLE, YELLOW, WHITE
}; // ������������ ������
const int widthField = 80; // ������ �������� ����
const int heightfield = 40; // ������ �������� ����
int field[heightfield][widthField]; // ������� ����
int const startLengthSnake = 3; // ��������� ����� ����
int const startSpeed = 120; // ��������� �������� ��������
bool debug = 0; // ���������� �����
COORD* snake; // ���������� ����
COORD apple; // ���������� ������
COORD* diz; // ���������� ���������������
COORD* superSpeed; // ���������� ��������������
COORD life; // ���������� �����

int main()
{
	// font size 14 !!! for windows 11
	MoveWindow(GetConsoleWindow(), 0, 0, 2000, 2000, 0);

	system("title Snake"); // ��������� ����
	system("mode con cols=100 lines=50"); // ��������� ������� ����
	CONSOLE_CURSOR_INFO x; // ������� ��������� �������
	x.bVisible = false;
	x.dwSize = 100;
	SetConsoleCursorInfo(h, &x);

	while (true) // ����� �������� ����
	{
		mainMenu();
	}
}

void gotoXY(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(h, c);
}

void setColor(int text, int background)
{
	int ConsoleColor = text + background * 16;
	SetConsoleTextAttribute(h, ConsoleColor);
}

void mainMenu()
{

	char keyMenu = 0; // ������� ������� � ����
	short menuPos = 1; // ������� � ����
	short menuMaxElem = 3; // ���������� ��������� � ���� 
	while (true)
	{
		gotoXY(0, 0);
		setColor(DARKGREEN, BLACK);
		cout << "\n\n\n";
		cout << "                   ********                                ***                          \n"
			"                 ***********                               ***                         \n"
			"                ***       *                                **     **       ****        \n"
			"                **           **   **           *****       **   ****      *****        \n"
			"                 *****      *** *****        ***  **       **  ***       **  **       \n"
			"                   *******  ** *** ***      **    **     *** ***        ******         \n"
			"                        *** ****    **   ****    ***   ********        *****    ***    \n"
			"                        *** ***     *********  ********** *** ***    *** **  ****      \n"
			"               ***********  **       ****  *****    **    **   *******   ******        \n"
			"                ********                     **            *      ***    *****         \n";
		setlocale(0, "");
		setColor(WHITE, BLACK);
		gotoXY(40, 22);
		cout << "   ����� ����     ";
		gotoXY(40, 24);
		cout << "�������� �������  ";
		gotoXY(40, 26);
		cout << "     �����        ";
		setColor(DARKGREEN, BLACK);
	
		switch (menuPos) // ����������� ������ ���� � ����������� �� �������
		{
		case 1:
			gotoXY(40, 22);
			setColor(GREEN, BLACK);
			cout << "   ����� ����   ";
			break;
		case 2:
			gotoXY(40, 24);
			setColor(GREEN, BLACK);
			cout << "�������� �������";
			break;
		case 3:
			gotoXY(40, 26);
			setColor(GREEN, BLACK);
			cout << "     �����      ";
			break;
		}
		keyMenu = _getch();
		if (keyMenu == 0 || keyMenu == 224) // ���������� �������� ��� ������� �� ������� ��� F ������� 
			keyMenu = _getch();

		switch (keyMenu) // �������� ������� �������
		{
		case 72: // ������� �����
			if (menuPos == 1)
				menuPos = menuMaxElem;
			else
				--menuPos;
			break;
		case 80: // ������� ����
			if (menuPos == menuMaxElem)
				menuPos = 1;
			else
				++menuPos;
			break;
		case 13: // Enter
			if (menuPos == 1)
			{
				short menuPosGame = 1; // ������� � ����
				short menuMaxElemGame = 3; // ���������� ��������� � ���� 
				while (true)
				{
					setlocale(0, "");
					setColor(WHITE, BLACK);
					gotoXY(40, 22);
					cout << "    �������               ";
					gotoXY(40, 24);
					cout << "  �� ���������            ";
					gotoXY(40, 26);
					cout << "     �����               ";
					gotoXY(40, 28);
					cout << "                        ";
					setColor(DARKGREEN, BLACK);
					
					
					switch (menuPosGame) // ����������� ������ ���� � ����������� �� �������
					{
					case 1:
						gotoXY(40, 22);
						setColor(GREEN, BLACK);
						cout << "    �������       ";
						break;
					case 2:
						gotoXY(40, 24);
						setColor(GREEN, BLACK);
						cout << "  �� ���������    ";
						break;
					case 3:
						gotoXY(40, 26);
						setColor(GREEN, BLACK);
						cout << "     �����        ";
						break;
					}

					keyMenu = _getch();
					if (keyMenu == 0 || keyMenu == 224) // ���������� �������� ��� ������� �� ������� ��� F ������� 
						keyMenu = _getch();

					switch (keyMenu) // �������� ������� �������
					{
					case 72: // ������� �����
						if (menuPosGame == 1)
							menuPosGame = menuMaxElemGame;
						else
							--menuPosGame;
						break;
					case 80: // ������� ����
						if (menuPosGame == menuMaxElemGame)
							menuPosGame = 1;
						else
							++menuPosGame;
						break;
					case 13: // Enter
						if (menuPosGame == 1)
						{
							game(1);
							return;
						}
						else if (menuPosGame == 2)
						{
							game(0);
							return;
						}
						else if (menuPosGame == 3)
						{
							return;
						}
						break;
					case 27:
						return;
					}
				}
			}
			else if (menuPos == 2)
			{
				editor();
				return;
			}
			else if (menuPos == 3)
			{
				exit(0);
			}
			break;
		case 27:
			exit(0);
		}
	}
}

void loadLevel(int n)
{
	FILE* f;
	int c = 0; // �������� �������� ���������� �������
	char* path = new char[100]; // ���� � �����

	gotoXY(0, 0); // �������� ����� ��� �� ����������
	system("mkdir data\\levels");
	gotoXY(0, 0);
	line(100, ' '); // �������� ���������� ���������

	if (n == 0) // ����� �� ���������
	{
		strcpy_s(path, 99, "data/levels/mylevel.txt");
		fopen_s(&f, path, "a+");
	}
	else // ����� �������
	{
		char* numlev = new char[3];
		strcpy_s(path, 99, "data/levels/level");
		_itoa_s(n, numlev, 2, 10);
		strcat_s(path, 99, numlev);
		strcat_s(path, 99, ".txt");
		fopen_s(&f, path, "a+");
		delete[]numlev;
	}
	gotoXY(0, 7); // ��������� �������� ����
	setColor(GREEN, BLACK);
	setlocale(0, "C");
	for (int y = 0; y < heightfield + 2; ++y)
	{
		for (int x = 0; x < widthField + 2; ++x)
		{
			if (x == 0 || y == 0 || x == widthField + 1 || y == heightfield + 1)
				cout << char(219);
			else
				cout << " ";
		}
		cout << "\n";
	}
	for (int i = 0; i < heightfield; ++i) // ��������� �������
	{
		for (int j = 0; j < widthField; ++j)
		{
			field[i][j] = 0;
		}
	}
	bool error = 0;
	for (int i = 0; i < heightfield; ++i) // ���������� � �����
	{
		for (int j = 0; j < widthField; ++j)
		{
			if (feof(f)) // ��������������� ����� �����
			{
				fclose(f); // �������� �����
				fopen_s(&f, path, "w+"); // �������� � ���������� �����
				for (int i = 0; i < heightfield; ++i) // ��������� �������
				{
					for (int j = 0; j < widthField; ++j)
					{
						field[i][j] = 0;
					}
				}
				for (int i = 0; i < heightfield; ++i) // ���������� ����� ������
				{
					for (int j = 0; j < widthField; ++j)
					{
						fputc('0', f);
					}
					if (i == heightfield - 1)
						break;
					fputc('\n', f);
				}
				setlocale(0, "");
				gotoXY(0, 0);
				cout << "������ ��� �������� " << path <<
					" \n������� ����� ������� ��� �����������";
				_getch();
				gotoXY(0, 0);
				line(100, ' ');
				gotoXY(0, 1);
				line(100, ' ');
				fclose(f);
				error = 1;
				break;
			}
			c = fgetc(f);
			if ((int)c != 13 && (int)c != 10) // ������ ������� �������� ������ � �������� �������
			{
				field[i][j] = c - 48; // �.� ����������� ��� �������, ����� ������ 48 ��� ��������� �����
			}
			else
				--j; // ������� �������� ���� ���������� ������ �������� ������ � �������� �������
		}
		if (error) // ��� ������ ���������� ����������
			break;
	}
	field[27][39] = 0; // ������������ ����� ������� ����
	field[26][39] = 0;
	field[25][39] = 0;
	field[28][39] = 0;
	delete[]path; // ���������� ������
	fclose(f); // ������� ����

	setColor(GREEN, BLACK);
	setlocale(0, "C");
	for (int y = 8; y < heightfield + 8; ++y) // ��������� ������
	{
		for (int x = 1; x < widthField + 1; ++x)
		{
			gotoXY(x, y);
			if (field[y - 8][x - 1] == 1)
			{
				setColor(WHITE, BLACK);
				cout << '*';
				 //cout << char(15);
				setColor(GREEN, BLACK);
			}
			else
				cout << " ";
		}
		cout << "\n";
	}
	setlocale(0, "");
}

void editor()
{
	system("cls");

	gotoXY(0, 7);
	setColor(GREEN, BLACK);
	setlocale(0, "C");
	for (int y = 0; y < heightfield + 2; ++y) // �����
	{
		for (int x = 0; x < widthField + 2; ++x)
		{
			if (x == 0 || y == 0 || x == widthField + 1 || y == heightfield + 1)
				cout << char(219);
			else
				cout << " ";
		}
		cout << "\n";
	}

	gotoXY(0, 0);
	system("mkdir data\\levels");
	gotoXY(0, 0);
	line(100, ' ');

	FILE* f;
	char* path = new char[100];
	strcpy_s(path, 99, "data/levels/mylevel.txt");
	fopen_s(&f, path, "a+");

	bool error = 0;
	int s = 0;
	for (int i = 0; i < heightfield; ++i) // ���������� � �����
	{
		for (int j = 0; j < widthField; ++j)
		{
			if (feof(f)) // ��������������� ����� �����
			{
				fclose(f);
				fopen_s(&f, path, "w+"); // ���������� �����
				for (int i = 0; i < heightfield; ++i) // ��������� �������
				{
					for (int j = 0; j < widthField; ++j)
					{
						field[i][j] = 0;
					}
				}
				for (int i = 0; i < heightfield; ++i) // ���������� ����� ������
				{
					for (int j = 0; j < widthField; ++j)
					{
						fputc('0', f);
					}
					if (i == heightfield - 1)
						break;
					fputc('\n', f);
				}
				setlocale(0, "");
				gotoXY(0, 0);
				cout << "������ ��� �������� " << path <<
					" \n������� ����� ������� ��� �����������";
				_getch();
				gotoXY(0, 0);
				line(100, ' ');
				gotoXY(0, 1);
				line(100, ' ');
				fclose(f);
				error = 1;
				break;
			}
			s = fgetc(f);
			if ((int)s != 13 && (int)s != 10) // ������ ������� �������� ������ � �������� �������
			{
				field[i][j] = s - 48; // �.� ����������� ��� �������, ����� ������ 48 ��� ��������� �����
				gotoXY(j + 1, i + 8);
				if (field[i][j] == 1)
				{
					setColor(WHITE, BLACK);
					cout << '*';
					setColor(GREEN, BLACK);
				}
				else
					cout << " ";
			}
			else
				--j; // ������� �������� ���� ���������� ������ �������� ������ � �������� �������
		}
		if (error)
			break;
	}

	HANDLE h2 = GetStdHandle(STD_INPUT_HANDLE); // ���������� �����
	SetConsoleMode(h2, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS); // �������� ����� ������������� ����
	INPUT_RECORD all_events[256]; // ������  ������������ �������
	DWORD e; // ���������� ������������ �������
	COORD c;
	char bh = '*';

	setColor(WHITE, BLACK);
	setlocale(0, "");

	gotoXY(35, 3);
	cout << "�������� �������";

	gotoXY(86, 10);
	cout << "���������";

	gotoXY(86, 14);
	cout << "�������";

	gotoXY(86, 18);
	cout << "��������";

	gotoXY(86, 22);
	cout << " �����";

	gotoXY(0, 0);
	setColor(WHITE, BLACK);
	while (true)
	{
		ReadConsoleInput(h2, all_events, 256, &e);
		for (int i = 0; i < e; ++i)
		{
			c.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
			c.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;
			if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && c.Y > 7 && c.Y < 48 && c.X > 0 && c.X < 81) // ��������� �� ����
			{
				if (bh == '*')
				{
					SetConsoleCursorPosition(h, c);
					field[c.Y - 8][c.X - 1] = 1;
					cout << bh;
				}
				else
				{
					SetConsoleCursorPosition(h, c);
					field[c.Y - 8][c.X - 1] = 0;
					cout << ' ';
				}
			}
			else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && c.Y == 14 && c.X >= 86 && c.X <= 94) // ����� �����������
			{
				setlocale(0, "");
				if (bh == '*')
				{
					gotoXY(86, 14);
					cout << "�����  ";
					bh = '#';
				}
				else
				{
					gotoXY(86, 14);
					cout << "�������";
					bh = '*';
				}
				setlocale(0, "C");
			}
			else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && c.Y == 18 && c.X >= 86 && c.X <= 94) // �������� �����
			{
				gotoXY(86, 14);
				setlocale(0, "");
				cout << "�������";
				setlocale(0, "C");
				bh = '*';
				for (int i = 0; i < heightfield; ++i)
				{
					for (int j = 0; j < widthField; ++j)
					{
						field[i][j] = 0;
					}
				}
				gotoXY(0, 7);
				setColor(GREEN, BLACK);
				for (int y = 0; y < heightfield + 2; ++y)
				{
					for (int x = 0; x < widthField + 2; ++x)
					{
						if (x == 0 || y == 0 || x == widthField + 1 || y == heightfield + 1)
							cout << char(219);
						else
							cout << " ";
					}
					cout << "\n";
				}
				setColor(WHITE, BLACK);
			}
			else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && c.Y == 22 && c.X >= 86 && c.X <= 94) // �����
			{
				system("cls");
				return;
			}
			else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && c.Y == 10 && c.X >= 86 && c.X <= 94) // ���������
			{
				FILE* f;
				const char* ps = "\n";
				gotoXY(1, 3);

				fopen_s(&f, "data/levels/mylevel.txt", "w+");
				for (int i = 0; i < heightfield; ++i)
				{
					for (int j = 0; j < widthField; ++j)
					{
						char* s = new char[2];
						_itoa_s(field[i][j], s, 1, 10);
						fputs(s, f);
						delete s;
					}
					if (i == heightfield - 1)
						break;
					fputc(*ps, f);
				}
				fclose(f);
				system("cls");
				return;
			}
		}
	}
}

void game(bool career)
{
	system("cls");
	srand(time(0));

	int lengthSnake = startLengthSnake; // ������� ����� ����
	int speed = 70; // ������� ��������
	int speedS = 25;
	int direction = UP; // ����������� ��������
	int banDirection = DOWN; // ����������� ����������� ��������
	char key = 0; // ��� ������� �������
	int score = 0; // ��������� ����
	int scoreTemp = 0;
	int scoreBonus = 100; // ����� � �����
	bool state = 1; // ��������� ����, 1 �������, 0 ��������
	int level = 1; // ������� �������
	int remain = 5; // ������� ����� �� ������
	int lives = 3; // ���������� ������
	int dizCount = 2; // ���������� ����������������
	bool dizState = 0; // ������ ������ ���������������
	int superSpeedCount = 2; // ������ ������ �������������
	bool superSpeedState = 0; // ���������� ��������������
	int lifeTime = 0; // ����� ����������� ����� �����
	snake = new COORD[lengthSnake]; // �������� ����

	setlocale(0, ""); // ��������� ��������������� ����������
	if (career)
	{
		gotoXY(84, 12);
		setColor(RED, BLACK);
		cout << char(4);
		setColor(WHITE, BLACK);
		cout << "  ������";

		gotoXY(84, 14);
		setColor(GREEN, BLACK);
		cout << char(3);
		setColor(WHITE, BLACK);
		cout << "  �����";

		gotoXY(84, 16);
		setColor(BLUE, BLACK);
		cout << char(15);
		setColor(WHITE, BLACK);
		cout << "  �����������";

		gotoXY(84, 18);
		setColor(YELLOW, BLACK);
		cout << char(15);
		setColor(WHITE, BLACK);
		cout << "  �������������";
	}

	setColor(GREEN, BLACK);
	gotoXY(86, 30);
	cout << "����������";
	setColor(WHITE, BLACK);
	gotoXY(90, 32);
	cout << char(24);
	gotoXY(94, 34);
	cout << char(26);
	gotoXY(86, 34);
	cout << char(27);
	gotoXY(90, 36);
	cout << char(25);

	gotoXY(84, 40);
	setColor(GREEN, BLACK);
	cout << "�����:";
	gotoXY(92, 40);
	setColor(WHITE, BLACK);
	cout << "������";

	gotoXY(84, 44);
	setColor(GREEN, BLACK);
	cout << "�����:";
	gotoXY(92, 44);
	setColor(WHITE, BLACK);
	cout << "Escape";

	if (career)
	{
		setColor(GREEN, BLACK);
		gotoXY(3, 5);
		cout << "�������: ";
		gotoXY(17, 5);
		cout << "�������� �����: ";
		gotoXY(53, 5);
		cout << "������:";
	}

	gotoXY(66, 5);
	setColor(GREEN, BLACK);
	cout << "����:";

	gotoXY(0, 7); // ��������� �������� ����
	setColor(GREEN, BLACK);
	setlocale(0, "C");
	for (int y = 0; y < heightfield + 2; ++y)
	{
		for (int x = 0; x < widthField + 2; ++x)
		{
			if (x == 0 || y == 0 || x == widthField + 1 || y == heightfield + 1)
				cout << char(219);
			else
				cout << " ";
		}
		cout << "\n";
	}
	if (career)
		showLevelNumber(1); // �������� �������� ������

	gotoXY(27, 2); // �������� ������������
	setlocale(0, "");
	setColor(WHITE, BLACK);
	cout << "��� ������ ���� ������� Enter";
	while (_getch() != 13);
	gotoXY(22, 2); // �������� ������
	line(50, ' ');

	 // ��������� ��������� ����
	snake[0].X = 40;
	snake[0].Y = 37;
	snake[1].X = 40;
	snake[1].Y = 38;
	snake[2].X = 40;
	snake[2].Y = 39;
	field[snake[0].Y - 8][snake[0].X - 1] = 3;
	field[snake[1].Y - 8][snake[1].X - 1] = 3;
	field[snake[2].Y - 8][snake[2].X - 1] = 3;
	if (career == 1) // ����� ������ ����
		loadLevel(1);
	else
		loadLevel(0);
	addApple(); // ��������� ������
	if (career) // ���������� ������� ���������
	{
		diz = new COORD[dizCount];
		addDiz(dizCount);
		superSpeed = new COORD[superSpeedCount];
		addSuperSpeed(superSpeedCount);
	}
	setColor(GREEN, BLACK);
	gotoXY(20, 0);
	cout << "S         N         A         K         E";

	while (true) // ������� ����
	{
		if (debug)
		{
			setColor(7, BLACK);
			gotoXY(83, 20);
			cout << "Apple X.Y";
			gotoXY(83, 21);
			cout << apple.X << " " << apple.Y << " ";
			gotoXY(83, 22);
			cout << "Snake X.Y";
			gotoXY(83, 23);
			cout << snake[0].X << " " << snake[0].Y << " ";
			gotoXY(83, 24);
			cout << "Lifetime = " << lifeTime << " ";
			gotoXY(83, 25);
			cout << "Speed: " << speed << " ";
			gotoXY(83, 26);
			cout << "Key code = " << (int)key;
			gotoXY(83, 27);
			cout << "\'n\' = next level";
		}


		if (scoreBonus > 0) // ���������� ������
			--scoreBonus;

		if (lifeTime < 10 && lifeTime > 1) // ������� ������ �����
		{
			SetConsoleCursorPosition(h, life);
			if (lifeTime % 2)
				cout << " ";
			else
				cout << char(3);
		}

		if (lifeTime > 1) // ���������� ������� ������ �����
			--lifeTime;
		else if (lifeTime == 1) // �������� �����
		{
			SetConsoleCursorPosition(h, life);
			cout << " ";
			field[life.Y - 8][life.X - 1] = 0;
			life.X = 0;
			life.Y = 0;
			--lifeTime;
		}

		gotoXY(72, 5); // ������� ���� ������
		setColor(WHITE, BLACK);
		cout << scoreTemp << "   ";
		if (career)
		{
			setColor(WHITE, BLACK);
			gotoXY(61, 5); // ���������� ���������� ������
			cout << lives;
			gotoXY(33, 5); // ������� �����
			setColor(WHITE, BLACK);
			cout << remain << " ";
			setColor(GREEN, BLACK);
			gotoXY(12, 5); // �������
			setColor(WHITE, BLACK);
			cout << level;
			setColor(GREEN, BLACK);
		}

		if (direction == UP) // ����� ���������� ��������
			banDirection = DOWN;
		else if (direction == RIGHT)
			banDirection = LEFT;
		else if (direction == DOWN)
			banDirection = UP;
		else if (direction == LEFT)
			banDirection = RIGHT;

		while (_kbhit()) // ������������ ������� ������
		{
			key = _getch();
			if (key == 0 || key == 224) // ���������� �������� ��� ������� �� ������� ��� F ������� 
			{
				key = _getch();
			}
			if (key == 119 || key == 72 && direction != DOWN && banDirection != UP)
				direction = UP;
			else if (key == 77 && direction != LEFT && banDirection != RIGHT)
				direction = RIGHT;
			else if (key == 80 && direction != UP && banDirection != DOWN)
				direction = DOWN;
			else if (key == 75 && direction != RIGHT && banDirection != LEFT)
				direction = LEFT;
			else if (key == 27) // Esc
			{
				system("cls");
				return;
			}
			else if (key == 32) // ������
			{
				gotoXY(3, 2);
				cout << "�����";
				_getch();
				gotoXY(3, 2);
				cout << "     ";
			}
			else if (key == 96) // ������, ��������� � ���������� ����������� ������
			{
				if (debug)
				{
					gotoXY(83, 20);
					line(16, ' ');
					gotoXY(83, 21);
					line(16, ' ');
					gotoXY(83, 22);
					line(16, ' ');
					gotoXY(83, 23);
					line(16, ' ');
					gotoXY(83, 24);
					line(16, ' ');
					gotoXY(83, 25);
					line(16, ' ');
					gotoXY(83, 26);
					line(16, ' ');
					gotoXY(83, 27);
					line(16, ' ');
					debug = 0;
				}
				else
					debug = 1;
			}
			else if (key == 110 && debug && career) // ������� n, ������� �� ��������� ������� ��� �������
			{
				remain = 0;
			}
		}
		SetConsoleCursorPosition(h, snake[0]); // �������� ������ ������
		cout << " ";
		field[snake[0].Y - 8][snake[0].X - 1] = 0;
		SetConsoleCursorPosition(h, snake[lengthSnake - 1]); // �������� ����� ������
		cout << " ";
		field[snake[lengthSnake - 1].Y - 8][snake[lengthSnake - 1].X - 1] = 0;
		for (int i = lengthSnake - 1; i > 0; --i) // ���������� ���������
		{
			snake[i].Y = snake[i - 1].Y;
			snake[i].X = snake[i - 1].X;
		}

		if (!dizState) // ���������� ��������
		{
			if (direction == UP) // ��������� ��������� ������ � ����������� �� �����������
				--snake[0].Y;
			else if (direction == RIGHT)
				++snake[0].X;
			else if (direction == DOWN)
				++snake[0].Y;
			else if (direction == LEFT)
				--snake[0].X;
		}
		else // �������� � ���������������
		{
			if (direction == UP) // ��������� ��������� ������ � ����������� �� �����������
				++snake[0].Y;
			else if (direction == RIGHT)
				--snake[0].X;
			else if (direction == DOWN)
				--snake[0].Y;
			else if (direction == LEFT)
				++snake[0].X;
		}

		if (career && remain <= 0) // �������� ������ ������
		{
			++level;
			if (level == 10) // ��������� ��������
			{
				showLevelNumber(10);
				system("cls");
				return;
			}
			remain = level * 5;
			lengthSnake = 3;
			direction = UP;
			speed -= 3;
			score += scoreTemp;
			scoreTemp = score;
			 // ��������� ��������� ����
			snake[0].X = 40;
			snake[0].Y = 37;
			snake[1].X = 40;
			snake[1].Y = 38;
			snake[2].X = 40;
			snake[2].Y = 39;
			field[snake[0].Y - 8][snake[0].X - 1] = 3;
			field[snake[1].Y - 8][snake[1].X - 1] = 3;
			field[snake[2].Y - 8][snake[2].X - 1] = 3;
			showLevelNumber(level); // �������� �������� ������
			gotoXY(12, 2);
			setColor(WHITE, BLACK);
			cout << "�� ������ �� ������� " << level << ", ������� Enter ��� ������ ����";
			while (_getch() != 13);
			gotoXY(3, 2);
			line(80, ' ');
			loadLevel(level);
			setColor(GREEN, BLACK);
			gotoXY(20, 0);
			cout << "S         N         A         K         E";
			addApple();
			if (career)
			{
				for (int i = 0; i < dizCount; ++i) // �������� ������ ��������������
					field[diz[i].Y - 8][diz[i].X - 1] = 0;
				addDiz(++dizCount); // ���������� ����� ��������������
				if (life.Y != 0) // ���� �������� ������ ����� �� ����
				{
					field[life.Y - 8][life.X + 1] = 0; // �������� ����� � ����
					life.X = 0;
					life.Y = 0;
					lifeTime = 0;
				}
				for (int i = 0; i < superSpeedCount; ++i) // �������� ������ ��������������
					field[superSpeed[i].Y - 8][superSpeed[i].X - 1] = 0;
				addSuperSpeed(++superSpeedCount); // ���������� ����� ��������������
			}
			continue;
		}
		for (int i = 0; career && (i < dizCount); ++i) // ��������� �� �����������
		{
			if (snake[0].X == diz[i].X && snake[0].Y == diz[i].Y && field[diz[i].Y - 8][diz[i].X - 1] == 4)
			{
				if (direction == UP) // ����� �����������
					direction = RIGHT;
				else if (direction == RIGHT)
					direction = DOWN;
				else if (direction == DOWN)
					direction = LEFT;
				else if (direction == LEFT)
					direction = UP;
				field[diz[i].Y - 8][diz[i].X - 1] == 0; // �������� ��������������
				dizState = 1; // ��������� ������ ��������������
				break;
			}
		}

		for (int i = 0; career && (i < dizCount); ++i) // ��������� �� �������������
		{
			if (snake[0].X == superSpeed[i].X && snake[0].Y == superSpeed[i].Y && field[superSpeed[i].Y - 8][superSpeed[i].X - 1] == 6)
			{
				field[superSpeed[i].Y - 8][superSpeed[i].X - 1] == 0; // �������� �������������
				superSpeedState = 1; // ��������� ������ �������������
				break;
			}
		}

		if (snake[0].X == life.X && snake[0].Y == life.Y) // ���� ������� �����
		{
			field[life.Y - 8][life.X + 1] = 0;
			++lives;
			life.X = 0;
			life.Y = 0;
			lifeTime = 0;
		}
		if (snake[0].X == apple.X && snake[0].Y == apple.Y) // ���� ������� ������
		{
			if (career) // ����� �������
			{
				--remain;
				int t = 0; // ����� ���������� �� ���� � ������ 1/3
				t = rand() % 3;
				if (t == 1)
				{
					SetConsoleCursorPosition(h, life);
					cout << " ";
					addLife();
					lifeTime = 32;
				}
			}
			else // ����� �� ���������
				speed -= 3;

			scoreTemp += 10;
			scoreTemp += scoreBonus;
			scoreBonus = 100;
			if (dizState)
			{
				if (direction == UP) // ����� �����������
					direction = RIGHT;
				else if (direction == RIGHT)
					direction = DOWN;
				else if (direction == DOWN)
					direction = LEFT;
				else if (direction == LEFT)
					direction = UP;
			}
			dizState = 0; // ���������� �������
			superSpeedState = 0;

			COORD* temp = new COORD[lengthSnake]; // ��������� ������ ���������
			for (int i = 0; i < lengthSnake; ++i) // ���������� ���� �� ��������� ������
			{
				temp[i] = snake[i];
			}
			delete[]snake; // �������� ������� �������
			snake = new COORD[++lengthSnake]; // �������� ������ ������� �� ���� ������� ������ �����������
			for (int i = 0; i < (lengthSnake - 1); ++i) // ������ � ����� ������
			{
				snake[i] = temp[i];
			}
			snake[lengthSnake - 1].X = snake[lengthSnake - 2].X; // ������� ��������� ������ ��������
			snake[lengthSnake - 1].Y = snake[lengthSnake - 2].Y;
			delete[]temp; // �������� ���������� �������

			field[apple.Y - 8][apple.X - 1] = 0; // ������� ���� � �������
			if (remain > 0)
				addApple(); // ��������� ������ ������
		}
		for (int i = 1; i < lengthSnake; ++i) // �������� �� ������������ � �����
		{
			if (snake[0].X == snake[i].X && snake[0].Y == snake[i].Y)
			{
				state = 0;
			}
		}
		if (field[snake[0].Y - 8][snake[0].X - 1] == 1 || snake[0].Y <= 7 || snake[0].Y >= heightfield + 8 || snake[0].X <= 0 || snake[0].X >= widthField + 1 || state == 0) // �������� �� ������������ � ������������ ��� �����
		{
			--lives; // ������ �����
			scoreTemp = score;
			if (lives && career) // ������ ������� ������
			{
				for (int i = 0; i < lengthSnake; ++i) // ��������� �������� ����
				{
					SetConsoleCursorPosition(h, snake[i]);
					if (i == 0)
					{
						setColor(DARKCYAN, BLACK);
						cout << char(1);
					}
					else
					{
						setColor(DARKGREEN, BLACK);
						cout << "*";
					}
				}

				gotoXY(10, 2);
				setColor(YELLOW, BLACK);
				cout << "�������� " << lives;
				if (lives == 1)
					cout << " �����. ";
				else
					cout << " �����. ";
				cout << "������� Enter ����� ������ ������� ������.";
				while (_getch() != 13);
				gotoXY(3, 2);
				line(80, ' ');
				if (career)
				{
					loadLevel(level);
					/*if(dizState) // ����������� ����������� ��������
					{
					if(direction == UP) // ����� �����������
					banDirection = DOWN;
					}*/
					for (int i = 0; career && (i < dizCount); ++i) // �������� ������ ��������������
					{
						field[diz[i].Y - 8][diz[i].X - 1] = 0;
					}
					addDiz(dizCount);
					if (life.Y != 0) // ���� �������� ������ ����� �� ����
					{
						field[life.Y - 8][life.X + 1] = 0; // �������� ����� � ����
						life.X = 0;
						life.Y = 0;
						lifeTime = 0;
					}
					for (int i = 0; i < superSpeedCount; ++i) // �������� ������ ��������������
						field[superSpeed[i].Y - 8][superSpeed[i].X - 1] = 0;
					addSuperSpeed(superSpeedCount);
				}
				else
					loadLevel(0);
				addApple();

				setColor(GREEN, BLACK);
				gotoXY(20, 0);
				cout << "S         N         A         K         E";

				remain = level * 5;
				dizState = 0;
				superSpeedState = 0;
				lengthSnake = startLengthSnake;
				direction = UP;
				state = 1;
				delete[]snake;
				snake = new COORD[lengthSnake];
				 // ��������� ��������� ����
				snake[0].X = 40;
				snake[0].Y = 37;
				snake[1].X = 40;
				snake[1].Y = 38;
				snake[2].X = 40;
				snake[2].Y = 39;
				field[snake[0].Y - 8][snake[0].X - 1] = 3;
				field[snake[1].Y - 8][snake[1].X - 1] = 3;
				field[snake[2].Y - 8][snake[2].X - 1] = 3;
				continue; // ���������� ����
			}
			gotoXY(13, 2);
			setColor(RED, BLACK);
			cout << "�� ���������, ������� Enter ��� ������ � ������� ����.\n";
			for (int i = 0; i < lengthSnake; ++i) // ��������� ������� ����
			{
				SetConsoleCursorPosition(h, snake[i]);
				if (i == 0)
				{
					setColor(RED, BLACK);
					cout << char(1);
				}
				else
				{
					setColor(DARKGREEN, BLACK);
					cout << "*";
				}
			}
			while (_getch() != 13); // �������� ������� Enter
			system("cls");
			delete[]snake;
			return;
		}

		for (int i = 0; i < lengthSnake; ++i) // ��������� ����
		{
			field[snake[i].Y - 8][snake[i].X - 1] = 3;
			SetConsoleCursorPosition(h, snake[i]);
			if (i == 0)
			{
				if (dizState)
					setColor(CYAN, BLACK);
				else if (superSpeedState)
					setColor(YELLOW, BLACK);
				else
					setColor(GREEN, BLACK);
				cout << char(1);
			}
			else
			{
				if (dizState)
					setColor(BLUE, BLACK);
				else if (superSpeedState)
					setColor(DARKYELLOW, BLACK);
				else
					setColor(DARKGREEN, BLACK);
				cout << "*";
			}
		}
		if (superSpeedState)
			Sleep(speedS);
		else
			Sleep(speed);
	}
}

void addApple()
{
	while (true)
	{
		apple.X = rand() % widthField + 1;
		apple.Y = rand() % heightfield + 8;
		if (field[apple.Y - 8][apple.X - 1] == 0)
		{
			SetConsoleCursorPosition(h, apple);
			setColor(RED, BLACK);
			cout << char(4);
			setColor(GREEN, BLACK);
			field[apple.Y - 8][apple.X + 1] = 2;
			break;
		}
		else
			continue;
	}
}

void addDiz(int k)
{
	delete[]diz;
	diz = new COORD[k];
	for (int i = 0; i < k; ++i)
	{
		while (true)
		{
			diz[i].X = rand() % widthField + 1;
			diz[i].Y = rand() % heightfield + 8;
			if (field[diz[i].Y - 8][diz[i].X - 1] == 0)
			{
				SetConsoleCursorPosition(h, diz[i]);
				setColor(BLUE, BLACK);
				cout << char(15);
				setColor(GREEN, BLACK);
				field[diz[i].Y - 8][diz[i].X - 1] = 4;
				break;
			}
		}
	}
}

void addSuperSpeed(int k)
{
	delete[]superSpeed;
	superSpeed = new COORD[k];
	for (int i = 0; i < k; ++i)
	{
		while (true)
		{
			superSpeed[i].X = rand() % widthField + 1;
			superSpeed[i].Y = rand() % heightfield + 8;
			if (field[superSpeed[i].Y - 8][superSpeed[i].X - 1] == 0)
			{
				SetConsoleCursorPosition(h, superSpeed[i]);
				setColor(YELLOW, BLACK);
				cout << char(15);
				setColor(GREEN, BLACK);
				field[superSpeed[i].Y - 8][superSpeed[i].X - 1] = 6;
				break;
			}
		}
	}
}

void addLife()
{
	while (true)
	{
		life.X = rand() % widthField + 1;
		life.Y = rand() % heightfield + 8;
		if (field[life.Y - 8][life.X - 1] == 0)
		{
			SetConsoleCursorPosition(h, life);
			setColor(GREEN, BLACK);
			cout << char(3);
			field[life.Y - 8][life.X + 1] = 5;
			break;
		}
	}
}

void line(int n, char s)
{
	for (; n > 0; --n)
		cout << s;
}

void showLevelNumber(int n)
{
	for (int y = 8; y < heightfield + 8; ++y) // ������� ����
	{
		for (int x = 1; x < widthField + 1; ++x)
		{
			gotoXY(x, y);
			cout << " ";
		}
		cout << "\n";
	}
	gotoXY(0, 15);
	if (n == 1)
		cout << "                                        **   \n"
		"                                        **   \n"
		"                                      ****   \n"
		"                                    *** **   \n"
		"                                   **   **   \n"
		"                                        **   \n"
		"                                        **   \n"
		"                                        **   \n"
		"                                        **   \n"
		"                                        **   \n"
		"                                        **   \n"
		"                                        **   \n"
		"                                        **   \n";
	else if (n == 2)
	{
		cout << "                                      ********                \n"
			"                                   **************             \n"
			"                                  ****         ***            \n"
			"                                 ****           ***           \n"
			"                                                ***           \n"
			"                                              ****            \n"
			"                                             ****             \n"
			"                                          *****               \n"
			"                                        ****                  \n"
			"                                     *****                    \n"
			"                                   ****                       \n"
			"                                  *****************           \n"
			"                                 ******************           \n";
	}
	else if (n == 3)
	{
		cout << "                                    ********               \n"
			"                                  **************           \n"
			"                                ******     ******          \n"
			"                               ****           ****        \n"
			"                                               ****        \n"
			"                                                ***        \n"
			"                                         **********           \n"
			"                                         *********          \n"
			"                                            ******          \n"
			"                                                ***       \n"
			"                                                 **       \n"
			"                             ****               ***       \n"
			"                              ****            ****         \n"
			"                                *****************         \n"
			"                                  *************            \n";
	}
	else if (n == 4)
	{

		cout << "                                           ****        \n"
			"                                          ******       \n"
			"                                         *******       \n"
			"                                       **** ****       \n"
			"                                      ****  ****       \n"
			"                                    *****   ****       \n"
			"                                   ****     ****       \n"
			"                                 ****       ****       \n"
			"                                ****        ****       \n"
			"                               ********************    \n"
			"                               ********************    \n"
			"                                            ****       \n"
			"                                            ****       \n"
			"                                            ****       \n";
	}
	else if (n == 5)
	{
		cout << "                                   ****************  \n"
			"                                  *****************  \n"
			"                                 ****                \n"
			"                                 ***                 \n"
			"                                ****                 \n"
			"                                ***   *******        \n"
			"                                ****************     \n"
			"                               *****         *****   \n"
			"                                               ****  \n"
			"                                                ***  \n"
			"                                                ***  \n"
			"                               ****            ****  \n"
			"                                ****          ****   \n"
			"                                 ***************     \n"
			"                                    **********       \n";
	}
	else if (n == 6)
	{
		cout << "                                      ************    \n"
			"                                    *******   ******  \n"
			"                                   ****          **** \n"
			"                                  ****                \n"
			"                                  ***                 \n"
			"                                 ****  **********     \n"
			"                                 ******************   \n"
			"                                 *****          ****  \n"
			"                                 ****            **** \n"
			"                                  ***             *** \n"
			"                                  ***            **** \n"
			"                                   ****         ****  \n"
			"                                    ***************   \n"
			"                                       *********      \n";

	}
	else if (n == 7)
	{
		cout << "                                 *********************\n"
			"                                 ******************** \n"
			"                                               *****  \n"
			"                                              *****   \n"
			"                                             ****     \n"
			"                                            ****      \n"
			"                                           ****       \n"
			"                                          ****        \n"
			"                                         ****         \n"
			"                                        ****          \n"
			"                                       ****           \n"
			"                                      ****            \n"
			"                                     ****             \n"
			"                                    ****              \n";
	}
	else if (n == 8)
	{
		cout << "                                    *******        \n"
			"                                  ************     \n"
			"                                ******    ******   \n"
			"                               ****          ****  \n"
			"                               ****          ****  \n"
			"                                ***          ****  \n"
			"                                  *************    \n"
			"                                  ************     \n"
			"                               *****        *****  \n"
			"                              ****            **** \n"
			"                              ****             *** \n"
			"                              ****            **** \n"
			"                               ****          ****  \n"
			"                                ****************   \n"
			"                                   **********      \n";
	}
	else if (n == 9)
	{
		cout << "                                    ********          \n"
			"                                  ************        \n"
			"                                ******    ******      \n"
			"                               ****           ***     \n"
			"                              ****            ****    \n"
			"                              ****             ***    \n"
			"                              ****            ****    \n"
			"                               *****        ******    \n"
			"                                 ************* ***    \n"
			"                                   ********    ***    \n"
			"                                              ****    \n"
			"                                             ****     \n"
			"                              *****         ****      \n"
			"                                ***************       \n"
			"                                  **********          \n";
	}
	else if (n == 10)
	{
		system("cls");
		int r = 0;
		while (true)
		{
			r = rand() % (16 - 9) + 9;
			gotoXY(0, 0);
			setColor(r, BLACK);
			if (_kbhit())
			{
				if (_getch() == 13)
					break;
			}
			cout << "                                    8B@7;i71@B                      \n"
				"                                  N@i:.:::,,.iO@                    \n"
				"                                 BSi,,:::::::,,i@7                  \n"
				"                                B7::::::::::,:,:i@;                 \n"
				"                               BL::O@B@r:::B@B@::r@                 \n"
				"                               @riBJ   @B7B    @j:7@         @      \n"
				"                              @7iB      @B      @:rB         B@     \n"
				"                             @7r@       @       @:vB        @2@    \n"
				"                             ,M7@,   B@ ,B G@    B;7@        :OS@   \n"
				"                             quL5@   @B B@  B    @;LB         @uB   \n"
				"                             BuvYB     M@v@     @57Y@         @j2B  \n"
				"                             @uJLuBO :B@7Lu@B  @@v7uB         Buj@  \n"
				"                             5qJjYuk@0uLYYuJ1BOYYLYU@         @uU1@ \n"
				"                              @5uujUuUjujujUuuuuJuuSB         @1u1@ \n"
				"                              @N5UUuUuUu2u2u2u2U2UFB          @221@ \n"
				"                               @EX1525U5252121252FBi          BFuSB \n"
				"                                @BEkk55152F152F1kB@           @51F@ \n"
				"                                  B@EPFXSk5F5kZBG:B           Bk5kB \n"
				"                                    .B@B@BBMMMr:ii@          BE5FX@ \n"
				"                                     iB   Biirr7r7B         r@FFFZM \n"
				"                                   B@@    @7vvLvvv@B@B@B@B: @XS5X@  \n"
				"                                 BB@      BuLYLjYJLJYujuu258BS5kP@  \n"
				"                                @B@       @2UuUu2uuJJLLLLvLuUZ55@.  \n"
				"                                B  M      Bk1F5F5S5S1F25UUuJ2O2qB   \n"
				"                               L   B      @FSSPP0qEqEqNXS11u58FO7   \n"
				"                               .        @@BM8q1UuuJujUuSXOOMOOO@    \n"
				"                                       B8uJ7r;rrrrrrrr7rrrvvJYkB    \n"
				"                                       @qYuuUuUuUu2u2uUuUuUu2jqB    \n"
				"                                       @S2U2u121U215212F251515k@    \n"
				"                                       BBOMMMMMMMOMOMOMMMMMOMOMB    \n"
				"                                     @OuYYLYLJLJLJLJvLLLLYLYLJYuM@  \n"
				"                                    @kFr7r7r777r777r777777777777FX@ \n"
				"                                    @Puuuu2u2uUu2u2U1u2U2u1u1U5UUk@ \n"
				"                                    B025UF11151F1F5F2F1S5F5F5F5F5NB \n"
				"                                    @ENkPXqXPPqXqXPkPXqXqXPXPkPSPMM \n"
				"                                     @B@@@B@B@B@B@B@BB@@B@B@B@B@B@  \n"
				"                                                          \n"
				"              BB      B@L      @7 8@  X@i      @7  qBi      Bv  P@B@@@B@B@U E@B@B@@@B@:    \n"
				"              rB     ,@M@     UB  EB  XB@.     Bv  S@B.     @7  P@          qB       r@i   \n"
				"               @L    MB B     Bu  X@  S@.@     @7  kB.B     B7  k@          X@        O@   \n"
				"               u@    @: @0   :@   q@  kB j@    B7  k@ UB    @r  XB          PB        GB   \n"
				"                B,  7@  r@   @8   X@  X@  B@   @7  PB  @B   B7  S@B@@@B@B@u F@       rB:   \n"
				"                MB  @F   Bi  B    qB  qB   @F  B7  X@   @F  @7  XB          k@@B@B@B@8.    \n"
				"                 @  @    N@ 1@    P@  X@    B: @r  NB    @: B7  X@          k@    2@       \n"
				"                 BMB@     @1@:    NB  qB    .B B7  P@    .@ @r  P@          PB     .@j     \n"
				"                 :B@:     B@@     0@  q@     rB@r  EB     i@B7  P@          N@       @E    \n"
				"                  @B      rBY     OB  O@      kBY  8@      F@L  G@@B@B@B@B2 O@        @Z   \n";
			gotoXY(23, 49);
			cout << "����������, �� ������ ��� ����, ��� ������ ������� Enter.";
			Sleep(50);
		}
		return;
	}

	gotoXY(0, 35);
	cout << "           **          *********** **         **   ***********  ** \n"
		"           ***        ************ ***       ***  ************  ***\n"
		"           ***        ***           ***     ***   ***           ***\n"
		"           ***        ***********    ***   ***    ***********   ***\n"
		"           ***        **              *** ***     **            ***\n"
		"           ********** ************     *****      ************  **********\n"
		"            ********   ***********      ***        ***********   *********\n";
	setlocale(0, "C");
	for (int i = 7; i < heightfield + 8; ++i) // ��������� ����� ������� ����
	{
		gotoXY(0, i);
		cout << char(219);
	}
	setlocale(0, "");
}