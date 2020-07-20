
/**
 * Somewhat the core of the smart contract.
 * With this method the user submits a hash of his threat intelligence data and some additional metadata.
 * If the reward is set the user has to pay it by this method. 
 */
ACTION reporting::report(name reporter, checksum256 hash, uint64_t price, string title, string description, bool report, bool sale) {
	require_auth( reporter );
	auto it_reporter = _users.find(reporter.value);
	check( !(it_reporter == _users.end()), "No such user on the blockchain.");
	check( !(it_reporter->frozen), "This user is frozen.");

    auto _item_index = _items.get_index<name("hash")>();
	auto itr = _item_index.find(hash);
	check( itr == _item_index.end(), "That item was already uploaded." );

	uint64_t reward = price * rewardpercent / 100;

	check(!(it_reporter->balance < (reward * votercount)), "you have insufficient balance for this report");

	_users.modify(it_reporter, _self, [&]( auto& row ) {
		if((row.balance - (reward * votercount)) >= 0){
			row.balance = row.balance - (reward * votercount);
		}else{
			row.balance = 0;
		}
	});

	uint64_t rowkey = 	_items.available_primary_key();

	_items.emplace(_self, [&]( auto& row ) {
	  row.key = rowkey;
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
	  row.timestamp = eosio::current_time_point(); 	
	});
	assignverifier(rowkey, reward);
	
}