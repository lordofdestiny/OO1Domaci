#pragma once

#include <string>
#include "Plane.h"

class Flight
{
public:
	using id_type = unsigned long long;
private:
	std::string startingPointName;
	std::string destinationPointName;
	unsigned long long id;
	Plane* const plane;
	static id_type idCounter;
public:
	Flight(std::string startName, std::string endName,Plane* const plane):
	startingPointName(startName), destinationPointName(endName),id(idCounter++) ,plane(plane){}

	Flight(const Flight& rhs):startingPointName(rhs.startingPointName), destinationPointName(rhs.destinationPointName),
	id(idCounter++),plane(rhs.plane){}
	
	Flight(Flight&& rhs) = default;

	std::string getStartingPointName() const {
		return startingPointName;
	}

	std::string getDestinationPointName() const {
		return destinationPointName;
	}

	id_type getFlightId() const {
		return id;
	}

	Plane* const getPlane() const {
		return plane;
	}

	friend std::ostream& operator<<(std::ostream& os, const Flight& flight) {
		return os << "LET-" << flight.startingPointName << ":" << flight.destinationPointName;
	}

	void print(std::ostream& os= std::cout) {
		os << *this;
	}
};
