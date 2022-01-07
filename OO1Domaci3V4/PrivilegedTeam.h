#pragma once
#include "Team.h"

namespace ndb {
	class PrivilegedTeam : public Team {
		int _min_value;
	public:
		PrivilegedTeam(std::string const& name, std::size_t size, int min_value) :
			Team(name, size), _min_value(min_value) { }

		/* Join a player to the position, only if his value is large enough */
		virtual PrivilegedTeam& join_player(Player& player, std::size_t position) override;
	protected:
		virtual std::ostream& print(std::ostream& os) const override;
	};
}
