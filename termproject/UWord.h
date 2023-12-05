#include "Word.h"
#include <iostream>
#include <random>

class unique_word : public word {
public:
	void makeword() override {
		bool number = false;
		bool alpha = false;
		if (w1 != nullptr) {
			if (w1->who() == "number") { number = true; }
			else if (w1->who() == "alpha") { alpha = true; }
		}

		if (w2 != nullptr) { alpha = true;  }

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(5, max_length);
		int a = dis(gen);
		char character;

		for (int i = 0; i < a; i++) {
			if (number) {
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
				if (number) {
					std::uniform_int_distribution<int> dis(33, 126);
					character = static_cast<char>(dis(gen));
				}
				else {
					std::uniform_int_distribution<int> dis1(33, 47);
					std::uniform_int_distribution<int> dis2(58, 126);
					std::uniform_int_distribution<int> dis3(97, 122);
					int randomselect = std::uniform_int_distribution<int>(0, 1)(gen);
					character = static_cast<char> (randomselect == 0) ? dis1(gen) : dis2(gen);
				}
			}
			else {
				std::uniform_int_distribution<int> dis1(33, 47);
				std::uniform_int_distribution<int> dis2(58, 64);
				int randomselect = std::uniform_int_distribution<int>(0, 1)(gen);
				character = static_cast<char> (randomselect == 0) ? dis1(gen) : dis2(gen);
			}
			words += character;
		}
	}

	void set_maxlength(int length) override { max_length = length; }
	void set_word(word* newword) {
		if (w1 == nullptr) { w1 = newword; }
		else { w2 = newword; }
	}

	string who() override {
		return "unique";
	}

	bool collect(string wo) { return (words == wo); }

	unique_word() { }
	~unique_word() {
		if (w1 != nullptr) { delete w1; }
		if (w2 != nullptr) { delete w2; }
	}

	const word& getw1() const { return *w1; }
	const word& getw2() const { return *w2; }
};