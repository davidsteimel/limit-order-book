#pragma once
#include <stack>
#include <iostream>
#include <vector>
#include "Order.hpp"
#include "ObjectPool.hpp"

struct Trade {
    uint32_t bid_id;
    uint32_t ask_id;
    int32_t price;
    uint32_t quantity;

    Trade(uint32_t b, uint32_t a, int32_t p, uint32_t q) 
        : bid_id(b), ask_id(a), price(p), quantity(q) {}
};

class OrderBook {
private:
    std::vector<Order*> bids; // Buyer (sorted: highest price last)
    std::vector<Order*> asks; // Seller (sorted: lowest price last)
    std::vector<Trade> trades;

public:
    OrderBook();
    void addOrder(Order* order);
    void match(ObjectPool<Order>& pool);

    const std::vector<Trade>& getTrades() const { return trades; }
};