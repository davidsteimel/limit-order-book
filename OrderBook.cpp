#include "OrderBook.hpp"
#include "ObjectPool.hpp"
using namespace std;

OrderBook:: OrderBook()
    :  bids(), asks()
{} 

auto compareBids = [](Order* a, Order* b) {
    return a->price < b->price;
};
auto compareAsks = [](Order* a, Order* b) {
    return a->price > b->price;
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
    
    while(!bids.empty() && !asks.empty() && bids.back()->price >= asks.back()->price){
        Order* bid = bids.back();
        Order* ask = asks.back();

        uint32_t quantity = std::min(bid->quantity, ask->quantity);
        // std::cout << "Trade: Price: " << ask->price << " Quantity: " << quantity << std::endl;

        /* std::cout << "Found match: Price: " << ask->price 
                  << " Quantity: " << quantity 
                  << " (BidID: " << bid->id << " vs AskID: " << ask->id << ")" 
                  << std::endl; */
        trades.emplace_back(bid->id, ask->id, ask->price, quantity);

        bid->quantity -= quantity;
        ask->quantity -= quantity;

        if(bid->quantity == 0){
            bids.pop_back();
            pool.deallocate(bid);
        }

        if(ask->quantity == 0){
            asks.pop_back();
            pool.deallocate(ask);
        }
    }
}

