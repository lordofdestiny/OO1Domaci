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
	struct CityNamePair {
		/*Reference da se izbegne kopiranje, const jer se ne menja nikada og vrednost*/
		const std::string &from, &to;
	};
	/* Funkcija je static jer ne mora pristupati nicemu sto  ima veze sa Arhivom
	*  Metoda filterAlgorithm koristi filterCondition da bi se primenjivao potreban
	*  uslov u zavisnosti koja od one 3 metode je pila pozvana
	*/
	static bool filterCondition(Flight* flight, bool turnFromOn, bool turnToOn, CityNamePair pair) {
		const bool startCondition = flight->getStartingPointName() == pair.from;
		const bool endCondition = flight->getDestinationPointName() == pair.to;
		return (turnFromOn && turnToOn && (startCondition && endCondition))
			|| (turnFromOn && startCondition)
			|| (turnToOn && endCondition);
	}
	FlightNode* filterAlgortihm(bool, bool, CityNamePair);
public:
	Archive() : fligtsHead(nullptr), flightsTail(nullptr) {};
	Archive(const Archive&);
	Archive(Archive&&) = default;
	~Archive();

	Archive& addFlight(Flight*);
	FlightNode* getFlightsFrom(std::string from) {
		/*Ovde mi treba samo uslov za from, tako da je usov za to false,
		* I to eliminise ona druga dva dela izraza
		* Kao drugi argument strukturi prosledujem ""
		* nije bitan rezultat uslova u kome ucestvuje
		*/
		return this->filterAlgortihm(true, false, { from, "" });
	}

	FlightNode* getFlightsToo(std::string to) {
		/*Ovde mi treba samo uslov za to, tako da je usov za from false,
		* I to eliminise ona druga dva dela izraza
		* Kao prvi argument strukturi prosledujem ""
		* nije bitan rezultat uslova u kome ucestvuje
		*/
		return this->filterAlgortihm(false, true, { "", to });
	}

	FlightNode* getFlightsFromTo(std::string from, std::string to) {
		/*
			Ovde oba argumenta true, prosledjujem oba stringa,
			i onda se primeni samo prvi deo uslova
		*/
		return this->filterAlgortihm(true, true, { from, to });
	}

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

