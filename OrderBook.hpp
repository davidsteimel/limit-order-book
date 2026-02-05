#pragma once
#include <stack>
#include <iostream>
#include <vector>
#include "Order.hpp"
#include "ObjectPool.hpp"

class OrderBook {
private:
    std::vector<Order*> bids; // Käufer (Sortiert: Höchster Preis zuerst)
    std::vector<Order*> asks; // Verkäufer (Sortiert: Niedrigster Preis zuerst)

public:
    OrderBook();
    void addOrder(Order* order);
    void match(ObjectPool<Order>& pool);
};