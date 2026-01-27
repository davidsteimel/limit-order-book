#pragma once
#include <random>
#include "Order.hpp"

class OrderGenerator
{
private:
    std::mt19937 engine;
    std::uniform_int_distribution<Price> priceDist;
    std::uniform_int_distribution<Quantity> quantityDist;
    std::uniform_int_distribution<uint16_t> sideDist;
    OrderID nextId;

public:
    OrderGenerator();
    Order generate();
};