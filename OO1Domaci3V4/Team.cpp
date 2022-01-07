#include <numeric>
#include <utility>
#include "Team.h"
#include "Exceptions.h"

namespace ndb {
	Team::Team(std::string const& name, std::size_t size) :
		_name(name), _size(0), _max_size(size),
		_players(new Player* [_max_size] {}) {}

	Team::Team(Team const& other) {
		copy_from(other);
	};

	Team::Team(Team&& other) noexcept {
		move_from(other);
	};

	Team& Team:: operator=(Team const& rhs) {
		if (this != &rhs) {
			free_data();
			copy_from(rhs);
		}
		return *this;
	};

	Team& Team::operator = (Team&& rhs) noexcept {
		if (this != &rhs) {
			free_data();
			move_from(rhs);
		}
		return *this;
	};

	Team::~Team() {
		free_data();
	}

	Team& Team::join_player(Player& player, std::size_t position) {
		if (_size >= _max_size) throw new ETeamFull();
		if (0 > position || position >= _max_size) {
			throw EInvalidPosition();
		}
		if (_players[position] != nullptr) {
			throw EPositionTaken();
		}
		_players[position] = &player;
		_size += 1;
		return *this;
	}

	Player* Team::operator[](std::size_t position) {
		return const_cast<Player*>(const_cast<Team const&>(*this)[position]);
	}

	Player const* Team::operator[](std::size_t position) const {
		if (0 > position || position >= _max_size) {
			throw EInvalidPosition();
		}
		return _players[position] ;
	}

	int Team::value() const {
		return std::accumulate(_players, _players + _max_size, 0,
			[](int sum, Player const* player) {
				return sum + (player ? player->value() : 0);
			}) / static_cast<int>(_size);
	}

	std::ostream& Team::print(std::ostream& os) const {
		std::size_t cnt = 0;
		os << "[";
		bool print_comma = false;
		for (std::size_t i = 0; i < _max_size; ++i) {
			if (print_comma == true && cnt != _size) {
				os << ", ";
				print_comma = false;
			};
			if (_players[i] != nullptr) {
				cnt += 1;
				os << *_players[i];
				print_comma = true;
			}
		}
		return os << "]";
	}

	void Team::copy_from(Team const& other) {
		if (_players != nullptr) return;
		Player** new_data = new Player * [other._max_size]{};
		_players = new_data;
		_name = other._name;
		_size = other._size;
		_max_size = other._max_size;
		for (std::size_t i = 0; i < _max_size; ++i) {
			_players[i] = other._players[i];
		}
	};

	void Team::move_from(Team& other) noexcept {
		if (_players != nullptr) return;
		_name = std::move(other._name);
		_size = std::exchange(other._size, 0);
		_max_size = std::exchange(other._max_size, 0);
		_players = std::exchange(other._players, nullptr);
	}

	void Team::free_data() {
		delete[] std::exchange(_players, nullptr);
		_size = 0;
		_max_size = 0;
	};

	bool operator==(Team const& lhs, Team const& rhs) {
		if (lhs._name != rhs._name) return false;
		if (lhs._max_size != rhs._max_size) return false;
		if (lhs._size != rhs._size) return false;

		for (std::size_t i = 0; i < lhs._max_size; ++i) {
			if (lhs._players[i] == nullptr && rhs._players[i] == nullptr) {
				continue;
			}
			if (lhs._players[i] != nullptr && rhs._players[i] != nullptr &&
				*lhs._players[i] != *rhs._players[i]) return false;
		}

		return true;
	}

	bool operator!=(Team const& lhs, Team const& rhs) {
		return !(lhs == rhs);
	}

	std::ostream& operator<<(std::ostream& os, Team const& team) {
		os << team._name;
		return team.print(os);
	}
}
