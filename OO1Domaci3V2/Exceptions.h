#pragma once
#include <exception>
#include <stdexcept>

namespace ndb {
	struct EListIndexOutOfRange : std::out_of_range {
		EListIndexOutOfRange() :
			std::out_of_range("List index out of range") {}
	};

	struct EShipmentDetailsNotCalculated : std::runtime_error {
		EShipmentDetailsNotCalculated() :
			std::runtime_error("Shipment details must be calculated"
				"before they are accessible") { }
	};

	struct EShipmentDetailsCalculated : std::runtime_error {
		EShipmentDetailsCalculated()
			: std::runtime_error("Shipment handlers cannot be added"
				"afther the shipment details have been calculated") {}
	};

	struct EVendorItemMissing : std::runtime_error {
		EVendorItemMissing() :
			std::runtime_error("This vendor does not have the requested item!") {}
	};
}