#pragma once
#include <ostream>
#include "Buket.h"

class Cvecara
{
private:
	struct Node {
		Buket bouquet;
		Node* next = nullptr;
		Node(Buket const& bouquet) :
			bouquet(bouquet) {};
	};
	using NodePtr = Node*;
public:
	Cvecara() = default;
	Cvecara(Cvecara const& rhs) :
		bouquets(rhs.copyBouquets()),
		totalEarned(rhs.totalEarned) {}
	Cvecara(Cvecara&& rhs) noexcept :
		bouquets(std::exchange(rhs.bouquets, nullptr)),
		totalEarned(std::exchange(rhs.totalEarned, 0)) {};
	~Cvecara() {
		freeBouquets();
	}

	Cvecara& operator=(Cvecara const&);
	Cvecara& operator=(Cvecara&&) noexcept;

	bool addBouquet(Buket const&);
	bool sellBouquet(int index);
	friend std::ostream& operator<<(std::ostream& os, Cvecara const& cvecara);
private:
	NodePtr copyBouquets() const;
	void freeBouquets();
	NodePtr bouquets = nullptr;
	int totalEarned = 1000;
	char c[4]{};
};
