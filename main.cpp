#include <iostream>
#include "ObjectPool.hpp"
#include "OrderBook.hpp"
#include "OrderGenerator.hpp"
#include "Order.hpp"

int main() {
    ObjectPool<Order> pool(10);
    OrderGenerator gen;
    std::cout << "Created ObjectPool with 10 elements." << std::endl;
    OrderBook book;


    for (std:: size_t i = 0; i < 50; i++){
        Order* memory = pool.allocate();

        if (memory != nullptr) {
            Order data = gen.generate();
            *memory = data;
            std::cout << "Order created: " << data.id 
                      << " Side: " << (int)data.side
                      << " Price: " << data.price 
                      << " Qty: " << data.quantity << std::endl;
            book.addOrder(memory);
            book.match(pool);
        } else {
            std::cout << "Pool is full! Cannot create Order " << i << std::endl;
        }
    }
    return 0;
}
    