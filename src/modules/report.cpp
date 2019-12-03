
/**
 * Somewhat the core of the smart contract.
 * With this method the user submits a hash of his threat intelligence data and some additional metadata.
 * If the reward is set the user has to pay it by this method. 
 */
ACTION reporting::report(name reporter, string hash, uint64_t price, string title, string description, bool report, bool sale) {
	require_auth( reporter );
	user_t users( _self, _self.value );
	auto it_reporter = users.find(reporter.value);
	check( !(it_reporter == users.end()), "No such user on the blockchain.");
	check( !(it_reporter->frozen), "This user is frozen.");
	

	uint64_t reward = price * rewardpercent / 100;

	users.modify(it_reporter, _self, [&]( auto& row ) { 
	  row.balance = row.balance - (reward * 3); 
	});

	item_t item( _self, _self.value );
	for(auto& row : item) { 
	  check( !(row.hash == hash), "That item was already uploaded." ); 
	}

	uint64_t rowkey = 	item.available_primary_key(); 


//item.available_primary_key();
	item.emplace(_self, [&]( auto& row ) { 
	  row.key =  rowkey;
	  row.reporter = reporter; 
	  row.hash = hash; 
	  row.accepts = 0;
	  row.votes = 0;
	  row.rating = 0; 
	  row.price = price;
	  row.reward = reward;
	  row.title = title;
	  row.description = description;
	  row.sale = sale;
	  row.report = report;
	});
		assignverifier(rowkey, reward);
}