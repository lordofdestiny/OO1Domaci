#pragma once
#include "Team.h"
#include "Pair.h"

namespace ndb {
	class Match {
	public:
		enum class MatchOutcome { UNKNOWN, WIN_HOST, DRAW, WIN_GUESS };
		friend std::ostream& operator<<(std::ostream& os, MatchOutcome const& outcome);
	private:
		Pair<Team, Team> _teams;
		MatchOutcome _outcome = MatchOutcome::UNKNOWN;
		static const int _percent = 10;
	public:
		Match(Team* host, Team* guess) :
			_teams(host, guess) {}
		Match(Match const& other);
		Match(Match&& other) noexcept;
		Match& operator=(Match const& rhs);
		Match& operator=(Match && rhs) noexcept;

		Pair<Team, Team>& get_teams() {
			return _teams;
		}

		Pair<Team, Team> const& get_teams() const {
			return _teams;
		}

		void play_match();
		bool was_played() const;
		Pair<int,int> get_points() const;
		friend std::ostream& operator<<(std::ostream& os, Match const& match);
	private:
		void update_teams_values();
		Team* get_winner();
		Team* get_loser();
	};
}

