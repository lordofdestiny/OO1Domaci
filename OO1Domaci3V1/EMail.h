#pragma once
#include <ostream>
#include "User.h"

namespace ndb {
	enum class EMailState { NONE, IN_PREPARATION, SENT, RECEIVED };

	class EMail {
	protected:
		User* _sender, * _receiver;
		std::string _title;
		mutable EMailState _state = EMailState::IN_PREPARATION;
	public:
		EMail(User& sender, User& receiver, std::string const& title) :
			_sender(&sender), _receiver(&receiver), _title(title) {}

		EMail(EMail const& other);
		EMail(EMail&& other) noexcept;

		EMail& operator=(EMail const& rhs);
		EMail& operator=(EMail&& rhs) noexcept;

		virtual ~EMail() = default;

		virtual void send_mail() const = 0;
		virtual EMail* copy() const = 0;

		friend std::ostream& operator<<(std::ostream& os, EMail const& mail) {
			return mail.print(os);
		}
	protected:
		virtual std::ostream& print(std::ostream& os) const;
	};
}

