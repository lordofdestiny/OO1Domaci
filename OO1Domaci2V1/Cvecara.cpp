#include "Cvecara.h"

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
}


bool Cvecara::addBouquet(Buket const& bouquet) {
	double percent = 100. * bouquet.getEarnings() / bouquet.getBuyPrice();
	if (!(percent < 20)) {
		Node* newNode = new Node(bouquet);
		newNode->next = std::exchange(this->bouquets, newNode);
		this->totalEarned -= bouquet.getBuyPrice();
	}
	return !(percent < 20);
}

bool Cvecara::sellBouquet(unsigned index) {
	if (index < 0) return false; //Invalid index
	NodePointer prev = nullptr, tmp = bouquets;
	while (index > 0 && tmp != nullptr) {
		prev = std::exchange(tmp, tmp->next);
		index--;
	}
	if (tmp == nullptr) return false; // Invalid index
	NodePointer keep = tmp;
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
