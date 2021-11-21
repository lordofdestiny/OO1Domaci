#pragma once
#include <utility>
#include <ostream>
#include "Cvet.h"

class Buket
{
private:
	struct Node {
		Cvet flower;
		Node* next = nullptr;
		Node(const Cvet& flower, int count = 1) :
			flower(flower) {}
	};
	using NodePointer = Node*;
public:
	Buket() = default;
	Buket(Buket const& rhs) :
		flowers(rhs.copyFlowers()) {
		updateCache();
	};
	Buket(Buket&& rhs)  noexcept :
		flowers(std::exchange(rhs.flowers, nullptr)) {
		updateCache();
	}
	~Buket() {
		freeFlowers();
		updateCache();
	}

	Buket& operator=(Buket const&);
	Buket& operator=(Buket&&) noexcept;


	void addFlower(Cvet const&);

	int getBuyPrice() const {
		return buyPriceCache;
	}
	int getSellPrice() const {
		return sellPriceCache;
	}
	int getEarnings() const {
		return earningsCache;
	}

	friend bool operator>(Buket const& left,Buket const& right) {
		return left.getSellPrice() > right.getSellPrice();
	}

	friend std::ostream& operator<<(std::ostream& os, Buket const& bouquet);
private:
	NodePointer copyFlowers() const;
	void freeFlowers();
	void updateCache();
	NodePointer flowers = nullptr;
	/* Cache values to optimize access */
	int buyPriceCache = 0;
	int sellPriceCache = 0;
	int earningsCache = 0;
};

