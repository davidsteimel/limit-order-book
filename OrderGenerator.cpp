#include "OrderGenerator.hpp"
OrderGenerator::OrderGenerator() 
    : engine(std::random_device{}()),
      priceDist(99, 101), 
      quantityDist(1, 100),
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