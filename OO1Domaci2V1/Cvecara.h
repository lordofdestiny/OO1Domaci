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
	using NodePointer = Node*;
public:
	Cvecara() = default;
	Cvecara(Cvecara const& rhs) :
		totalEarned(rhs.totalEarned),
		bouquets(rhs.copyBouquets()) {}
	Cvecara(Cvecara&& rhs) noexcept :
		totalEarned(std::exchange(rhs.totalEarned, 0)),
		bouquets(std::exchange(rhs.bouquets, nullptr)) {};
	~Cvecara() {
		freeBouquets();
	}

	Cvecara& operator=(Cvecara const&);
	Cvecara& operator=(Cvecara&&) noexcept;

	bool addBouquet(Buket const&);
	bool sellBouquet(int index);
	friend std::ostream& operator<<(std::ostream& os, Cvecara const& cvecara);
private:
	NodePointer copyBouquets() const;
	void freeBouquets();
	int totalEarned = 1000;
	NodePointer bouquets = nullptr;
};