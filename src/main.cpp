#include <reporting.hpp>
#include "modules/users.cpp"
#include "modules/report.cpp"
#include "modules/items.cpp"
#include "modules/orders.cpp"
#include "modules/utility.cpp"
#include "modules/verification.cpp"
#include "modules/initialize.cpp"
#include "modules/transactions.cpp"

#include <eosio/system.hpp>



ACTION reporting::test() {

    auto order = _orders.find(1);

//int64_t micro_since_epoch = std::chrono::seconds(order->timestamp);

   // print("Order: ", order->timestamp);

    uint32_t a =  order->timestamp.sec_since_epoch();

uint32_t diff = eosio::current_time_point().sec_since_epoch() - a;


    int period = redeemperioddays *24*60*60;

 print("diff: ",diff);
 print("period: ", diff>period);


}











