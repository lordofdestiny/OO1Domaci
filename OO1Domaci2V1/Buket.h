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
		Node(const Cvet& flower) :
			flower(flower) {}
	};
	using NodePtr = Node*;
public:
	Buket() = default;
	Buket(Buket const& rhs) :
		flowers(rhs.copyFlowers()),
		buyPriceCache(rhs.buyPriceCache),
		sellPriceCache(rhs.sellPriceCache),
		earningsCache(rhs.earningsCache) {};
	Buket(Buket&& rhs) noexcept :
		flowers(std::exchange(rhs.flowers, nullptr)),
		buyPriceCache(std::exchange(rhs.buyPriceCache, 0)),
		sellPriceCache(std::exchange(rhs.sellPriceCache, 0)),
		earningsCache(std::exchange(rhs.earningsCache, 0)) {}
	~Buket() {
		freeFlowers();
		buyPriceCache = 0;
		sellPriceCache = 0;
		earningsCache = 0;
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

	friend bool operator>(Buket const& left, Buket const& right) {
		return left.getSellPrice() > right.getSellPrice();
	}

	friend std::ostream& operator<<(std::ostream& os, Buket const& bouquet);
private:
	NodePtr copyFlowers() const;
	void freeFlowers();
	NodePtr flowers = nullptr;
	/* Cache values to optimize access */
	int buyPriceCache = 0;
	int sellPriceCache = 0;
	int earningsCache = 0;
};

