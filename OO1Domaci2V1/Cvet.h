#pragma once
#include <string>
#include <utility>
#include <ostream>

class Cvet
{
public:
	Cvet(std::string name, int buyPrice, int sellPrice) :
		name(name),
		buyPrice(buyPrice),
		sellPrice(sellPrice) {}
	Cvet(Cvet const& other) = default;
	Cvet(Cvet&& other) noexcept :
		name(std::move(other.name)),
		buyPrice(std::exchange(other.buyPrice, 0)),
		sellPrice(std::exchange(other.sellPrice, 0)) {}

	Cvet& operator=(Cvet const& rhs);
	Cvet& operator=(Cvet&& rhs) noexcept;

	const std::string& getName() const {
		return name;
	}

	int getBuyPrice() const {
		return buyPrice;
	}

	int getSellPrice() const {
		return sellPrice;
	}

	int getEarnings() const {
		return sellPrice - buyPrice;
	}

	friend bool operator==(Cvet const& left, Cvet const& right) {
		return left.name == right.name;
	}

	friend bool operator!=(Cvet const& left, Cvet const& right) {
		return !(left == right);
	}

	friend std::ostream& operator<<(std::ostream& os, Cvet const& cvet);
private:
	std::string name;
	int buyPrice, sellPrice;
};

