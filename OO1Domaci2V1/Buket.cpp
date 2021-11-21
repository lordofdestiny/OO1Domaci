#include "Buket.h"

Buket::NodePointer Buket::copyFlowers() const {
	NodePointer tmp = flowers;
	NodePointer head = nullptr, tail = nullptr;
	while (tmp != nullptr) {
		NodePointer newNode = new Node(tmp->flower, tmp->count);
		tail = (head == nullptr ? head : tail->next) = newNode;
		tmp = tmp->next;
	}
	return head;
}

void Buket::addFlower(Cvet const& flower) {
	if (flowers == nullptr) {
		flowers = new Node(flower);
	}
	else {
		NodePointer tmp = flowers;
		while (tmp != nullptr && tmp->flower != flower) {
			tmp = tmp->next;
		}
		if (tmp == nullptr) {
			NodePointer newNode = new Node(flower);
			newNode->next = std::exchange(flowers, newNode);
		}
		else {
			tmp->count += 1;
		}
	}
	updateCache();
}

void Buket::freeFlowers() {
	while (flowers != nullptr) {
		delete std::exchange(flowers, flowers->next);
	}
}

void Buket::updateCache() {
	NodePointer tmp = flowers;
	int buyPrice = 0;
	int sellPrice = 0;
	int earnings = 0;
	while (tmp != nullptr) {
		buyPrice += tmp->count * tmp->flower.getBuyPrice();
		sellPrice += tmp->count * tmp->flower.getSellPrice();
		earnings += tmp->count * tmp->flower.getEarnings();
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
			os << "," << tmp->flower;
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
