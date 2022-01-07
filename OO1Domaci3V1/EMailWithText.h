#pragma once
#include "EMail.h"
#include "Exceptions.h"

namespace ndb {
	class EMailWithText : public EMail {
		std::string _text;
	public:
		EMailWithText(User& sender, User& receiver, std::string const& title) :
			EMail(sender, receiver, title) {}

		void set_text(std::string const& text) {
			if (_state == EMailState::SENT) {
				throw EMailAlreadySent();
			};
			_text = text;
		}

		virtual void send_mail() const override {
			_state = EMailState::SENT;
		}

		virtual EMailWithText* copy() const override {
			return new EMailWithText(*this);
		}
	protected:
		virtual std::ostream& print(std::ostream& os) const override {
			return EMail::print(os) << '\n' << _text;
		}
	};
}

