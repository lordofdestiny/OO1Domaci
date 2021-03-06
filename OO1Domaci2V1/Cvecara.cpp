#include "Cvecara.h"
#include <iostream>

Cvecara &Cvecara::operator=(Cvecara const &other) {
	if (this != &other) {
		NodePtr newBouquets = other.copyBouquets();
		freeBouquets();
		totalEarned = other.totalEarned;
		bouquets = newBouquets;
	}
	return *this;
}

Cvecara &Cvecara::operator=(Cvecara &&other) noexcept {
	if (this != &other) {
		freeBouquets();
		totalEarned = std::exchange(other.totalEarned, 0);
		bouquets = std::exchange(other.bouquets, nullptr);
	}
	return *this;
}

Cvecara::NodePtr Cvecara::copyBouquets() const {
	NodePtr tmp = bouquets;
	NodePtr head = nullptr, tail = nullptr;
	while (tmp != nullptr) {
		NodePtr newNode = new Node(tmp->bouquet);
		tail = (head == nullptr ? head : tail->next) = newNode;
		tmp = tmp->next;
	}
	return head;
}

void Cvecara::freeBouquets() {
	while (bouquets != nullptr) {
		delete std::exchange(bouquets, bouquets->next);
	}
	bouquets = nullptr;
}

bool Cvecara::addBouquet(Buket const &bouquet) {
	double percent = bouquet.getEarnings() * 100.0 / bouquet.getSellPrice();
	if (percent < 20) return false;

	NodePtr node = new Node(bouquet);
	this->totalEarned -= bouquet.getBuyPrice();
	if (bouquets == nullptr ||
		bouquets->bouquet.getSellPrice() > node->bouquet.getSellPrice()) {
		node->next = std::exchange(bouquets, node);
	}
	else {
		NodePtr tmp = bouquets;
		while (tmp->next != nullptr &&
			tmp->next->bouquet.getSellPrice() <= node->bouquet.getSellPrice()) {
			tmp = tmp->next;
		}
		node->next = std::exchange(tmp->next, node);
	}

	return true;
}

bool Cvecara::sellBouquet(int index) {
	bool wasDeleted = false;
	if (index >= 0 && bouquets != nullptr) {
		NodePtr prev = nullptr, tmp = bouquets;
		while (tmp != nullptr && index > 0) {
			prev = std::exchange(tmp, tmp->next);
			--index;
		}
		if (tmp != nullptr) {
			this->totalEarned += tmp->bouquet.getSellPrice();
			if (tmp == bouquets) {
				delete std::exchange(bouquets, bouquets->next);
			}
			else {
				prev->next = tmp->next;
				delete tmp;
			}
			wasDeleted = true;
		}
	}
	return wasDeleted;
}

std::ostream &operator<<(std::ostream &os, Cvecara const &cvecara) {
	os << "zarada=" << cvecara.totalEarned << "RSD\n";
	Cvecara::NodePtr tmp = cvecara.bouquets;
	while (tmp != nullptr) {
		os << tmp->bouquet << '\n';
		tmp = tmp->next;
	}
	return os;
}
