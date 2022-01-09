#pragma once
#include <string>
#include <ostream>

namespace ndb {
	class Player {
		std::string _name;
		double _value;
	public:
		Player(std::string const& name, long value = 1000) :
			_name(name), _value(value) {}

		double value() const;
		double increase_value(double percent);
		double decrease_vaue(double percent);

		friend bool operator==(Player const& lhs, Player const& rhs);
		friend bool  operator!=(Player const& lhs, Player const& rhs);

		friend std::ostream& operator<<(std::ostream& os, Player const& player);
	};
}

