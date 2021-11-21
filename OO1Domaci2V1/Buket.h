#pragma once
#include <utility>
#include <ostream>
#include "Cvet.h"
class Buket
{
private:
	struct Node {
		Cvet flower;
		int count;
		Node* next = nullptr;
		Node(const Cvet& flower, int count = 1) :
			flower(flower), count(count) {}
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

	double getPercentEarnings() const {
		return earningsCache * 100.0 / buyPriceCache;
	};

	bool operator>(const Buket& other) const {
		return getSellPrice() > other.getSellPrice();
	}

	Buket& operator=(Buket const&);
	Buket& operator=(Buket&&) noexcept;
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

