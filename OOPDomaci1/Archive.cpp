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


std::ostream& operator<<(std::ostream& os, const Archive& archive) {
	os << "AHIVA\n";
	Archive::FlightNode* temp = archive.fligtsHead;
	while (temp != nullptr) {
		os << *temp->flight << '\n';
		temp = temp->next;
	}
	return os;
}

void printFlights(Archive::FlightNode* flights) {
	while (flights != nullptr) {
		std::cout << *flights->flight << '\n';
		flights = flights->next;
	}
}

void deleteFlights(Archive::FlightNode* flights) {
	while (flights != nullptr) {
		Archive::FlightNode* keep = flights;
		flights = flights->next;
		delete keep;
	}
}