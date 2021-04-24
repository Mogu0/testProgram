#include<iostream>
#include<windows.h>
#include<stdlib.h>      
#include<time.h> 
#include<vector>
#include<iterator>
#include <conio.h>

/*
00 是在左上角!!!
左右动 列!!!y
上下动行 ！！x
*/
/*
	vector 用队列来代替！！！！！！！！
*/
using namespace std;
//蛇头
int snake_x;
int snake_y;
//蛇尾
int tail_x;
int tail_y;
int snake_length = 1;

//定义食物，蛇，边界  0为可行走区域
const int zero = 0;
const int board = 1;
const int snake_head = 2;
const int snake_body = 3;
const int food = 4;
const int snake_tail = 5;
//定义方向 
const int UP = 1;
const int DOWN = -1;
const int RIGHT = 2;
const int LEFT = -2;
//最大边界 
const int max_size = 15;
//画面用二维数组显示 

int screen[max_size][max_size] = { 0 };
//游戏状态
const int win = 0;
const int lose = 1;
const int game_continue = 2;
//蛇的运动方向 
vector<int> snakeDirection;

void initial_print();
void set_food();
bool in_game();

void initial_print() {
	system("cls");
	cout << "小游戏贪吃蛇!" << endl;
	srand((unsigned)time(NULL));

	for (int i = 0; i < max_size; i++) {
		for (int j = 0; j < max_size; j++) {
			if (i == 0 || i == max_size - 1 || j == 0 || j == max_size - 1)
				screen[i][j] = board;
		}
	}

	snake_x = rand() % 5 + 3;
	snake_y = rand() % 5 + 3;
	tail_x = snake_x;
	tail_y = snake_y;
	snakeDirection.push_back(2);
	screen[snake_x][snake_y] = snake_head;
	set_food();
	for (int i = 0; i < max_size; i++) {
		for (int j = 0; j < max_size; j++) {
			if (screen[i][j] == board) {
				cout << "* ";
			}
			if (screen[i][j] == snake_head) {
				cout << "@ ";
			}
			if (screen[i][j] == food) {
				cout << "! ";
			}
			if (screen[i][j] == zero) {
				cout << "  ";
			}

		}
		cout << "\n";
	}
}
void set_food() {
	srand((unsigned)time(NULL));

	int food_x = rand() % (max_size - 1) + 1;
	int food_y = rand() % (max_size - 1) + 1;
	while (screen[food_x][food_y] != zero) {
		food_x = rand() % (max_size - 1) + 1;
		food_y = rand() % (max_size - 1) + 1;
	}
	screen[food_x][food_y] = food;
}
bool in_game() {
	int tmp, dir = 0, tmpOther;
	//有键盘输入 
	if (_kbhit()) {
		tmpOther = _getch();
		tmp = _getch();
		switch (tmp) {                                 //判断方向
		case 72: dir = UP; break;
		case 80: dir = DOWN; break;
		case 75: dir = LEFT; break;
		case 77: dir = RIGHT; break;
		}

		if (dir == (-1 * snakeDirection[0]))
			return true;
		//一端插入一端删除!!! 
		vector <int>::iterator begin = snakeDirection.begin();
		snakeDirection.insert(begin, dir);

		int tmp_x = snake_x;
		int tmp_y = snake_y;
		switch (snakeDirection[0]) {
		case UP:    snake_x = tmp_x - 1;    break;
		case DOWN:  snake_x = tmp_x + 1;    break;
		case LEFT:  snake_y = tmp_y - 1;    break;
		case RIGHT: snake_y = tmp_y + 1;    break;
		}
		if (screen[snake_x][snake_y] == food)
		{
			screen[snake_x][snake_y] = snake_head;
			screen[tmp_x][tmp_y] = snake_body;

			snake_length++;
			if (snake_length == 2) {
				tail_x = tmp_x;
				tail_y = tmp_y;
			}
			set_food();
		}
		else if ((screen[snake_x][snake_y]) == snake_body || screen[snake_x][snake_y] == board) {
			return false;
		}
		else
		{
			screen[snake_x][snake_y] = snake_head;
			screen[tmp_x][tmp_y] = snake_body;
			snakeDirection.pop_back();
			if (snake_length > 1) {

				screen[tail_x][tail_y] = zero;
				switch (snakeDirection.back()) {
				case UP:    tail_x = tail_x - 1;    break;
				case DOWN:  tail_x = tail_x + 1;    break;
				case LEFT:  tail_y = tail_y - 1;    break;
				case RIGHT: tail_y = tail_y + 1;    break;
				}
			}
			else {
				screen[tail_x][tail_y] = zero;
				tail_x = snake_x;
				tail_y = snake_y;
			}

		}

	}
	else {
		int flag = 0;
		dir = snakeDirection[0];
		vector <int>::iterator begin = snakeDirection.begin();
		snakeDirection.insert(begin, dir);

		int tmp_x = snake_x;
		int tmp_y = snake_y;
		switch (snakeDirection.front()) {
		case UP:    snake_x = tmp_x - 1;    break;
		case DOWN:  snake_x = tmp_x + 1;    break;
		case LEFT:  snake_y = tmp_y - 1;    break;
		case RIGHT: snake_y = tmp_y + 1;    break;
		}
		if (screen[snake_x][snake_y] == food)
		{
			screen[snake_x][snake_y] = snake_head;
			screen[tmp_x][tmp_y] = snake_body;

			snake_length++;
			if (snake_length == 2) {
				tail_x = tmp_x;
				tail_y = tmp_y;
			}
			set_food();
		}
		else if ((screen[snake_x][snake_y]) == snake_body || screen[snake_x][snake_y] == board) {
			return false;
		}
		else
		{
			screen[snake_x][snake_y] = snake_head;
			screen[tmp_x][tmp_y] = snake_body;
			snakeDirection.pop_back();
			if (snake_length > 1) {
				screen[tail_x][tail_y] = zero;
				switch (snakeDirection.back()) {
				case UP:    tail_x = tail_x - 1;    break;
				case DOWN:  tail_x = tail_x + 1;    break;
				case LEFT:  tail_y = tail_y - 1;    break;
				case RIGHT: tail_y = tail_y + 1;    break;
				}
			}
			else {
				screen[tail_x][tail_y] = zero;
				tail_x = snake_x;
				tail_y = snake_y;
			}

		}

	}
	return true;
}
void print() {
	system("cls");
	cout << "小游戏贪吃蛇!" << endl;
	srand((unsigned)time(NULL));

	for (int i = 0; i < max_size; i++) {
		for (int j = 0; j < max_size; j++) {
			if (screen[i][j] == board) {
				cout << "* ";
			}
			if (screen[i][j] == snake_head) {
				cout << "@ ";
			}
			if (screen[i][j] == food) {
				cout << "! ";
			}
			if (screen[i][j] == zero) {
				cout << "  ";
			}
			if (screen[i][j] == snake_body) {
				cout << "0 ";
			}
		}
		cout << "\n";
	}
}
int main() {
	initial_print();
	while (true) {

		if (in_game())
		{
			print();
			cout << snakeDirection.size() << endl;
			cout << snake_length;
		}
		else
			break;
		Sleep(200);
	}
	cout << "you lose !!!!";
	while (true) {

	}
}