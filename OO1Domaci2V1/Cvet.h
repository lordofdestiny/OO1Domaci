#pragma once
#include <string>
#include <utility>
#include <ostream>

class Cvet
{
public:
	Cvet(std::string name, unsigned buyPrice, unsigned sellPrice);
	Cvet(Cvet const& other) = default;
	Cvet(Cvet&& other) noexcept;
	std::string getName() const {
		return name;
	}
	unsigned getBuyPrice() const {
		return buyPrice;
	}
	unsigned getSellPrice() const {
		return sellPrice;
	}
	unsigned getEarnings() const {
		return sellPrice - buyPrice;
	}
	Cvet& operator=(Cvet const& rhs);
	Cvet& operator=(Cvet&& rhs) noexcept;
	bool operator==(Cvet const& other) const{
		return name == other.name;
	}
	friend std::ostream& operator<<(std::ostream& os, Cvet const& cvet);
private:
	std::string name;
	unsigned buyPrice, sellPrice;
};

