#include <iostream>
#include "List.h"
#include "Item.h"
#include "Shipment.h"
#include "Vendor.h"

int main() {
	using ndb::Item, ndb::Shipment, ndb::Vendor;
	Item item("Kukuruz", 152131043943, 115);
	Vendor vendor("Vendor1");
	vendor.expand_catalogue(item, 25, 6);
	Shipment package(item);
	package += vendor;
	package.calculate_details();
	std::cout << "Price: " << package.get_details().sprice << '\n';
	std::cout << "Delivery time: " << package.get_details().shipping_time << '\n';
}

