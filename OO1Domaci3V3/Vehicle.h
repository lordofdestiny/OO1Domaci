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
		double get_transport_price(Path const& path);
		friend std::ostream& operator<<(std::ostream& os, Vehicle const& vehicle);
	protected:
		virtual double get_starting_price() const;

		virtual std::ostream& print(std::ostream& os) const;
	};
}