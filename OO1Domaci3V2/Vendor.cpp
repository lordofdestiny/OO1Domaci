#include "Vendor.h"

namespace ndb {
	void Vendor::expand_catalogue(Item const& item, double margin, short delivery_time) {
		if (margin <= 0) throw EInvalidMargin();
		_catalogue += {item, margin, delivery_time};
	}

	std::string const& Vendor::get_name() const {
		return _name;
	}

	void Vendor::process_shipment(Shipment& shipment) const {
		/* Get reference to shipment details */ 
		auto& shipment_details = get_shipment_details(shipment); 
		/* Find item in catalogue */ 
		auto const& [item, margin, delivery_time] = find_item(shipment.get_item()); 
		/* Update details */
		shipment_details.shipping_time += delivery_time; // 1 Update time
		shipment_details.sprice += item.get_price() * margin; // 2 Update price
	}

	Vendor::CatalogueItem const& Vendor::find_item(Item const& item) const {
		for (std::size_t i = 0; i < _catalogue.size(); i++) {
			if (item == _catalogue[i].item) {
				return _catalogue[i];
			}
		}
		throw EVendorItemMissing();
	}
}