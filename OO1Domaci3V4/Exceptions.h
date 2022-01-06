#pragma once
#include <exception>
#include <stdexcept>

namespace ndb {
	struct ETeamFull : std::runtime_error {
		ETeamFull() :
			std::runtime_error("Cannot add a player into a full team") {}
	};

	struct EInvalidPosition : std::runtime_error {
		EInvalidPosition() :
			std::runtime_error("Player on this position doesn't exist") {}
	};

	struct EPlayerValueTooLow : std::runtime_error {
		EPlayerValueTooLow(int min_value) :
			std::runtime_error(
				("Player value must be larger than " + std::to_string(min_value)).c_str()
			) {}
	};

	struct EMatchNotPlayed : std::runtime_error {
		EMatchNotPlayed() :
			std::runtime_error("Match was not played, points unknown") {}
	};
}