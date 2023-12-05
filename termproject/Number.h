#include "Word.h"
#include "UWord.h"
#include <iostream>
#include <random>

class number : public word {
public:
	void makeword() override {
		bool unique = false;
		bool alpha = false;
		if (w1 != nullptr) {
			if (w1->who() == "unique") { unique = true; }
			else if (w1->who() == "alpha") { alpha = true; }
		}

		if (w2 != nullptr) { unique = true;	}

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(5, max_length);
		int a = dis(gen);
		char character;

		for (int i = 0; i < a; i++) {
			if (unique) {
				if (alpha) {
					std::uniform_int_distribution<int> dis(33, 126);
					character = static_cast<char>(dis(gen));
				}
				else {
					std::uniform_int_distribution<int> dis1(33, 64);
					std::uniform_int_distribution<int> dis2(91, 96);
					int randomselect = std::uniform_int_distribution<int>(0, 1)(gen);
					character = static_cast<char> (randomselect == 0) ? dis1(gen) : dis2(gen);
				}
			}
			else if (alpha) {
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
				std::uniform_int_distribution<int> dis(48, 57);
				character = static_cast<char>(dis(gen));
			}
			words += character;
		}
	}

	void set_maxlength(int length) override { max_length = length; }

	void set_word(word* newword) override {
		if (w1 == nullptr) {
			w1 = newword;
		}
		else {
			w2 = newword;
		}
	}

	string who() override { return "number"; }

	bool collect(string wo) { return (words == wo); }

	number() {}
	~number() {
		delete w1;
		delete w2;
	}

	word getw1() const { return *w1; }
	word getw2() const { return *w2; }
};