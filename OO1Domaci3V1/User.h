#pragma once
#include <string>
#include <ostream>

namespace ndb {
	class User {
		std::string _name;
		std::string _email;
	public:
		User(std::string const& name, std::string const& email) :
			_name(name), _email(email) {}
		User(User const&) = delete;
		User(User&&)noexcept = default;
		User& operator=(User const&) = delete;
		User& operator=(User&&) noexcept = default;

		friend std::ostream& operator<<(std::ostream& os, User const& user) {
			return os << '(' << user._name << ')' << user._email;
		}
	};
}

