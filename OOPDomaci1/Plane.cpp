#include "Plane.h"

Plane& Plane::setPilot(Pilot* const pilot) {
	if (pilot->getFlightTime() >= 100) {
		this->pilot = pilot;
		this->pilot->setFlightStatus(true);
	}
	return *this;
}

Plane& Plane::setCopilot(Pilot* const pilot) {
	this->copilot = pilot;
	this->pilot->setFlightStatus(true);
	return *this;
}