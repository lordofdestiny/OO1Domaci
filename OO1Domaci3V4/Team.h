#pragma once
#include <string>
#include "Player.h"

namespace ndb {
	class Team {
		std::string _name{};
		std::size_t _size{}, _max_size{};
		Player** _players = nullptr;
	public:
		Team(std::string const& name, std::size_t size);
		Team(Team const& other);
		Team(Team&& other) noexcept;
		Team& operator=(Team const& rhs);
		Team& operator=(Team&& rhs) noexcept;
		virtual ~Team();

		/* Add a player to the team to the provided position;
		 * Players pointer is taken and stored */
		virtual Team& join_player(Player& player, std::size_t position);
		/* Return number of player in the team*/
		std::size_t size() const { return _size; }
		/* Return maximum number of players */
		std::size_t capacity() const { return _max_size; }
		/* Access players by position */
		Player* operator[](std::size_t position);
		Player const* operator[](std::size_t position) const;
		/* Calculate the value of the team*/
		int value() const;

		friend bool operator==(Team const& lhs, Team const& rhs);
		friend bool operator!=(Team const& lhs, Team const& rhs);
		friend std::ostream& operator<<(std::ostream& os, Team const& team);
	protected:
		virtual std::ostream& print(std::ostream& os) const;
	private:
		void copy_from(Team const& other);
		void move_from(Team& other) noexcept;
		void free_data();
	};
}
