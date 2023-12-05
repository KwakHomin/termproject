#include <iostream>
using namespace std;

class word {
public:
	word* w1 = nullptr;
	word* w2 = nullptr;
	int max_length = 0;
	int x = 0;
	int y = 0;
	string words;

	virtual void makeword() {}
	virtual void set_maxlength(int length) {}
	virtual void set_word(word* what) {};
	virtual string who() { return "nope"; }

	bool collect(string wo) { return true; }
	void setX(int a) { x = a; }
	int getX() { return x; }
	void setY(int a) { y = a; }
	int getY() { return y; }
	
	bool nonew1() { return (w1 == nullptr); }

	bool nonew2() { return (w2 == nullptr); }

	string what_w1() {
		if (nonew1()) return "nope";
		return w1->who();
	}
	string what_w2() {
		if (nonew2()) return "nope";
		return w2->who();
	}
	string getWords() { return words;  }

	word() { }
	word(const word& other) {
		max_length = other.max_length;
		x = other.x;
		y = other.y;
		words = other.words;
	}
};