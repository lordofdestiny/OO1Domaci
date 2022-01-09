#include "Player.h"
#include "Exceptions.h"

namespace ndb {
	double Player::value() const {
		return _value;
	}

	double Player::increase_value(double percent) {
		if (percent < 0) throw EInvalidPercentage();
		return _value = _value * (100 + percent) / 100;
	}

	double Player::decrease_vaue(double percent) {
		if (percent < 0) throw EInvalidPercentage();
		return _value = _value * (100 - percent) / 100;
	}

	bool operator==(Player const& lhs, Player const& rhs) {
		return lhs._name == rhs._name && lhs._value == rhs._value;
	}

	bool  operator!=(Player const& lhs, Player const& rhs) {
		return lhs._name != rhs._name || lhs._value != rhs._value;
	}

	std::ostream& operator<<(std::ostream& os, Player const& player) {
		return os << player._name << '#' << player._value;
	}
}