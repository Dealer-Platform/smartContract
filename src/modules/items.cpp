
/**
 * Allows the user to update the price for the threat intelligence data.
 * Nothing special to expect.
 */
ACTION reporting::updateprice(name reporter, uint64_t itemKey, uint64_t price) {
  require_auth( reporter );
	user_t users( _self, _self.value );
	auto it_reporter = users.find(reporter.value);
	check( !(it_reporter == users.end()), "No such user on the blockchain.");
	check( !(it_reporter->frozen), "This user is frozen.");
  
  item_t item( _self, _self.value );
	auto it_item = item.find(itemKey);
	check( !(it_item == item.end()), "No such item on the blockchain.");
	check( it_item->reporter == reporter, "Cannot set price for items owned by other users.");
	item.modify(it_item, _self, [&]( auto& row ) { 
	  row.price = price;
	});
}

ACTION reporting::placeorder( name buyer, uint64_t itemKey ) {
	require_auth( buyer );
	auto it_buyer = _users.find(buyer.value);
	check( !(it_buyer == _users.end()) , "Please enrol first." );

	auto it_item = _items.find(itemKey);
	check( !(it_item == _items.end()), "No such item" );
	check( !(it_item->reporter == buyer), "You cannot buy your own item." );
	//check( !(it_item->rating/1000000000 == 0), "This item does not meet quality requirements to be sold." );
	
	//name seller = it_item->reporter;
	//uint64_t price = ;
	
	for(auto& row : _orders) { 
	  check( !(row.itemKey == itemKey && row.buyer == buyer), "That order was already placed." ); 
	}

	_orders.emplace(_self, [&]( auto& row ) { 
	  row.key = _orders.available_primary_key();  
	  row.itemKey = itemKey;
	  row.seller = it_item->reporter;
	  row.buyer = buyer; 
	  row.finished = 0; 
	  row.timestamp = eosio::current_time_point(); 	
	});
	if(it_item->price > 0) {
	  transfer(buyer, it_item->reporter, it_item->price);
	}
}

