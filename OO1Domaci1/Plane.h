#pragma once

#include <string>
#include "Pilot.h"

class Plane
{
private:
	std::string name;
	unsigned capacity;
	Pilot* pilot, * copilot;
public:
	Plane(std::string name, unsigned passengers)
		: name(name), capacity(passengers),
		pilot(nullptr), copilot(nullptr) {}

	Plane(const Plane&) = delete;
	Plane& operator=(const Plane&) = delete;
	Plane(Plane&&) = default;
	Plane& operator=(Plane&&) = default;

	Plane& setPilot(Pilot* const pilot);
	Plane& setCopilot(Pilot* const pilot);

	const std::string& getName() const {
		return name;
	}

	Pilot* getPilot() const {
		return pilot;
	}

	Pilot* getCopilot() const {
		return pilot;
	}

	unsigned getCapacity() const {
		return capacity;
	}

	friend std::ostream& operator<<(std::ostream& os, const Plane& plane) {
		return os << "AVION:" << plane.name << " - " << plane.capacity;
	}

	void print(std::ostream& os = std::cout) {
		os << *this;
	}
};

