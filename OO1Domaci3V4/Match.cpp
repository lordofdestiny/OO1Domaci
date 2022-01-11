#include "Match.h"
#include "Exceptions.h"

namespace ndb {
	Match::Match(Match const& other) :
		_teams(other._teams) {}
	Match::Match(Match&& other) noexcept :
		_teams(std::move(other._teams)) { }
	Match& Match::operator=(Match const& rhs) {
		if (this != &rhs) {
			_teams = rhs._teams;
			_p_host = 0;
			_p_guest = 0;
			_outcome = MatchOutcome::UNKNOWN;
		}
		return *this;
	}
	Match& Match::operator=(Match&& rhs) noexcept { 
		if (this != &rhs) {
			_teams = std::move(rhs._teams);
			_p_host = std::exchange(rhs._p_host,0);
			_p_guest = std::exchange(rhs._p_guest,0);
			_outcome = std::exchange(rhs._outcome, MatchOutcome::UNKNOWN);
		}
		return *this;
	}

	void Match::play_match() {
		if (_outcome != MatchOutcome::UNKNOWN) 	return;
		// Get values of both teams
		auto v_host = _teams.get_first()->value();
		auto v_guess = _teams.get_second()->value();

		/* Determine the winner */
		if (v_host < v_guess) {
			_outcome = MatchOutcome::WIN_GUEST;
			_p_host = 0;
			_p_guest = 3;
		}
		else if (v_host > v_guess) {
			_outcome = MatchOutcome::WIN_HOST;
			_p_host = 3;
			_p_guest = 0;
		}
		else {
			_outcome = MatchOutcome::DRAW;
			_p_host = 0;
			_p_guest = 0;
		}

		update_teams_values();
	}

	/* Increase values of the players in the winning team
	 * Decarese values of members of the losing team */
	void Match::update_teams_values() {
		Team* winner = get_winner();
		Team* loser = get_loser();
		if (winner == nullptr || loser == nullptr) return;
		for (std::size_t i = 0; i < winner->capacity(); i++) {
			if ((*winner)[i] != nullptr)
				(*winner)[i]->increase_value(Match::_percent);
		}
		for (std::size_t i = 0; i < loser->capacity(); i++) {
			if ((*loser)[i] != nullptr)
				(*loser)[i]->decrease_vaue(Match::_percent);
		}
	}

	Pair<const int> ndb::Match::get_points() const {
		if (_outcome == MatchOutcome::UNKNOWN) {
			throw EMatchNotPlayed();
		}

		return { &_p_host, &_p_guest };
	}


	bool Match::was_played() const {
		return _outcome != MatchOutcome::UNKNOWN;
	}

	Team* Match::get_winner() {
		switch (_outcome) {
		case MatchOutcome::WIN_HOST:
			return _teams.get_first();
		case MatchOutcome::WIN_GUEST:
			return _teams.get_second();
		default:
			return nullptr;
		}
	}

	Team* ndb::Match::get_loser() {
		auto winner = get_winner();
		if (winner == nullptr) return nullptr;
		if (winner == _teams.get_first()) return _teams.get_second();
		return _teams.get_first();
	}

	std::ostream& operator<<(std::ostream& os, Match const& match) {
		os << match._teams;
		if (match._outcome != MatchOutcome::UNKNOWN) {
			os << " " << match._outcome;
		}

		return os;
	}

	std::ostream& ndb::operator<<(std::ostream& os, MatchOutcome const& outcome) {
		switch (outcome) {
		case MatchOutcome::WIN_HOST:
			return os << "Host won";
		case MatchOutcome::DRAW:
			return os << "Draw";
		case MatchOutcome::WIN_GUEST:
			return os << "Guest won";
		default:
			return os << "Not played";
		}
	}
}
