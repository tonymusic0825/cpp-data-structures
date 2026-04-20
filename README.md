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
└── README.md              # Project documentation