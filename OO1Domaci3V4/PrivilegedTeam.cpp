#include "PrivilegedTeam.h"
#include "Exceptions.h"

namespace ndb {
	PrivilegedTeam& PrivilegedTeam::join_player(Player& player, std::size_t position) {
		if (player.value() < _min_value) {
			throw EPlayerValueTooLow(_min_value);
		}
		Team::join_player(player, position);

		return *this;
	}

	std::ostream& PrivilegedTeam::print(std::ostream& os) const
	{
		os << "(" << _min_value << ")";
		return Team::print(os);
	}

}