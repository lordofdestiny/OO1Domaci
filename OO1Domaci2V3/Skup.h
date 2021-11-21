#pragma once
#include <string>
#include <iostream>
class Skup
{
	struct Node {
		char c;
		Node* next = nullptr;
		Node(char c) : c(c) {};
	};
	using NodePointer = Node*;
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

	Skup& operator+=(char c) {
		insertChar(c);
		return *this;
	}

	bool operator()(char c) const {
		return findChar(c) != nullptr;
	}
private:
	NodePointer findChar(char) const;
	bool insertChar(char);
	void freeChars();

	NodePointer data = nullptr;
};

