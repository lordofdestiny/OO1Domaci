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
	updateCache();
}

void Buket::freeFlowers() {
	while (flowers != nullptr) {
		delete std::exchange(flowers, flowers->next);
	}
	flowers = nullptr;
}

void Buket::updateCache() {
	NodePointer tmp = flowers;
	int buyPrice = 0;
	int sellPrice = 0;
	int earnings = 0;
	while (tmp != nullptr) {
		buyPrice += tmp->flower.getBuyPrice();
		sellPrice += tmp->flower.getSellPrice();
		earnings += tmp->flower.getEarnings();
		tmp = tmp->next;
	}
	this->buyPriceCache = buyPrice;
	this->sellPriceCache = sellPrice;
	this->earningsCache = earnings;
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
		updateCache();
	}
	return *this;
}

Buket& Buket::operator=(Buket&& other) noexcept {
	if (this != &other) {
		freeFlowers();
		flowers = std::exchange(other.flowers, nullptr);
		updateCache();
	}
	return *this;
}
