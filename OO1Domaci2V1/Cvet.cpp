#include "Cvet.h"

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
		name = std::move(rhs.name);
		buyPrice = std::exchange(rhs.buyPrice, 0);
		sellPrice = std::exchange(rhs.sellPrice, 0);
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, Cvet const& cvet) {
	return os << cvet.name;
}
