#pragma once
#include <string>

namespace ndb {
	class Item {
	protected:
		std::string _name;
		unsigned long long _barcode;
		double _pprice;
	public:
		Item(std::string name, unsigned long long barcode, double price) :
			_name(name), _barcode(barcode), _pprice(price) {}

		std::string const& get_name() const {
			return _name;
		}

		unsigned long long get_barcode() const {
			return _barcode;
		}

		double get_price() const {
			return _pprice;
		}

		friend bool operator==(Item const& lhs, Item const& rhs) {
			return lhs._barcode == rhs._barcode;
		}

		friend bool operator!=(Item const& lhs, Item const& rhs) {
			return lhs._barcode != rhs._barcode;
		}
	};
}

