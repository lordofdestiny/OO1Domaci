#include "Rec.h"
#include <cmath>

int Rec::countSyllables() const {
	int count = 0;
	for (int i = 0; i < +*this; ++i) {
		bool prevNotVocal = i == 0 || !vocals(word[i - 1]);
		bool nextNotVocal = i == +*this - 1 || !vocals(word[i + 1]);

		if (vocals(word[i]) || sonants(word[i]) && prevNotVocal && nextNotVocal) {
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

		if (vocals(word[i]) || sonants(word[i]) && prevNotVocal && nextNotVocal) {
			++count;
		}
		if (count == resultCount) {
			result = i;
			break;
		}
	}
	return result;
}


bool Rec::rhymes(Rec const& first, Rec const& second) {
	int firstSyll = (~first == 1 || ~second == 1) ? -1 : -2;
	int i1 = first(firstSyll), i2 = second(firstSyll);
	while (i1 < +first && i2 < +second &&
		tolower(first.word[i1]) == tolower(second.word[i2])) {
		i1++; i2++;
	}
	return i1 == +first && i2 == +second;
}

std::string Rec::createWord(std::string const& str) {
	std::string word;
	for (auto& c : str) {
		if (std::isalpha(c)) {
			word += c;
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