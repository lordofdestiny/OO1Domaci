#pragma once
#include <string>
#include <iostream>
class Skup
{
	struct Node {
		char sep;
		Node* next = nullptr;
		Node(char sep) : sep(sep) {};
	};
	using NodePtr = Node*;
public:
	Skup() = default;
	Skup(std::string const&);
	Skup(Skup const&) = delete;
	Skup(Skup&& other) noexcept :
		data(std::exchange(other.data, nullptr)) {}
	~Skup() {
		freeChars();
	}
	Skup& operator=(Skup const&) = delete;
	Skup& operator=(Skup&&) noexcept;

	Skup& operator+=(char sep) {
		insertChar(sep);
		return *this;
	}

	bool operator()(char sep) const {
		return findChar(sep) != nullptr;
	}
private:
	NodePtr findChar(char) const;
	bool insertChar(char);
	void freeChars();

	NodePtr data = nullptr;
};

