# cpp-data-structures

A collection of low-level data structures implemented from scratch in C++. This repository serves as a personal laboratory for exploring memory management, pointers, and the "Rule of Five."

The primary goal of this project is to understand how fundamental building blocks work under the hood, moving away from high-level abstractions to master systems-level programming.

## Projects Overview

Current implementations include:

### 1. Custom Dynamic Array (`CustomArray`)
A template-based dynamic array implementation similar to `std::vector`.
- **Key Features:** Automatic resizing (doubling capacity), `shrink_to_fit`, `reserve`, and bounds-checked element access.
- **Manual Memory Management:** Implements the full **Rule of Five** (Destructor, Copy Constructor, Copy Assignment, Move Constructor, and Move Assignment).
- **Performance Testing:** Includes a benchmarking suite in `main()` comparing its performance against `std::vector` across millions of operations.

### 2. Doubly Linked List (`DoublyLinkedList`)
A template-based bi-directional linked list.
- **Node Structure:** Custom internal `Node` struct with `prev` and `next` pointers.
- **Iterator Support:** Custom internal `iterator` class allowing for standard traversal and compatibility with range-based loops.
- **Operations:** Efficient `push_front`, `push_back`, `pop_front`, `pop_back`, `insert`, and `erase` operations.
- **Resource Safety:** Uses a private `free_mem()` helper to ensure all nodes are properly deallocated during destruction or reassignment.

### 3. Hash Map (`CustomMap`)
A template-based associative container that maps unique keys to values using **Separate Chaining** for collision resolution. This implementation marks the transition from simple data storage to high-performance data retrieval.
- **Internal Architecture:** An array (vector) of buckets, where each bucket is a linked list storing `KeyValuePair` structs. This utilizes the "Hardcore" pipeline: **Hash** (std::hash) -> **Compress** (modulo) -> **Search** (list traversal).
- **Dynamic Rehash:** Implements a sophisticated `rehash()` function. When the **Load Factor** ($\frac{size}{capacity}$) exceeds the threshold (0.75), the map automatically doubles its internal array and migrates all existing elements. 
- **Move Semantics:** Leveraging the "Rule of Five," the rehash process uses `std::move` to transfer key-value pairs between buckets, avoiding expensive deep copies of complex data types.
- **API Features:**
    - `operator[]`: Implements the standard "access or insert" logic.
    - `at()`: Provides bounds-checked access with `std::out_of_range` exceptions.
    - `erase()`: Handles manual memory management within buckets during node removal.
- **Health Metrics:** Includes methods to monitor the map's "stress level" via `load_factor()` and `max_load_factor()`.

---

## Tech Stack & Environment
- **Language:** C++17 (or higher)
- **Compiler:** GCC/Clang
- **OS:** Fedora Linux
- **Concepts Explored:** Templates, Pointer Arithmetic, Move Semantics, Iterators, and Resource Acquisition Is Initialization (RAII).

## Repository Structure
```text
cpp-data-structures/
├── dynamicArray.cpp       # Dynamic array implementation & benchmarks
├── doublyLinkedList.cpp   # Doubly linked list & iterator implementation
├── hashMap.cpp            # Hash map with separate chaining & rehash logic
└── README.md              # Project documentation
