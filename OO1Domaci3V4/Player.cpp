#include "Player.h"

namespace ndb {
	int Player::value() const {
		return _value;
	}

	int Player::increase_value(unsigned int percent) {
		return _value = _value * (100 + percent) / 100;
	}

	int Player::decrease_vaue(unsigned int percent) {
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