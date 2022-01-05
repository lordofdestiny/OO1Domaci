#pragma once
#include <string>
#include "Path.h"

namespace ndb {
	class Vehicle {
		std::string _model;
		static inline double _price_per_unit = 0.1;
		static inline double _get_starting_price = 120;
	public:
		Vehicle(std::string const& model_name) :
			_model(model_name) {}
		double get_transport_price(Path const& path) {
			return get_starting_price() + path.get_length() * _price_per_unit;
		}

		friend std::ostream& operator<<(std::ostream& os, Vehicle const& vehicle) {
			return vehicle.print(os);
		}
	protected:
		virtual double get_starting_price() const {
			return _get_starting_price;
		}

		virtual std::ostream& print(std::ostream& os) const {
			return os << _model;
		}
	};
}