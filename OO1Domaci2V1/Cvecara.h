#pragma once
#include <ostream>
#include "Buket.h"

class Cvecara
{
private:
	struct Node;
	using NodePointer = Node*;
	struct Node {
		Buket bouquet;
		NodePointer next = nullptr;
		Node(Buket const& bouquet) :
			bouquet(bouquet) {};
	};
public:
	Cvecara() : bouquets(nullptr) {}
	Cvecara(Cvecara const& rhs) : 
		totalEarned(rhs.totalEarned),
		bouquets(rhs.copyBouquets()) {}
	Cvecara(Cvecara&& rhs) noexcept:
		totalEarned(std::exchange(rhs.totalEarned, 0)),
		bouquets(std::exchange(rhs.bouquets, nullptr)) {};
	bool addBouquet(const Buket&);
	bool sellBouquet(unsigned index);
	friend std::ostream& operator<<(std::ostream& os, Cvecara const& cvecara);
private:
	NodePointer copyBouquets() const;
	void freeBouquets();
	unsigned totalEarned = 1000;
	NodePointer bouquets = nullptr;
};

