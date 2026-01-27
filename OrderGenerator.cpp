#include "OrderGenerator.hpp"
OrderGenerator::OrderGenerator() 
    : engine(std::random_device{}()),
      priceDist(10000, 50000),
      quantityDist(1, 1000),
      sideDist(0, 1),
      nextId(1)
{}

Order OrderGenerator::generate() {
    
    Order newOrder;
    
    newOrder.id = nextId++; 
    newOrder.price = priceDist(engine);
    newOrder.quantity = quantityDist(engine); 

    newOrder.side = (sideDist(engine) == 0) ? Side::Buy : Side::Sell;
    
    return newOrder;
}