#pragma once

#include <iostream>
#include <string>

class Pilot
{
private:
	std::string name;
	double totalFlightHours;
	bool flightStatus;
public:
	Pilot(std::string name, double flightTime, bool isFlying = false)
		: name(name), totalFlightHours(flightTime), flightStatus(isFlying) {}
	Pilot(const Pilot&) = delete;
	Pilot& operator=(const Pilot&) = delete;
	Pilot(Pilot&&) = default;
	Pilot& operator=(Pilot&&) = default;

	std::string getName() const {
		return this->name;
	}

	double getFlightTime() const {
		return totalFlightHours;
	}

	bool isFlying() const {
		return flightStatus;
	}

	Pilot& updateFlightTime(double duration) {
		this->totalFlightHours += duration;
		return *this;
	}

	Pilot& setFlightStatus(bool status) {
		this->flightStatus = status;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Pilot& pilot) {
		return os << pilot.name << '(' << pilot.totalFlightHours << ") - " << (pilot.flightStatus ? 'L' : 'N');
	}

	void print(std::ostream& os = std::cout) {
		os << *this;
	}
};
