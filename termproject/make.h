#include "Word.h"
#include "Number.h"
#include "UWord.h"
#include <iostream>
#include <random>
using namespace std;

class alpha : public word {
public:
	void makeword() override {
		bool unique = false;
		bool number = false;
		if (!nonew1()) {
			if (what_w1() == "unique") { unique = true; }
			else if (what_w1() == "number") { number = true; }
		}

		if (!nonew2()) { unique = true; }

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(3, max_length);
		int a = dis(gen);
		char character;

		for (int i = 0; i < a; i++) {
			if (unique) {
				if (number) {
					std::uniform_int_distribution<int> dis(33, 126);
					character = static_cast<char>(dis(gen));
				}
				else {
					std::uniform_int_distribution<int> dis1(33, 47);
					std::uniform_int_distribution<int> dis2(58, 126);
					int randomselect = std::uniform_int_distribution<int>(0, 1)(gen);
					character = static_cast<char> (randomselect == 0) ? dis1(gen) : dis2(gen);
				}
			}
			else if (number) {
				if (unique) {
					std::uniform_int_distribution<int> dis(33, 126);
					character = static_cast<char>(dis(gen));
				}
				else {
					std::uniform_int_distribution<int> dis1(48, 57);
					std::uniform_int_distribution<int> dis2(65, 90);
					std::uniform_int_distribution<int> dis3(97, 122);
					int randomselect = std::uniform_int_distribution<int>(0, 2)(gen);
					character = static_cast<char> (randomselect > 0) ? ((randomselect == 1) ? dis1(gen) : dis3(gen)) : dis2(gen);
				}
			}
			else {
				std::uniform_int_distribution<int> dis1(65, 90);
				std::uniform_int_distribution<int> dis2(97, 122);
				int randomselect = std::uniform_int_distribution<int>(0, 1)(gen);
				character = static_cast<char> (randomselect == 0) ? dis1(gen) : dis2(gen);
			}
			words += character;
		}
	}

	void set_maxlength(int length) override { max_length = length; }
	bool collect(string wo) { return (words == wo); }
	void set_word(word* newword) {
		if (w1 == nullptr) { w1 = newword; }
		else { w2 = newword; }
	}

	string who() override { return "alpha"; }

	alpha() { }
	~alpha() {
		delete w1;
		delete w2;
	}
	word getw1() const { return *w1; }

	word getw2() const { return *w2; }
};