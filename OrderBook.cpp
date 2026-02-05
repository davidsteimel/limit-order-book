#include "OrderBook.hpp"
#include "ObjectPool.hpp"
using namespace std;

OrderBook:: OrderBook()
    :  bids(), asks()
{} 

auto compareBids = [](Order* a, Order* b) {
    return a->price > b->price;
};
auto compareAsks = [](Order* a, Order* b) {
    return a->price < b->price;
};

void OrderBook::addOrder(Order* order) {
    if (order -> side == Side::Buy){
        auto bids_pos = lower_bound(bids.begin(), bids.end(), order, compareBids);
        bids.insert(bids_pos, order);
    } else {
        auto asks_pos = lower_bound(asks.begin(), asks.end(), order, compareAsks);
        asks.insert(asks_pos, order);
    };
}


void OrderBook::match(ObjectPool<Order>& pool) {
    
    while(!bids.empty() && !asks.empty() && bids.front()->price >= asks.front()->price){
        Order* bid = bids.front();
        Order* ask = asks.front();

        uint32_t quantity = std::min(bid->quantity, ask->quantity);
        // std::cout << "Trade: Price: " << ask->price << " Quantity: " << quantity << std::endl;

        /* std::cout << "Found match: Price: " << ask->price 
                  << " Quantity: " << quantity 
                  << " (BidID: " << bid->id << " vs AskID: " << ask->id << ")" 
                  << std::endl; */

        bid->quantity -= quantity;
        ask->quantity -= quantity;

        if(bid->quantity == 0){
            bids.erase(bids.begin()); 
            pool.deallocate(bid);
        }

        if(ask->quantity == 0){
            asks.erase(asks.begin());
            pool.deallocate(ask);
        }
    }
}

