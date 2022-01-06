#include "Rec.h"
#include <cmath>

int Rec::countSyllables() const {
	int count = 0;
	for (int i = 0; i < +*this; ++i) {
		bool prevNotVocal = i == 0 || !vocals(word[i - 1]);
		bool nextNotVocal = i == +*this - 1 || !vocals(word[i + 1]);

		if (vocals(word[i]) || (sonants(word[i]) && prevNotVocal && nextNotVocal)) {
			++count;
		}
	}
	return count;
}

int Rec::getNthSyllableCarrier(int n) const {
	int count = 0, result = -1;
	int resultCount = n + 1 + ((n < 0) * ~*this);
	for (int i = 0; i < +*this; ++i) {
		bool prevNotVocal = i == 0 || !vocals(word[i - 1]);
		bool nextNotVocal = i == +*this - 1 || !vocals(word[i + 1]);

		if (vocals(word[i]) || (sonants(word[i]) && prevNotVocal && nextNotVocal)) {
			++count;
		}
		if (count == resultCount) {
			result = i;
			break;
		}
	}
	return result;
}

/* case innsensitive equality check*/
int ciequal(char c1, char c2) {
	return tolower(c1) == tolower(c2);
}

bool Rec::rhymes(Rec const& first, Rec const& second) {
	int firstSyll = (~first == 1 || ~second == 1) ? -1 : -2;
	int i = first(firstSyll), j = second(firstSyll);
	if (i < 0 || j < 0) return false;
	while (i < +first && j < +second &&
		ciequal(first.word[i], second.word[j])) {
		i++; j++;
	}
	return i == +first && j == +second;
}

std::string Rec::createWord(std::string const& str) {
	std::string word;
	for (auto& sep : str) {
		if (std::isalpha(sep)) {
			word += sep;
		}
	}
	return word;
}

std::istream& operator>>(std::istream& is, Rec& rec) {
	std::string word;
	is >> word;
	rec.word = Rec::createWord(word);
	return is;
}

std::ostream& operator<<(std::ostream& os, Rec const& rec) {
	return os << rec.word;
}