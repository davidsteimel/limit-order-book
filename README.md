# High-Frequency Limit Order Book

An optimized C++20 Limit Order Book engine designed for low latency and deterministic memory behavior.
The system utilizes a custom **Object Pool** to eliminate runtime memory allocations (`new`/`delete`).

## Key Features

- **Limit Order Book:** Supports Buy (Bid) and Sell (Ask) orders with _Price-Time Priority_.
- **Zero-Allocation Runtime:** Custom `ObjectPool<T>` allocator prevents heap fragmentation and Garbage Collection pauses during critical execution paths.
- **Continuous Matching:** Implements a Continuous Double Auction mechanism that matches orders immediately upon arrival.
- **Optimized Algorithms:** Uses `std::lower_bound` (Binary Search) for efficient order insertion (O(log n)).
- **High Performance:** Achieves ~2.8 microseconds (µs) "Time-to-Match" on consumer hardware (Apple Silicon).

* **Limit Order Book:** Supports Buy (Bid) and Sell (Ask) orders with _Price-Time Priority_.
* **Zero-Allocation Runtime:** Custom `ObjectPool<T>` allocator prevents heap fragmentation and Garbage Collection pauses.
* **Vector Optimization:** "Flipped" book layout allows for O(1) removal of best orders (`pop_back`).
* **Continuous Matching:** Immediate matching upon order arrival.
* **High Performance:** Achieves **~1.5 microseconds (µs)** "Time-to-Match" on consumer hardware (Apple Silicon).

## Tech Stack

- **Language:** C++20
- **Testing/Benchmarking:** Google Benchmark
- **Compiler:** Clang / GCC
- **Architecture:** Single-threaded event loop (simulated)

## Performance Benchmarks

Measured using Google Benchmark on Apple Silicon (M-Series).

| Benchmark       | Time (CPU)              | Iterations |
| :-------------- | :---------------------  | :--------- |
| **1024 Orders** | **1,482 ns** (~1.48 µs) | 1,000,000  |
| **4096 Orders** | **2,561 ns** (~2.56 µs) | 1,383,864  |
| **8192 Orders** | **2,446 ns** (~2.45 µs) | 1,334,681  |

> **Note:** Latency figures include the overhead of the custom memory pool management and the matching logic itself.

## Build & Run

### Prerequisites

- C++20 compatible compiler (Clang/GCC)
- [Google Benchmark](https://github.com/google/benchmark) (installed via `brew install google-benchmark` or built from source)

### Build and Run Engine

````bash
clang++ -std=c++20 Main.cpp OrderBook.cpp OrderGenerator.cpp -o lob_engine
./lob_engine
