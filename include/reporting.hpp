#include <eosio/eosio.hpp>
#include <eosio/crypto.hpp>
#include <eosio/time.hpp>
#include <eosio/system.hpp>
#include <eosio/print.hpp>
#include <chrono>

//things are more readable with this namespace
using namespace eosio;
using namespace std;


CONTRACT reporting : public contract {
  public:
    using contract::contract;
     reporting(name receiver, name code, datastream<const char*> ds):
       contract(receiver, code, ds),
      _seed(receiver, receiver.value),
      _items(receiver, receiver.value),
      _voteassign(receiver, receiver.value),
      _orders(receiver, receiver.value),
      _users(receiver, receiver.value),
      _notices(receiver, receiver.value)
      {}
  
 
    ACTION test();
    ACTION init();
    ACTION report(name reporter, string hash, uint64_t price, string title, string description, bool report, bool sale);
    ACTION verify(uint64_t itemKey, name voter, bool accept, uint64_t rating);
    ACTION placeorder( name buyer, uint64_t itemKey );
    ACTION warning(name sender, string content);
    ACTION reassvoter(uint64_t itemKey);
    ACTION keyupload(uint64_t orderno);
    ACTION opendispute(name user, uint64_t orderno);
    ACTION closedispute(name user, uint64_t orderno);
    ACTION finishorder(name user, uint64_t orderno);
    ACTION redeemorder(uint64_t orderno);
    
    ACTION reguser(name user, string publicKey, bool validator, string ipns);
  private:
  
    //private Methods which are only called internal by the smart contract

    int random(const int range);
    void blameintern(name blamer, name blamed, string reason, bool freeze);
    void assignverifier(uint64_t itemKey, uint64_t reward);
    void insertitem(name reporter, string hash, int price, string description, string title, bool sale, bool report);
    void insertorder(name buyer, uint64_t itemKey, bool keyupload);
    void writelog(string logmsg);
    bool usersavail();
    void payvoterescrow(uint64_t itemKey, uint64_t reward);
    void addescrow(name user, uint64_t reward);
    void payescrow(name user, uint64_t reward);
    void transferescrow(name from, name to, uint64_t reward);
    vector<eosio::name> choosverifier(int count, name reporter);


      //a boolean for the init() method
      bool initialized = false;
      int rewardpercent = 10;
      int votercount = 3;
      int redeemperioddays = 7;

      //parameters: These parameters can be altered (or should be considered to) by anyone who deploys this smart contract

      
      //tables: These lines describe the tables/datamodel of the smart contract. This is where the smart contract persists its data.
    TABLE user {
        name              user; 
        uint64_t          balance;
        uint64_t          escrow;
        bool              verifier;
        bool              frozen;
        string            publicKey;
        string            ipns;
        uint64_t          primary_key() const { return user.value; }
    };
    typedef multi_index<"users"_n, user> user_t;
    user_t _users;

    TABLE item {
        uint64_t          key;
        name              reporter;
        string            hash;
        uint64_t          accepts;
        uint64_t          votes;
        uint64_t          rating;
        uint64_t          price;
        uint64_t          reward;
        string            title;
        string            description;
        bool              sale;
        bool              report;
        time_point        timestamp;
        uint64_t          primary_key() const { return key; }
      };
      typedef multi_index<"item"_n, item> item_t;
      item_t _items;

      TABLE voteassign {
        uint64_t              key;
        uint64_t              itemKey;
        name                  voter;
        bool                  done;
        bool                  approved;
        uint64_t              rating;
        time_point            timestamp;
        uint64_t          primary_key() const { return key; }
      };
      typedef multi_index<"voteassign"_n, voteassign> voteassign_t;
      voteassign_t _voteassign;

      TABLE application {
        uint64_t              key;
        uint64_t              itemKey;
        name                    applicant;
        bool              active;
        time_point   timestamp;
          uint64_t          primary_key() const { return key; }
          uint64_t          by_itemKey() const { return itemKey; }
      };
      typedef multi_index<"application"_n, application, indexed_by<"itemkey"_n, const_mem_fun<application, uint64_t, &application::by_itemKey>>> application_t;    

    
    TABLE order {
        uint64_t      key;
        uint64_t      itemKey;
        name          seller;
        name          buyer;
        bool          finished;
        bool          bkeyupload;
        bool          dispute;
        time_point    timestamp;
        uint64_t      primary_key() const { return key; }
    };
    typedef multi_index<"order"_n, order> order_t;
    order_t _orders;

    TABLE notice {
      uint64_t      key;
      name          sender;
      string        content;
      time_point    timestamp;
      uint64_t      primary_key() const { return key; }
    };
    typedef multi_index<"notice"_n, notice> notice_t;
    notice_t _notices; 

    TABLE seed {
      uint64_t  key = 1;
      uint32_t  value = 1;
      uint64_t      primary_key() const { return key; }
    };
    typedef multi_index <"seed"_n, seed> seed_t;
    seed_t _seed;



};

//every ACTION has to be mentioned here to be called from outside of the smart contract
EOSIO_DISPATCH(reporting, (init) (report)(verify)(placeorder)(warning)(reguser)(reassvoter)(keyupload)(opendispute)(closedispute)(finishorder)(test)(redeemorder))
