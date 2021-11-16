#include "Buket.h"

Buket::NodePointer Buket::copyFlowers() const{
	NodePointer tmp = flowers;
	NodePointer head = nullptr, tail = nullptr;
	while (tmp != nullptr) {
		NodePointer newNode = new Node(tmp->flower,tmp->count);
		tail = (head == nullptr ? head : tail->next) = newNode;
		tmp = tmp->next;
	}
	return head;
}

void Buket::addFlower(Cvet const& flower) {
	if (flowers == nullptr) {
		NodePointer newNode = new Node(flower);
		flowers = newNode;
	}
	else {
		NodePointer tmp = flowers;
		while (tmp != nullptr && tmp->flower.getName() != flower.getName()) {
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
}

void Buket::freeFlowers() {
	while (flowers != nullptr) {
		delete std::exchange(flowers, flowers->next);
	}
}

unsigned Buket::getBuyPrice() const{
	return getValueAlgorithm(&Cvet::getBuyPrice);
}

unsigned Buket::getSellPrice() const {
	return getValueAlgorithm(&Cvet::getSellPrice);
}

unsigned Buket::getEarnings() const {
	return getValueAlgorithm(&Cvet::getEarnings);
}

unsigned Buket::getValueAlgorithm(PriceGetter priceGetter) const {
	NodePointer tmp = flowers;
	unsigned price = 0;
	while (tmp != nullptr) {
		price += tmp->count * (tmp->flower.*priceGetter)();
		tmp = tmp->next;
	}
	return price;
}

std::ostream& operator<<(std::ostream& os, Buket const& bouquet) {
	Buket::NodePointer tmp = bouquet.flowers;
	os << "(";
	if (tmp != nullptr) {
		os << tmp->flower.getName();
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
		freeFlowers();
		flowers = other.copyFlowers();
	}
	return *this;
}

Buket& Buket::operator=(Buket&& other) noexcept{
	if (this != &other) {
		freeFlowers();
		flowers = std::exchange(other.flowers, nullptr);
	}
	return *this;
}
