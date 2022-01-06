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
		auto v_host = _teams.get_first()->value();
		auto v_guess = _teams.get_second()->value();

		if (v_host < v_guess) {
			_outcome = MatchOutcome::WIN_GUESS;
		}
		else if (v_host > v_guess) {
			_outcome = MatchOutcome::WIN_HOST;
		}
		else {
			_outcome = MatchOutcome::DRAW;
		}

		update_teams_values();
	}

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

	Pair<int, int> ndb::Match::get_points() const {
		if (_outcome == MatchOutcome::UNKNOWN) {
			throw EMatchNotPlayed();
		}
		if (_outcome == MatchOutcome::WIN_HOST) {
			return { new int{3},new int{0} };
		}
		else if (_outcome == MatchOutcome::WIN_GUESS) {
			return { new int{0}, new int{3} };
		}
		else { //_outcome == MatchOutcome::DRAW
			return { new int{1}, new int{1} };
		}
	}

	bool Match::was_played() const {
		return _outcome != MatchOutcome::UNKNOWN;
	}

	Team* ndb::Match::get_winner() {
		if (_outcome == MatchOutcome::UNKNOWN
			|| _outcome == MatchOutcome::DRAW) {
			return nullptr;
		}
		if (_outcome == MatchOutcome::WIN_HOST) {
			return _teams.get_first();
		}
		else {
			return _teams.get_second();
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

	std::ostream& operator<<(std::ostream& os, Match::MatchOutcome const& outcome) {
		using Outcome = Match::MatchOutcome;
		if (outcome == Outcome::WIN_HOST) {
			return os << "Host Won";
		}
		else if (outcome == Outcome::DRAW) {
			return os << "Draw";
		}
		else if (outcome == Outcome::WIN_GUESS) {
			return os <<"Guess Won";
		}
		else {
			return os <<"Unknown";
		}
	}
}