#pragma once
#include <utility>
#include "Plane.h"
class PlaneList
{
private:
	struct Node {
		Plane* plane;
		Node* next = nullptr;
	};
	Node* head, * tail;
public:
	PlaneList() = default;
	PlaneList(const PlaneList& rhs) : head(nullptr), tail(nullptr) {
		Node* temp = rhs.head;
		while (temp != nullptr) {
			Node* newNode = new Node{ temp->plane };
			if (this->tail == nullptr) {
				this->head = newNode;
			}
			else {
				tail->next = newNode;
			}
			tail = newNode;
			temp = temp->next;
		}
	}
	~PlaneList() {
		Node* temp = head;
		while (temp != nullptr) {
			Node* keep = temp;
			temp = temp->next;
			delete keep;
		}
	}

	PlaneList(PlaneList&& rhs) noexcept: 
		head(std::exchange(rhs.head,nullptr)), tail(std::exchange(rhs.tail,nullptr)){}

	PlaneList& addPlane(Plane* plane) {
		if (plane != nullptr) {
			Node* newNode = new Node{ plane };
			if (this->tail == nullptr) {
				this->head = newNode;
			}
			else {
				this->tail->next = newNode;
			}
			this->tail = newNode;
		}
		return *this;
	}

	bool deletePlane(std::string planeName) {
		Node* temp = head;
		Node* prev = nullptr;
		while (temp != nullptr) {
			if (temp->plane->getName() == planeName) {
				//prev <=> prev != nullptr <=> temp == planesHead
				(prev ? prev->next : head) = temp->next;
				if (temp == tail) {
					tail = prev;
				}
				delete temp;

				return true;
			}
			prev = temp;
			temp = temp->next;
		}
		return false;
	}

	unsigned count() {
		Node* temp = this->head;
		unsigned counter = 0;
		while (temp != nullptr) {
			counter++;
			temp = temp->next;
		}
		return counter;
	}

};

