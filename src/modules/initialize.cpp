/**
 * Initializes database
 */

ACTION reporting::init() {
  	int usercount = 0;
	for(auto& row : _users) { 
		usercount++;
	}

	if(usercount == 0){
	reguser("peter"_n, "",true);
    reguser("emma"_n, "",true);
    reguser("isabelle"_n, "",true);
    reguser("validator1"_n, "",true);
    reguser("validator2"_n, "",true);
	reguser("validator3"_n, "",true);
	}

	
	//insertitem("peter"_n, "7c4975cc7c57023b9911c84274be358fd17e92f7598f8a524da5557359dbee80", 12, "a very nice incident over here", "incident1", true, true);
	//insertitem("emma"_n, "7c4975cc7c57aa3b9911c84274be358fd17e9bbb598f8a524da5557359dbee80", 14, "another incident", "incident2", true, true);

	/*_orders.emplace(_self, [&]( auto& row ) { 
	  row.key = _orders.available_primary_key();  
	  row.itemKey = 1;
	  row.seller = "peter"_n;
	  row.buyer = "emma"_n; 
	  row.finished = 0; 
	  row.timestamp = eosio::current_time_point(); 	
	});
*/
}

void reporting::insertitem(name reporter, string hash, int price, string description, string title, bool sale, bool report){
	require_auth( _self );

		int pk =  _items.available_primary_key();

		_items.emplace(_self, [&]( auto& row ) { 
			row.key = pk;
			row.reporter = reporter;
			row.hash = hash;
			row.price = price;
			row.description = description;
			row.title = title;
			row.sale = sale;
			row.report = report;
		});

	assignverifier(pk);

}


