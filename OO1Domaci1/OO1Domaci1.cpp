#include <iostream>
#include "Pilot.h"
#include "Plane.h"
#include  "PlaneFleet.h"
#include "Flight.h"
#include "Archive.h"

int main()
{
	PlaneFleet fleet("Vuciceve delije");

	Pilot pilot1("Branislav", 600);
	Pilot pilot2("Djole", 700);
	Pilot pilot3("Jana", 300);
	Pilot pilot4("Maka", 150);
	Pilot pilot5("Mrvica", 50);
	Pilot pilot6("Andjela", 99);

	Plane plane1("Aribus A380", 853);
	plane1.setPilot(&pilot1).setCopilot(&pilot6);
	Plane plane2("Concorde", 100);
	plane2.setPilot(&pilot2).setCopilot(&pilot3);
	Plane plane3("Boeing 747-400", 524);
	plane3.setPilot(&pilot4).setCopilot(&pilot5);

	fleet.addPlane(&plane1)
		.addPlane(&plane2)
		.addPlane(&plane3);
	fleet.print();

	std::cout << "Avion sa max kapacitetom: " << *fleet.getLargestCapacityPlane() << std::endl;
	std::cout << "Ukupan kapacitet: " << fleet.totalCapacity() << std::endl;
	std::cout << "Broj aviona:" << fleet.countPlanes() << std::endl;

	auto planes = fleet.getAllInRange(100, 600);
	printPlanes(planes);
	deletePlanes(planes);

	Flight flight1("Beograd", "Pariz", &plane1);
	Flight flight2("Pristina", "Abu Dabi", &plane2);

	Archive archive;
	archive.addFlight(&flight1);
	archive.addFlight(&flight2);

	archive.print();
}
