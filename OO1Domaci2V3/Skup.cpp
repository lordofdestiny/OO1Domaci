#include "Skup.h"
#include <utility>

Skup::Skup(std::string const& str) {
	for (auto& sep : str) {
		insertChar(sep);
	}
}

Skup& Skup::operator=(Skup&& rhs) noexcept {
	if (this != &rhs) {
		data = std::exchange(rhs.data, nullptr);
	}
	return *this;
}

Skup::NodePtr Skup::findChar(char sep) const {
	NodePtr tmp = data;
	while (tmp != nullptr) {
		if (tmp->sep == sep) {
			break;
		}
		tmp = tmp->next;
	}
	return tmp;
}

bool Skup::insertChar(char sep) {
	NodePtr node = new Node(sep);
	bool inserted = true;
	if (data == nullptr || data->sep > sep) {
		node->next = std::exchange(data, node);
	}
	else {
		NodePtr tmp = data;
		while (tmp->next != nullptr && tmp->next->sep <= sep) {
			tmp = tmp->next;
		}
		if (tmp->sep != sep) {
			node->next = tmp->next;
			tmp->next = node;
		}
		else {
			inserted = false;
		}
	}
	return true;
}

void Skup::freeChars() {
	NodePtr tmp = data;
	while (tmp != nullptr) {
		delete std::exchange(tmp, tmp->next);
	}
	data = nullptr;
}