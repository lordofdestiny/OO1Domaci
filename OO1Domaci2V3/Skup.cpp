#include "Skup.h"
#include <utility>

Skup::Skup(std::string const& str) {
	for (auto& c : str) {
		insertChar(c);
	}
}

Skup& Skup::operator=(Skup&& rhs) noexcept {
	if (this != &rhs) {
		data = std::exchange(rhs.data, nullptr);
	}
	return *this;
}

Skup& Skup::add(char c) {
	insertChar(c);
	return *this;
}

Skup& Skup::operator+=(char c) {
	return add(c);
}

bool Skup::has(char c) const {
	return findChar(c) != nullptr;
}

bool Skup::operator()(char c) const {
	return has(c);
}

Skup::NodePointer Skup::findChar(char c) const {
	NodePointer tmp = data;
	while (tmp != nullptr) {
		if (tmp->c == c) {
			break;
		}
		tmp = tmp->next;
	}
	return tmp;
}

bool Skup::insertChar(char c) {
	NodePointer node = new Node(c);
	bool inserted = true;
	if (data == nullptr || data->c > c) {
		node->next = std::exchange(data, node);
	}
	else {
		NodePointer tmp = data;
		while (tmp->next != nullptr && tmp->next->c <= c) {
			tmp = tmp->next;
		}
		if (tmp->c != c) {
			node->next = tmp->next;
			tmp->next = node;
		}
		else {
			inserted = false;
		}
	}
	return true;
}

void Skup::deleteAll() {
	NodePointer tmp = data;
	while (tmp != nullptr) {
		delete std::exchange(tmp, tmp->next);
	}
}