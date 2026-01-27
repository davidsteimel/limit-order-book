#pragma once
#include <cstdint>

using OrderID = uint64_t;
using Price = int32_t; 
using Quantity = uint32_t;

enum class Side : uint8_t {
    Buy = 0,
    Sell = 1
};

struct Order {
    OrderID id;
    Price price;
    Quantity quantity;
    Side side;
};
