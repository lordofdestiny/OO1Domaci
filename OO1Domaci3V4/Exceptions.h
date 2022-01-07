#pragma once
#include <exception>
#include <stdexcept>

namespace ndb {
	struct ETeamFull : std::runtime_error {
		ETeamFull() :
			runtime_error("Cannot add a player into a full team") {}
	};

	struct EInvalidPosition : std::runtime_error {
		EInvalidPosition() :
			runtime_error("Player on this position doesn't exist") {}
	};

	struct EPositionTaken : std::runtime_error {
		EPositionTaken() :
			runtime_error("Required position is taken by another player") {}
	};

	struct EPlayerValueTooLow : std::runtime_error {
		static inline std::string(* const str)(int) = std::to_string;
		EPlayerValueTooLow(int min) :
			runtime_error(("Player value must be larger than " +
				str(min)).c_str()) {}
	};

	struct EMatchNotPlayed : std::runtime_error {
		EMatchNotPlayed() :
			runtime_error("Match was not played, points unknown") {}
	};
}