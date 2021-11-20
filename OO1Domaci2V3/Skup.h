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
	Skup(Skup&&) noexcept;
	~Skup();
	Skup& operator=(Skup const&) = delete;
	Skup& operator=(Skup&&) noexcept;

	Skup& add(char);
	Skup& operator+=(char);

	bool has(char) const;
	bool operator()(char) const;
private:
	NodePointer hasChar(char) const;
	bool insertChar(char);
	void deleteAll();

	NodePointer data = nullptr;
};

