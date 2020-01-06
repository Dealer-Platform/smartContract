ACTION reporting::keyupload(uint64_t orderno){
    auto it_order = _orders.find(orderno);

    require_auth( it_order->seller);


    _orders.modify(it_order, _self, [&]( auto& row ) { 
		row.bkeyupload = true;
	});

}
//download failed -> open dispute
ACTION reporting::opendispute(name user, uint64_t orderno){
    auto it_order = _orders.find(orderno);
    require_auth( it_order->buyer);

    _orders.modify(it_order, _self, [&]( auto& row ) { 
		  row.dispute = true;
	});

}

//temporarily close dispute (try next download)
ACTION reporting::closedispute(name user, uint64_t orderno){
    auto it_order = _orders.find(orderno);
    require_auth( it_order->buyer);

    _orders.modify(it_order, _self, [&]( auto& row ) { 
		  row.dispute = false;
	});

}


//redeem order that has not been finished after a fixed timeperiod
ACTION reporting::redeemorder(uint64_t orderno){
    auto order = _orders.find(orderno);
    auto item = _items.find(order->itemKey);

    int32_t orderdate =  order->timestamp.sec_since_epoch();
    uint32_t diff = eosio::current_time_point().sec_since_epoch() - orderdate;

    int orderperiod = redeemperioddays *24*60*60;


    if(orderperiod > diff && order->finished == 0){

    _orders.modify(order, _self, [&]( auto& row ) { 
		  row.dispute = true;
          row.finished = true;
          row.timestamp = eosio::current_time_point(); 	
	});

    int reward = item->price;

    _users.modify(_users.find(order->seller.value), _self, [&]( auto& row ) { 
			row.escrow = row.escrow - reward;
		});
   
    _users.modify(_users.find(order->buyer.value), _self, [&]( auto& row ) { 
			row.balance = row.balance + reward;
		});
    
    }

}

//redeem order that is not confirmed by the buyer
ACTION reporting::sellredeem(uint64_t orderno){
    auto order = _orders.find(orderno);
    auto item = _items.find(order->itemKey);

    int32_t orderdate =  order->timestamp.sec_since_epoch();
    uint32_t diff = eosio::current_time_point().sec_since_epoch() - orderdate;

    int orderperiod = redeemperioddays *24*60*60;


    if(orderperiod > diff && order->finished == 0){

    _orders.modify(order, _self, [&]( auto& row ) { 
		  row.dispute = true;
          row.finished = true;
          row.timestamp = eosio::current_time_point(); 	
	});

    int reward = item->price;

    _users.modify(_users.find(order->seller.value), _self, [&]( auto& row ) { 
			row.escrow = row.escrow - reward;
            row.balance = row.balance + reward;
		});
    
    }

}



//download succeeded, remove dispute, finish order, release escrow
ACTION reporting::finishorder(name user, uint64_t orderno){
    auto it_order = _orders.find(orderno);
    require_auth( it_order->buyer);

    auto it_item = _items.find(it_order->itemKey);

    _orders.modify(it_order, _self, [&]( auto& row ) { 
		  row.dispute = false;
          row.finished = true;
          row.timestamp = eosio::current_time_point(); 	
	});

    payescrow(it_order->seller, it_item->price);

}