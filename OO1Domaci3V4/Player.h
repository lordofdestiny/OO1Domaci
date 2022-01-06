#pragma once
#include <string>
#include <ostream>

namespace ndb {
	class Player {
		std::string _name;
		int _value;
	public:
		Player(std::string const& name, int value = 1050) :
			_name(name), _value(value) {}

		int value() const;
		int increase_value(unsigned int percent);
		int decrease_vaue(unsigned int percent);

		friend bool operator==(Player const& lhs, Player const& rhs);
		friend bool  operator!=(Player const& lhs, Player const& rhs);

		friend std::ostream& operator<<(std::ostream& os, Player const& player);
	};
}

