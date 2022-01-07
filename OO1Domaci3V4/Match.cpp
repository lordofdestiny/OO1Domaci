#include "Match.h"
#include "Exceptions.h"

namespace ndb {
	Match::Match(Match const& other) :
		_teams(other._teams) {}
	Match::Match(Match&& other) noexcept :
		_teams(std::move(other._teams)) { }
	Match& Match::operator=(Match const& rhs) { return *this; }
	Match& Match::operator=(Match&& rhs) noexcept { return *this; }

	void Match::play_match() {
		if (_outcome != MatchOutcome::UNKNOWN) 	return;
		// Get values of both teams
		auto v_host = _teams.get_first()->value();
		auto v_guess = _teams.get_second()->value();

		/* Determine the winner */
		if (v_host < v_guess) {
			_outcome = MatchOutcome::WIN_GUEST;
		}
		else if (v_host > v_guess) {
			_outcome = MatchOutcome::WIN_HOST;
		}
		else {
			_outcome = MatchOutcome::DRAW;
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

	Pair<int> ndb::Match::get_points() const {
		using Outcome = Match::MatchOutcome;
		switch (_outcome) {
		case Outcome::WIN_HOST:
			return { new int{3},new int{0} };
		case Outcome::DRAW:
			return { new int{3},new int{0} };
		case Outcome::WIN_GUEST:
			return { new int{3},new int{0} };
		default:
			throw EMatchNotPlayed();
		}
	}

	bool Match::was_played() const {
		return _outcome != MatchOutcome::UNKNOWN;
	}

	Team* Match::get_winner() {
		using Outcome = Match::MatchOutcome;
		switch (_outcome) {
		case Outcome::WIN_HOST:
			return _teams.get_first();
		case Outcome::WIN_GUEST:
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
		if (match._outcome != Match::MatchOutcome::UNKNOWN) {
			os << " " << match._outcome;
		}

		return os;
	}

	std::ostream& ndb::operator<<(std::ostream& os, Match::MatchOutcome const& outcome) {
		using Outcome = Match::MatchOutcome;
		switch (outcome) {
		case Outcome::WIN_HOST:
			return os << "Host won";
		case Outcome::DRAW:
			return os << "Draw";
		case Outcome::WIN_GUEST:
			return os << "Guest won";
		default:
			return os << "Not played";
		}
	}
}
