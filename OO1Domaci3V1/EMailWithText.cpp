#include "EMailWithText.h"

namespace ndb {
	void EMailWithText::set_text(std::string const& text) {
		if (_state == EMailState::SENT) {
			throw EMailAlreadySent();
		};
		_text = text;
	}

	void EMailWithText::send_mail() const {
		_state = EMailState::SENT;
	}

	EMailWithText* EMailWithText::copy() const {
		return new EMailWithText(*this);
	}
}