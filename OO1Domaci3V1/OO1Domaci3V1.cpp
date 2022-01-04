#include <iostream>
#include <string>
#include "List.h"
#include "EMailWithText.h"
#include "Helpers.h"

int main() {
	using ndb::User, ndb::EMailWithText, ndb::EMailState;
	User u1("Steven", "steven.strange@gmail.com");
	User u2("Tony", "tony.start@outlook.com");
	EMailWithText mail(u1, u2, "The Dusting");
	mail.set_text("Hello Tony!");
	std::cout << mail << '\n' << ndb::ssep;
}