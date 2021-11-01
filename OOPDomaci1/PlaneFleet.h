#pragma once

#include "Plane.h"

class PlaneFleet
{
public:
	struct PlaneNode {
		Plane* plane;
		PlaneNode* next = nullptr;
	};
private:
	std::string name;
	PlaneNode* planesHead;
	PlaneNode* planesTail;
public:
	PlaneFleet(std::string name) : name(name), planesHead(nullptr), planesTail(nullptr) {}
	PlaneFleet(const PlaneFleet&);
	PlaneFleet(PlaneFleet&&) noexcept;
	~PlaneFleet();

	PlaneFleet& addPlane(Plane* plane);

	/*Removes the first plane with the given name*/
	bool deletePlane(std::string);

	unsigned countPlanes();

	unsigned totalCapacity();

	Plane* getLargestCapacityPlane();

	PlaneNode* getAllInRange(unsigned, unsigned);

	void print();
};

