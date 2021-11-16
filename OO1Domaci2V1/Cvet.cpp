#include "Cvet.h"

Cvet::Cvet(std::string name, unsigned buyPrice, unsigned sellPrice) :
	name(name),
	buyPrice(buyPrice),
	sellPrice(sellPrice) {}

Cvet::Cvet(Cvet&& other) noexcept :
	name(std::move(other.name)),
	buyPrice(std::exchange(other.buyPrice, 0)),
	sellPrice(std::exchange(other.sellPrice, 0))
{}

Cvet& Cvet::operator=(Cvet const& rhs) {
	if (this != &rhs) {
		name = rhs.name;
		buyPrice = rhs.buyPrice;
		sellPrice = rhs.sellPrice;
	}
	return *this;
}
Cvet& Cvet::operator=(Cvet&& rhs) noexcept {
	if (this != &rhs) {
		name = std::move(name);
		buyPrice = std::exchange(rhs.buyPrice, 0);
		sellPrice = std::exchange(rhs.sellPrice, 0);
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, Cvet const& cvet) {
	return os << cvet.name;
}