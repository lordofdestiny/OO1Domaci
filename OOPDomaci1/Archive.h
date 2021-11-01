#pragma once

#include "Flight.h"
#include <iostream>

class Archive
{
public:
	struct FlightNode {
		Flight* flight;
		FlightNode* next = nullptr;
	};
private:
	FlightNode* fligtsHead;
	FlightNode* flightsTail;
public:
	Archive() : fligtsHead(nullptr), flightsTail(nullptr) {};
	Archive(const Archive&);
	Archive(Archive&&) = default;
	~Archive();
	
	Archive& addFlight(Flight*);
	FlightNode* getFlightsFrom(std::string);
	FlightNode* getFlightsToo(std::string);
	FlightNode* getFlightsFromTo(std::string, std::string);

	friend std::ostream& operator<<(std::ostream& os, const Archive& archive) {
		os << "AHIVA\n";
		FlightNode* temp = archive.fligtsHead;
		while (temp != nullptr) {
			os << *temp->flight << '\n';
			temp = temp->next;
		}
		return os;
	}

	void print(std::ostream& os = std::cout) {
		os << *this;
	}
};

