#include "Vendor.h"

namespace ndb {
	void Vendor::process_shipment(Shipment const& shipment) const {
		auto& shipment_details = get_shipment_details(shipment);
		auto const& [item, margin, delivery_time] = find_item(shipment.get_item());
		shipment_details.shipping_time += delivery_time;
		shipment_details.sprice += item.get_price() * (1+margin);
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