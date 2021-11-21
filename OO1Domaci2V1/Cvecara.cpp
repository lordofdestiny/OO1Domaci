#include "Cvecara.h"

Cvecara& Cvecara::operator=(Cvecara const& other) {
	if (this != &other) {
		NodePointer newBouquets = other.copyBouquets();
		freeBouquets();
		totalEarned = other.totalEarned;
		bouquets = newBouquets;
	}
	return *this;
}

Cvecara& Cvecara::operator=(Cvecara&& other) noexcept {
	if (this != &other) {
		freeBouquets();
		totalEarned = std::exchange(other.totalEarned, 0);
		bouquets = std::exchange(other.bouquets, nullptr);
	}
	return *this;
}

Cvecara::NodePointer Cvecara::copyBouquets() const {
	NodePointer tmp = bouquets;
	NodePointer head = nullptr, tail = nullptr;
	while (tmp != nullptr) {
		NodePointer newNode = new Node(tmp->bouquet);
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

bool Cvecara::addBouquet(Buket const& bouquet) {
	double percent = bouquet.getBuyPrice() * 100.0 / bouquet.getSellPrice();
	if (percent >= 20) {
		Node* newNode = new Node(bouquet);
		newNode->next = std::exchange(this->bouquets, newNode);
		this->totalEarned -= bouquet.getBuyPrice();
	}
	return percent >= 20;
}

bool Cvecara::sellBouquet(int index) {
	if (index < 0) return false; // Index undeflow
	if (bouquets == nullptr) return false; // No bouquets
	NodePointer prev = nullptr, tmp = bouquets;
	while (index > 0 && tmp != nullptr) {
		prev = std::exchange(tmp, tmp->next);
		index--;
	}
	if (tmp == nullptr) return false; // Index overflow
	NodePointer keep = tmp;
	/*  Ovaj warrning ne moze da  se ispuni, prev nikad nece biti nullptr
		Drugi if izlazi iz funkcije ako je bouquets nullptr
		Ako bukets nije bio nullptr bouquet ce napraviti bar jednu iteraciju
		i prev ce se promeniti na vrednost koja nije nullptr
	*/
	prev->next = tmp->next;
	this->totalEarned += keep->bouquet.getSellPrice();
	delete keep;
	return true;
}

std::ostream& operator<<(std::ostream& os, Cvecara const& cvecara) {
	os << "zarada=" << cvecara.totalEarned << "RSD\n";
	Cvecara::NodePointer tmp = cvecara.bouquets;
	while (tmp != nullptr) {
		os << tmp->bouquet << '\n';
		tmp = tmp->next;
	}
	return os;
}
