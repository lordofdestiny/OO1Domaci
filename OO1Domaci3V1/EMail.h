#pragma once
#include <ostream>
#include "User.h";

namespace ndb {
	enum class EMailState { IN_PREPARATION, SENT, RECEIVED };

	class EMail {
	protected:
		User* _sender, * _receiver;
		mutable EMailState _state;
		std::string _title;
	public:
		EMail(User& sender, User& receiver, std::string const& title) :
			_sender(&sender), _receiver(&receiver),
			_title(title), _state(EMailState::IN_PREPARATION) {}

		EMail(EMail const&) = default;
		EMail(EMail&&) = default;

		EMail& operator=(EMail const&) = default;
		EMail& operator=(EMail&&) = default;

		virtual ~EMail() = default;

		virtual void send_mail() const = 0;
		virtual EMail* copy() const = 0;

		friend std::ostream& operator<<(std::ostream& os, EMail const& mail) {
			return mail.print(os);
		}
	protected:
		virtual std::ostream& print(std::ostream& os) const {
			return os << _title << '\n' << *_sender << '\n' << *_receiver;
		}
	};
}

