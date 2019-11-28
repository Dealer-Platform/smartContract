/**
* generates random number
* input: range of available numbers
**/
int reporting::random(const int range) {

  auto seed_iterator = _seed.begin();

  if (seed_iterator == _seed.end()) {
    seed_iterator = _seed.emplace(_self, [&](auto& seed) {
    });
  }
  
  int prime = 65337;
  auto new_seed_value = (seed_iterator->value + current_time_point().sec_since_epoch()) % prime;
  
  _seed.modify(seed_iterator,_self,[&](auto& seed){
    seed.value = new_seed_value;
  });
  
  int random_result = new_seed_value % range;
  return random_result;
}

ACTION reporting::warning(name sender, string content){
		require_auth( sender );


    int pk =  _warning.available_primary_key();
    _warning.emplace(_self, [&]( auto& row ) { 
			row.key = pk;
		  row.sender = sender;
      row.content = content;
       row.timestamp = eosio::current_time_point(); 	
		});

}