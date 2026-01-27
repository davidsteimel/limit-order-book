#include <iostream>
#include "OrderGenerator.hpp"

std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "Order[" << order.id << "] " 
       << (order.side == Side::Buy ? "BUY " : "SELL ")
       << order.quantity << " @ " << order.price;
    return os;
}

int main() {
    std::cout << "--- High Frequency Order Book Simulation ---" << std::endl;

    OrderGenerator gen;

    for(int i = 0; i < 5; i++) {
        Order o = gen.generate();
        std::cout << o << std::endl; 
    }

    std::cout << "--- Done ---" << std::endl;
    return 0;
}