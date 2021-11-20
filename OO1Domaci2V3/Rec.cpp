#include "Rec.h"
#include <cmath>

int Rec::countSyllables() const {
	int count = 0;
	int len = static_cast<int>(word.length());
	for (int i = 0; i < len; i++) {
		bool prevNotVocal = i > 0 ?
			!isVocal(word[i - 1]) : true;
		bool nextNotVocal = i < len - 1 ?
			!isVocal(word[i + 1]) : true;
		if (isVocal(word[i]) ||
			(isSonant(word[i]) && prevNotVocal && nextNotVocal)) {
			++count;
		}
	}
	return count;
}


int Rec::getNthSyllableCarrier(int n) const {
	int count = 0, result = -1;
	int len = static_cast<int>(word.length());
	int resultCount = n >= 0 ? n : ~*this + n;
	for (int i = 0; i < len; i++) {
		bool prevNotVocal = i > 0 ?
			!vocals.has(word[i - 1]) : true;
		bool nextNotVocal = i < len - 1 ?
			!vocals.has(word[i + 1]) : true;
		if (isVocal(word[i]) ||
			(isSonant(word[i]) && prevNotVocal && nextNotVocal)) {
			++count;
		}
		if (count - 1 == resultCount) {
			result = i;
			break;
		}
	}
	return result;
}


bool Rec::rhymes(Rec const& first, Rec const& second) {
	int x = (~first == 1 || ~second == 1) ? -1 : -2;
	int i1 = first(x), i2 = second(x);
	while (i1 < +first && i2 < +second && first[i1] == second[i2]) {
		i1++;
		i2++;
	}
	return i1 == +first && i2 == +second;
}

std::string Rec::createWord(std::string const& str) {
	/*Replace with string stream*/
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