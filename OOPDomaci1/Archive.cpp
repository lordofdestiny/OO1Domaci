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

Archive::FlightNode* Archive::getFlightsFrom(std::string from) {
	FlightNode* result = nullptr;
	FlightNode* tail = nullptr;
	FlightNode* temp = fligtsHead;
	while (temp != nullptr) {
		if (temp->flight->getStartingPointName() == from) {
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

Archive::FlightNode* Archive::getFlightsToo(std::string to) {
	FlightNode* result = nullptr;
	FlightNode* tail = nullptr;
	FlightNode* temp = fligtsHead;
	while (temp != nullptr) {
		if (temp->flight->getDestinationPointName() == to) {
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

Archive::FlightNode* Archive::getFlightsFromTo(std::string from, std::string to) {
	FlightNode* result = nullptr;
	FlightNode* tail = nullptr;
	FlightNode* temp = fligtsHead;
	while (temp != nullptr) {
		if (temp->flight->getStartingPointName() == from && 
			temp->flight->getDestinationPointName() == to) {
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