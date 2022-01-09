#ifndef EMAIL_H
#define EMAIL_H

#include <ostream>
#include "User.h"

namespace ndb {
	enum class EMailState { NONE, PREPARING, SENT, RECEIVED };

	class EMail {
	protected:
		User* _sender, * _receiver;
		std::string _title;
		mutable EMailState _state = EMailState::PREPARING;
	public:
		EMail(User& sender, User& receiver, std::string const& title) :
			_sender(&sender), _receiver(&receiver), _title(title) {}

		EMail(EMail const& other);
		EMail(EMail&& other) noexcept;

		EMail& operator=(EMail const& rhs);
		EMail& operator=(EMail&& rhs) noexcept;

		virtual ~EMail() = default;

		User const& get_sender() const { return *_sender; }
		User const& get_receiver() const { return *_receiver; }
		std::string const& get_title() const { return _title; }
		EMailState get_state() const { return _state; }

		virtual void send_mail() const = 0;
		virtual EMail* copy() const = 0;

		friend std::ostream& operator<<(std::ostream& os, EMail const& mail) {
			return mail.print(os);
		}
	protected:
		virtual std::ostream& print(std::ostream& os) const;
	};
}

#endif