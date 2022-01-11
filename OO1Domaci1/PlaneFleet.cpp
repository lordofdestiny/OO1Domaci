#include "PlaneFleet.h"

PlaneFleet::PlaneFleet(const PlaneFleet& rhs) :
	name(rhs.name), planesHead(nullptr), planesTail(nullptr) {
	PlaneNode* temp = rhs.planesHead;
	while (temp != nullptr) {
		PlaneNode* newNode = new PlaneNode{ temp->plane };
		if (this->planesTail == nullptr) {
			this->planesHead = newNode;
		}
		else {
			planesTail->next = newNode;
		}
		planesTail = newNode;
		temp = temp->next;
	}
}

PlaneFleet::PlaneFleet(PlaneFleet&& rhs) noexcept : name(std::move(name)),
planesHead(std::exchange(rhs.planesHead, nullptr)),
planesTail(std::exchange(rhs.planesTail, nullptr)) {}

PlaneFleet::~PlaneFleet() {
	PlaneNode* temp = planesHead;
	while (temp != nullptr) {
		PlaneNode* keep = temp;
		temp = temp->next;
		delete keep;
	}
}

PlaneFleet& PlaneFleet::addPlane(Plane* plane) {
	if (plane != nullptr) {
		PlaneNode* newNode = new PlaneNode{ plane };
		if (this->planesTail == nullptr) {
			this->planesHead = newNode;
		}
		else {
			this->planesTail->next = newNode;
		}
		this->planesTail = newNode;
	}
	return *this;
}

bool PlaneFleet::deletePlane(std::string planeName) {
	PlaneNode* temp = planesHead;
	PlaneNode* prev = nullptr;
	while (temp != nullptr) {
		if (temp->plane->getName() == planeName) {
			//prev <=> prev != nullptr <=> temp == planesHead
			(prev ? prev->next : planesHead) = temp->next;
			if (temp == planesTail) {
				planesTail = prev;
			}
			delete temp;

			return true;
		}
		prev = temp;
		temp = temp->next;
	}
	return false;
}

unsigned PlaneFleet::countPlanes() {
	PlaneNode* temp = this->planesHead;
	unsigned counter = 0;
	while (temp != nullptr) {
		counter++;
		temp = temp->next;
	}
	return counter;
}


unsigned PlaneFleet::totalCapacity() {
	unsigned counter = 0;
	PlaneNode* temp = this->planesHead;
	if (temp != nullptr) {
		while (temp != nullptr) {
			counter += temp->plane->getCapacity();
			temp = temp->next;
		}
	}
	return counter;
}

Plane* PlaneFleet::getLargestCapacityPlane() {
	if (this->planesHead == nullptr) return nullptr;

	PlaneNode* temp = this->planesHead;
	Plane* maxPlane = temp->plane;
	while (temp != nullptr) {
		if (temp->plane->getCapacity() > maxPlane->getCapacity()) {
			maxPlane = temp->plane;
		}
		temp = temp->next;
	}
	return maxPlane;
}

PlaneFleet::PlaneNode* PlaneFleet::getAllInRange(unsigned min, unsigned max) {
	PlaneNode* result = nullptr;
	PlaneNode* tail = nullptr;
	PlaneNode* temp = planesHead;
	while (temp != nullptr) {
		unsigned capacity = temp->plane->getCapacity();
		if (min <= capacity && capacity <= max) {
			PlaneNode* newNode = new PlaneNode{ temp->plane };
			if (tail == nullptr) {
				result = newNode;
			}
			else {
				tail->next = newNode;
			}
			tail = newNode;
		}
		temp = temp->next;
	}
	return result;
}


void PlaneFleet::print() {
	std::cout << "Fleet: " << name << '\n';
	PlaneNode* temp = this->planesHead;
	if (temp == nullptr) {
		std::cout << "Flota je prazna!\n";
	}
	else while (temp != nullptr) {
		std::cout << *temp->plane << "\n";
		temp = temp->next;
	}
}

void printPlanes(PlaneFleet::PlaneNode* planes) {
	while (planes != nullptr) {
		std::cout << *planes->plane << '\n';
		planes = planes->next;
	}
}

void deletePlanes(PlaneFleet::PlaneNode* planes) {
	while (planes != nullptr) {
		PlaneFleet::PlaneNode* keep = planes;
		planes = planes->next;
		delete keep;
	}
}

