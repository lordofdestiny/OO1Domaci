#include "Buket.h"

Buket::NodePointer Buket::copyFlowers() const {
	NodePointer tmp = flowers;
	NodePointer head = nullptr, tail = nullptr;
	while (tmp != nullptr) {
		NodePointer newNode = new Node(tmp->flower);
		tail = (head == nullptr ? head : tail->next) = newNode;
		tmp = tmp->next;
	}
	return head;
}

void Buket::addFlower(Cvet const& flower) {
	NodePointer node = new Node(flower);
	node->next = std::exchange(flowers, node);
	buyPriceCache += node->flower.getBuyPrice();
	sellPriceCache += node->flower.getSellPrice();
	earningsCache += node->flower.getEarnings();
}

void Buket::freeFlowers() {
	while (flowers != nullptr) {
		delete std::exchange(flowers, flowers->next);
	}
	flowers = nullptr;
}

std::ostream& operator<<(std::ostream& os, Buket const& bouquet) {
	Buket::NodePointer tmp = bouquet.flowers;
	os << "(";
	if (tmp != nullptr) {
		os << tmp->flower;
		tmp = tmp->next;
		while (tmp != nullptr) {
			bool print = true;
			Buket::NodePointer tmp2 = bouquet.flowers;
			while (tmp2 != tmp) {
				if (tmp2->flower == tmp->flower) {
					print = false;
					break;
				}
				tmp2 = tmp2->next;
			}
			if (print) {
				os << "," << tmp->flower;
			}
			tmp = tmp->next;
		}
	}
	return os << ")" << bouquet.getSellPrice() << "RSD";
}

Buket& Buket::operator=(Buket const& other) {
	if (this != &other) {
		NodePointer newData = other.copyFlowers();
		freeFlowers();
		flowers = newData;
		buyPriceCache = other.buyPriceCache;
		sellPriceCache = other.sellPriceCache;
		earningsCache = other.earningsCache;
	}
	return *this;
}

Buket& Buket::operator=(Buket&& other) noexcept {
	if (this != &other) {
		freeFlowers();
		flowers = std::exchange(other.flowers, nullptr);
		buyPriceCache = std::exchange(other.buyPriceCache, 0);
		sellPriceCache = std::exchange(other.sellPriceCache, 0);
		earningsCache = std::exchange(other.earningsCache, 0);
	}
	return *this;
}
