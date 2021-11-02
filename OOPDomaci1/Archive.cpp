#include "Archive.h"

Archive::Archive(const Archive& rhs) : fligtsHead(nullptr), flightsTail(nullptr) {
	FlightNode* temp = rhs.fligtsHead;
	while (temp != nullptr) {
		FlightNode* newNode = new FlightNode{ temp->flight };
		if (this->flightsTail == nullptr) {
			this->fligtsHead = newNode;
		}
		else {
			flightsTail->next = newNode;
		}
		flightsTail = newNode;
		temp = temp->next;
	}
}

Archive::~Archive() {
	FlightNode* temp = fligtsHead;
	while (temp != nullptr) {
		FlightNode* keep = temp;
		temp = temp->next;
		delete keep;
	}
}

Archive& Archive::addFlight(Flight* flight) {
	if (flight != nullptr) {
		FlightNode* newNode = new FlightNode{ flight };
		if (this->flightsTail == nullptr) {
			this->fligtsHead = newNode;
		}
		else {
			this->flightsTail->next = newNode;
		}
		this->flightsTail = newNode;
	}
	return *this;
}

Archive::FlightNode* Archive::filterAlgortihm(bool c1, bool c2, CityNamePair pair) {
	FlightNode* result = nullptr;
	FlightNode* tail = nullptr;
	FlightNode* temp = fligtsHead;
	while (temp != nullptr) {
		if ( Archive::filterCondition(temp->flight, c1, c2, pair) ) {
			FlightNode* newNode = new FlightNode{ temp->flight };
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
