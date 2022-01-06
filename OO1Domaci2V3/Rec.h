#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include "Skup.h"

class Rec
{
public:
	Rec() = default;
	Rec(const char* str) :
		Rec(std::string(str)) {}
	Rec(std::string str) :
		word(createWord(str)) {}
	Rec(Rec const& w) :
		word(w.word) {}
	Rec(Rec&& w) noexcept :
		word(std::move(w.word)) {}

	Rec& operator=(Rec const&) = default;
	Rec& operator=(Rec&& other) noexcept {
		if (this != &other) {
			word = std::move(other.word);
		}
		return *this;
	}

	int operator+() const {
		return static_cast<int>(word.length());
	}

	int operator~() const {
		return countSyllables();
	}

	int operator()(int n) const {
		return getNthSyllableCarrier(n);
	}

	friend bool operator^(Rec const& first, Rec const& second) {
		return rhymes(first, second);
	}

	friend std::istream& operator>>(std::istream& is, Rec& rec);
	friend std::ostream& operator<<(std::ostream& os, Rec const& rec);
private:
	int countSyllables() const;
	int getNthSyllableCarrier(int) const;
	static bool rhymes(Rec const&, Rec const&);
	static std::string createWord(std::string const&);
	static const inline Skup vocals{ "aeiouAEIOU" };
	static const inline Skup sonants{ "lrnLRN" };
	std::string word;
};