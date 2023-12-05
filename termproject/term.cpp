#include <windows.h>
#include <thread>
#include <iostream>
#include <random>
#include <cstdlib>
#include <conio.h>
#include "Word.h"
#include "make.h"
#include "UWord.h"
#include "Number.h"
#include <string>
#include <mutex>
using namespace std;

mutex mtx;
vector<word*> words;
word* origin = new word();
int checkorigin = -1;

void move_cursor(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void showCursor() {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void deleterain() {
	showCursor();
	for (int i = 0; i < words.size(); i++) {
		for (int j = 0; j < words[i]->getWords().size(); j++) {
			move_cursor(words[i]->getX() + j, words[i]->getY() - 4);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	hideCursor();
}

word* wordmaking() {
	word* a = new word();
	if (checkorigin == 0) {
		a = new alpha();
		if (!origin->nonew1()) {
			if (origin->what_w1() == "unique") {
				a->set_word(new unique_word());
			}
			else if (origin->what_w1() == "number") {
				a->set_word(new number());
			}
		}
		if (!origin->nonew2()) {
			if (origin->what_w2() == "unique") {
				a->set_word(new unique_word());
			}
			else if (origin->what_w2() == "number") {
				a->set_word(new number());
			}
		}
	}
	else if (checkorigin == 1) {
		a = new number();
		if (!origin->nonew1()) {
			if (origin->what_w1() == "alpha") {
				a->set_word(new alpha());
			}
			else if (origin->what_w1() == "unique") {
				a->set_word(new unique_word());
			}
		}
		if (!origin->nonew2()) {
			if (origin->what_w2() == "unique") {
				a->set_word(new unique_word());
			}
			else if (origin->what_w2() == "alpha") {
				a->set_word(new alpha());
			}
		}
	}
	else if (checkorigin == 2) {
		a = new unique_word();
		if (!origin->nonew1()) {
			if (origin->what_w1() == "alpha") {
				a->set_word(new alpha());
			}
			else if (origin->what_w1() == "number") {
				a->set_word(new number());
			}
		}
		if (!origin->nonew2()) {
			if (origin->what_w2() == "number") {
				a->set_word(new number());
			}
			else if (origin->what_w2() == "alpha") {
				a->set_word(new alpha());
			}
		}
	}
	return a;
}

void start_rain_thread() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 3);
	std::uniform_int_distribution<int> dis1(0, 50);
	bool flag = true;
	while (flag) {
		word* newWord = wordmaking();
		newWord->set_maxlength(6);
		newWord->makeword();
		newWord->setX(dis1(gen));
		newWord->setY(0);
		deleterain();
		mtx.lock();
		words.push_back(newWord);
		mtx.unlock();
		mtx.lock();
		for (int i = 0; i < words.size(); i++) {
			move_cursor(words[i]->getX(), words[i]->getY());
			words[i]->setY((words[i]->getY() + 4));
			std::cout << words[i]->getWords() << std::endl;
			if (words[i]->getY() >= 44) flag = false;
		}
		mtx.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(dis(gen)));
	}

}

void window_setting() {
	mtx.lock();
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_THICKFRAME);
	SetWindowPos(consoleWindow, NULL, 0, 0, 80 * 8, 50 * 16, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	system("cls");
	move_cursor(2, 45);
	std::cout << "->" << std::endl;
	move_cursor(0, 44);
	std::cout << "===================================================" << std::endl;
	hideCursor();
	mtx.unlock();
}

void game() {
	int print_x = 7;
	int print_y = 45;
	string answer = "";
	std::thread t1(start_rain_thread);
	window_setting();
	while (true) {
		if (_kbhit()) {
			char input = _getch();
			mtx.lock();
			if (input == 8) {
				if (!answer.empty()) {
					move_cursor(--print_x, print_y);
					std::cout << " " << std::endl;
					answer = answer.substr(0, answer.length() - 1);
				}
			}
			else if (input == 13) {
				for (int i = 0; i < words.size(); i++) {
					if (words[i]->collect(answer)) {
						for (int j = 0; j < words[i]->getWords().size(); j++) {
							move_cursor(words[i]->getX() + j, words[i]->getY() - 4);
							std::cout << " ";
						}
						delete words[i];
						words.erase(words.begin() + i);
						break;
					}
				}
				for (int i = 0; i < answer.size(); i++) {
					move_cursor(--print_x, print_y);
					std::cout << " " << std::endl;
				}
				answer = "";
			}
			else {
				move_cursor(print_x, print_y);
				print_x++;
				std::cout << input << std::endl;
				answer += input;
			}
			mtx.unlock();
		}
	}
	t1.join();
	std::cout << "end" << std::endl;
}

int main() {
	std::string choice;
	std::cout << "===== 옵션 메뉴 =====" << std::endl;
	std::cout << "원하는 옵션 숫자를 공백을 사이에 두고 오름차순으로 입력해주세요" << std::endl;
	std::cout << "1. Alphabet, 2. 숫자, 3. 특수문자" << std::endl;
	std::cout << "ex) 1 2 " << std::endl;
	std::cout << "=====================" << std::endl;
	std::cout << "입력 : ";
	std::getline(std::cin, choice);
	bool first = true;

	for (char c : choice) {
		if (c != ' ') {
			if (first) {
				if (c == '1') {
					checkorigin = 0;
					origin = new alpha();
				}
				else if (c == '2') {
					checkorigin = 1;
					origin = new number();
				}
				else {
					checkorigin = 2;
					origin = new unique_word();
				}
				first = false;
			}
			else {
				if (c == '1') {
					origin->set_word(new alpha());
				}
				else if (c == '2') {
					origin->set_word(new number());
				}
				else {
					origin->set_word(new unique_word());
				}
			}
		}
	}
	game();
}
