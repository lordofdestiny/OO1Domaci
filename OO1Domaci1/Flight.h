#pragma once

#include <string>
#include <utility>
#include "Plane.h"

class Flight
{
public:
	using id_type = unsigned long long;
private:
	std::string startingPointName;
	std::string destinationPointName;
	id_type id;
	Plane* plane;
	static inline id_type idCounter = 0;
public:
	Flight(std::string startName, std::string endName, Plane* const plane) :
		startingPointName(startName),
		destinationPointName(endName),
		id(idCounter++), plane(plane) {}

	Flight(const Flight& rhs) :
		startingPointName(rhs.startingPointName),
		destinationPointName(rhs.destinationPointName),
		id(idCounter++), plane(rhs.plane) {}

	Flight(Flight&& rhs) noexcept :
		startingPointName(std::move(rhs.startingPointName)),
		destinationPointName(std::move(rhs.destinationPointName)),
		id(std::exchange(rhs.id, 0)), plane(std::exchange(rhs.plane, nullptr)) {}

	const std::string& getStartingPointName() const {
		return startingPointName;
	}

	const std::string& getDestinationPointName() const {
		return destinationPointName;
	}

	id_type getFlightId() const {
		return id;
	}

	Plane const* getPlane() const {

		return plane;
	}

	friend std::ostream& operator<<(std::ostream& os, const Flight& flight) {
		return os << "LET-" << flight.startingPointName << ":" << flight.destinationPointName;
	}

	void print(std::ostream& os = std::cout) {
		os << *this;
	}
};
