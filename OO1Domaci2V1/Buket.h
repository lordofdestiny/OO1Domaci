#pragma once
#include <utility>
#include <ostream>
#include "Cvet.h"

class Buket
{
private:
	struct Node;
	using NodePointer = Node*;
	struct Node {
		Cvet flower;
		unsigned count = 1;
		NodePointer next = nullptr;
		Node(const Cvet& flower, unsigned count = 1) :
			flower(flower), count(count) {}
	};
public:
	Buket() :flowers(nullptr) {}
	Buket(Buket const& rhs) :
		flowers(rhs.copyFlowers()) {};
	Buket(Buket&& rhs)  noexcept :
		flowers(std::exchange(rhs.flowers, nullptr)) {}
	~Buket() {
		freeFlowers();
	}
	void addFlower(Cvet const&);
	unsigned getBuyPrice() const;
	unsigned getSellPrice() const;
	unsigned getEarnings() const;
	bool operator>(const Buket& other) const {
		return getSellPrice() > other.getSellPrice();
	}
	Buket& operator=(Buket const&);
	Buket& operator=(Buket&&) noexcept;
	friend std::ostream& operator<<(std::ostream& os, Buket const& bouquet);
private:
	using PriceGetter = unsigned (Cvet::*)() const;
	unsigned getValueAlgorithm(PriceGetter) const;
	NodePointer copyFlowers() const;
	void freeFlowers();
	NodePointer flowers;
};

