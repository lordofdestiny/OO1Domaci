#include "Skup.h"
#include <utility>

Skup::Skup(std::string const& str) {
	for (auto& c : str) {
		insertChar(c);
	}
}

Skup::Skup(Skup&& other) noexcept :
	data(std::exchange(other.data, nullptr)) {}

Skup::~Skup() {
	deleteAll();
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
	insertChar(c);
	return *this;
}

bool Skup::has(char c) {
	return hasChar(c) != nullptr;
}

bool Skup::operator()(char c) {
	return hasChar(c) != nullptr;
}

Skup::NodePointer Skup::hasChar(char c) {
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

void Skup::deleteAll(){
	NodePointer tmp = data;
	while (tmp != nullptr) {
		delete std::exchange(tmp, tmp->next);
	}
}