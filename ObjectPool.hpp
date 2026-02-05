#pragma once
#include <stack>
#include <iostream>
#include <vector>
#include "Order.hpp"

template <typename T>
class ObjectPool {
private:
    std::stack<uint32_t> free_indices;
    std::vector<T> allocated_blocks;
    
public:
    ObjectPool(std::size_t size) {
        allocated_blocks.resize(size);

        for (std:: size_t i = 0; i < size; i++){
            free_indices.push(i);
        } 
    }
    T* allocate(){
        if (free_indices.empty()){
            return nullptr;
        }
        uint32_t index = free_indices.top();
        free_indices.pop();
        return &allocated_blocks[index];
    }
    void deallocate(T* objectPtr) {
        std::size_t index = objectPtr - allocated_blocks.data();
        free_indices.push(index);
    }
};