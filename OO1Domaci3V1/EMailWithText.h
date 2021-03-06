#ifndef TEXT_MAIL_H
#define TEXT_MAIL_H
#include "EMail.h"
#include "Exceptions.h"

namespace ndb {
	class EMailWithText : public EMail {
		std::string _text;
	public:
		EMailWithText(User& sender, User& receiver, std::string const& title) :
			EMail(sender, receiver, title) {}

		void set_text(std::string const& text);
		/* Check if this getter is allowed/needed */
		std::string const& get_text() const { return _text; }

		virtual void send_mail() const override;

		virtual EMailWithText* copy() const override;
	protected:
		virtual std::ostream& print(std::ostream& os) const override {
			return EMail::print(os) << '\n' << _text;
		}
	};
}

#endif