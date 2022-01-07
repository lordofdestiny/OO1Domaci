#include "EMail.h"

namespace ndb{
	EMail::EMail(EMail const& other) :
		_sender(other._sender),
		_receiver(other._receiver),
		_title(other._title) {}

	EMail::EMail(EMail&& other) noexcept :
		_sender(std::exchange(other._sender, nullptr)),
		_receiver(std::exchange(other._receiver, nullptr)),
		_title(std::move(other._title)),
		_state(std::exchange(other._state, EMailState::NONE)) {}

	EMail& EMail::operator=(EMail const& rhs) {
		if (this != &rhs) {
			_sender = rhs._sender;
			_receiver = rhs._receiver;
			_title = rhs._title;
			_state = EMailState::PREPARING;
		}
		return *this;
	};

	EMail& EMail::operator=(EMail&& rhs) noexcept {
		if (this != &rhs) {
			_sender = std::exchange(rhs._sender, nullptr);
			_receiver = std::exchange(rhs._receiver, nullptr);
			_title = std::move(rhs._title);
			_state = std::exchange(rhs._state, EMailState::NONE);
		}
		return *this;
	};

	std::ostream& EMail::print(std::ostream& os) const {
		return os << _title << '\n';
		if (_sender == nullptr) os << "none";
		else os << *_sender << '\n';
		if (_receiver == nullptr) os << "none";
		else os << *_receiver;
		return os;
	}
}