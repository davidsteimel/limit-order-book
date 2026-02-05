#include <benchmark/benchmark.h>
#include <vector>
#include "ObjectPool.hpp"
#include "OrderBook.hpp"
#include "OrderGenerator.hpp"

static void BM_OrderMatching(benchmark::State& state) {
    ObjectPool<Order> pool(1000000); 
    OrderBook book;
    OrderGenerator gen;

    std::vector<Order> input_data;
    input_data.reserve(state.range(0)); 
    for(int i = 0; i < state.range(0); ++i) {
        input_data.push_back(gen.generate());
    }

    size_t data_index = 0;

    for (auto _ : state) {
        
        Order* memory = pool.allocate();

        if(memory == nullptr) {
            state.SkipWithError("Pool full during benchmark!");
            break;
        }

        *memory = input_data[data_index % input_data.size()];
        data_index++;
        book.addOrder(memory);
        book.match(pool);
    }
}

BENCHMARK(BM_OrderMatching)->Range(1024, 8<<10);

BENCHMARK_MAIN();