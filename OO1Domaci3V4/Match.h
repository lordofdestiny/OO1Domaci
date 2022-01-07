#pragma once
#include "Team.h"
#include "Pair.h"

namespace ndb {
	class Match {
	public:
		/** Desribes the result of the match
		* UNKNOWN - not played yet
		* WIN_HOST
		* DRAW
		* WIN_GUEST */
		enum class MatchOutcome { UNKNOWN, WIN_HOST, DRAW, WIN_GUEST };
		friend std::ostream& operator<<(std::ostream& os, MatchOutcome const& outcome);
	private:
		Pair<Team> _teams;
		MatchOutcome _outcome = MatchOutcome::UNKNOWN;
		static const int _percent = 10;
	public:
		Match(Team* host, Team* guess) :
			_teams(host, guess) {}
		Match(Match const& other);
		Match(Match&& other) noexcept;

		Match& operator=(Match const& rhs);
		Match& operator=(Match&& rhs) noexcept;

		/* Return pair of pointers to teams that are playing the match */
		Pair<Team>& get_teams() { return _teams; }
		Pair<Team> const& get_teams() const { return _teams; }

		/* Determin the winner based on team values
		 * Updates player's values */
		void play_match();
		/* Check whether the match was played or not */
		bool was_played() const;
		/* Caller is required to delete content of the pair*/
		Pair<int> get_points() const;

		friend std::ostream& operator<<(std::ostream& os, Match const& match);
	private:
		void update_teams_values();
		Team* get_winner();
		Team* get_loser();
	};
}

