#pragma once

#include "Plane.h"

class PlaneLinkedList
{
	struct PlaneNode {
		Plane* data;
		PlaneNode* next;
	};
	PlaneNode* head;

	PlaneLinkedList(): head(nullptr) {
	}

	void insertBack(Plane* plane) {
		PlaneNode* newNode = new PlaneNode{ plane,nullptr };
		if (this->head == nullptr) {
			this->head = newNode;
		}
		else {
			this->head->next = newNode;
		}
	}
};

