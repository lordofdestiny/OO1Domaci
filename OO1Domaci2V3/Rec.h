#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include "Skup.h"

class Rec
{
public:
	Rec(const char* str) :
		Rec(std::string(str)) {}
	Rec(std::string str) :
		word(createWord(str)) {}
	Rec(Rec const& w) :
		word(w.word) {}
	Rec(Rec&& w) noexcept :
		word(std::move(w.word)) {}

	int operator+() const {
		return static_cast<int>(word.length());
	}
	int operator~() const {
		return countSyllables();
	}
	int operator()(int n) const {
		return getNthSyllableCarrier(n);
	}

	bool operator^(Rec const& other) const {
		return rhymes(*this, other);
	}
	char& operator[](int i) {
		return word[i];
	}
	const char& operator[](int i) const {
		return word[i];
	}

	friend std::istream& operator>>(std::istream& is, Rec& rec);
	friend std::ostream& operator<<(std::ostream& os, Rec const& rec);
private:
	int countSyllables() const;
	int getNthSyllableCarrier(int) const;
	static bool rhymes(Rec const&, Rec const&);
	static std::string createWord(std::string const&);
	static const inline Skup vocals{ "aeiou" };
	static const inline Skup sonants{ "lrn" };
	static bool isVocal(char c) {
		return vocals.has(std::tolower(c));
	}
	static bool isSonant(char c) {
		return sonants.has(std::tolower(c));
	}
	std::string word;
};

