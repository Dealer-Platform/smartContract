ACTION reporting::transfer(name from, name to, uint64_t amount) {
	require_auth( from );
	auto it_from = _users.find(from.value); 
	auto it_to = _users.find(to.value);
	
	check( !(it_from == _users.end()), "The sending account does not exist. Please enrol.");
	check( !(it_to == _users.end()), "The receiving account does not exist. Please enrol.");

	check( it_from->balance - amount < it_from->balance , "IntegerOverflow (sender), not enough balance.");
	check( it_to->balance + amount > it_to->balance , "IntegerOverflow (receiver).");

	check( it_from->balance - amount >= 0 , "Sender has not enough token.");
	check( !(it_from == it_to), "You have to send the token to another user.");

	_users.modify(it_from, _self, [&]( auto& row ) { row.balance = row.balance - amount; });
	_users.modify(it_to, _self, [&]( auto& row ) { row.balance = row.balance + amount; });
}