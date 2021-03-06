#ifndef SHIPMENT_H
#define SHIPMENT_H

#include <utility>
#include "Item.h"
#include "List.h"

namespace ndb {
	class ShipmentHandler;
	class Shipment {
	public:
		struct ShipmentDetails {
			double sprice = 0;
			unsigned shipping_time = 0;
		};
		friend class ShipmentHandler;
		using t_id = unsigned long long;
	private:
		static inline t_id _next_id = 0;
		t_id _id = _next_id++;
		Item _item;
		bool _details_calculated = false;
		ShipmentDetails _details{};
		List<ShipmentHandler*> _handlers{};
	public:
		Shipment(Item const& item) : _item(item) {}

		Shipment(Shipment const& other);
		Shipment(Shipment&& other) noexcept;

		Shipment& operator=(Shipment const& rhs);
		Shipment& operator=(Shipment&& rhs) noexcept;

		Shipment& operator+=(ShipmentHandler& handler);

		void calculate_details();

		/*Ask about first two getters*/
		t_id get_id() const { return _id; }
		Item const& get_item() const { return _item; }
		ShipmentDetails const& get_details() const;

		friend std::ostream& operator<<(std::ostream& os, Shipment const& shimpemnt);
	};
}

#endif