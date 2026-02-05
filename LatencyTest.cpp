#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include "ObjectPool.hpp"
#include "OrderBook.hpp"
#include "OrderGenerator.hpp"

using namespace std::chrono;

int main() {
    // Setup
    const int NUM_ORDERS = 10000;
    ObjectPool<Order> pool(100); 
    OrderBook book;
    OrderGenerator gen;

    std::vector<long long> latencies;
    latencies.reserve(NUM_ORDERS);

    std::cout << "Starting Benchmark with " << NUM_ORDERS << " orders..." << std::endl;

    int successful_orders = 0;

    for(int i = 0; i < NUM_ORDERS; ++i) {
        Order* memory = pool.allocate();
        
        if(memory == nullptr) {
            book.match(pool);
            memory = pool.allocate();
            if (memory == nullptr) continue;
        }
        Order data = gen.generate();
        *memory = data;

        auto start = high_resolution_clock::now();

        book.addOrder(memory);
        book.match(pool);

        auto end = high_resolution_clock::now();

        auto duration = duration_cast<nanoseconds>(end - start).count();
        latencies.push_back(duration);
        successful_orders++;
    }

    // Evaluate
    std::sort(latencies.begin(), latencies.end());

    long long sum = std::accumulate(latencies.begin(), latencies.end(), 0LL);
    double avg = (double)sum / latencies.size();
    long long min = latencies.front();
    long long max = latencies.back();
    long long p50 = latencies[latencies.size() * 0.50];
    long long p99 = latencies[latencies.size() * 0.99];
    long long p999 = latencies[latencies.size() * 0.999];

    std::cout << "\n--- Results: (" << successful_orders << " Orders processed) ---" << std::endl;
    std::cout << "Average Latency: " << avg << " ns" << std::endl;
    std::cout << "Min Latency:     " << min << " ns" << std::endl;
    std::cout << "Max Latency:     " << max << " ns" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "p50 (Median):    " << p50 << " ns" << std::endl;
    std::cout << "p99 (Slow):      " << p99 << " ns" << std::endl;
    std::cout << "p99.9 (Spikes):  " << p999 << " ns" << std::endl;

    return 0;
}