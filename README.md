# Mini Memory Allocator

A simple memory allocator written in C for educational purposes.

This project implements a minimal version of the standard C dynamic memory allocation functions to demonstrate how heap memory management works internally. The implementation focuses on readability and learning rather than performance or production use.

## Features

* Custom `malloc()` implementation
* Custom `free()` implementation
* `free_all()` helper for resetting the allocator
* Custom `calloc()` implementation with overflow protection
* Custom `realloc()` implementation
* Heap management using `brk`/`sbrk`
* Block metadata management
* Memory reuse through free block tracking

## Learning Objectives

This project explores the core concepts behind dynamic memory allocation, including:

* Heap memory management
* The `brk` and `sbrk` system calls
* Block metadata design
* Free block management
* Memory allocation strategies
* Memory deallocation
* Zero-initialized allocations
* Integer overflow detection using `SIZE_MAX`
* Memory resizing with `realloc()`
* Data copying between memory blocks
* Common causes of segmentation faults in memory allocators

## Requirements

* Linux
* GCC or Clang compiler
* POSIX-compatible environment

## Building

```bash
make
```

## Running

```bash
./mini_alloc
```

## Example

```c
void *ptr = mini_malloc(128);

ptr = mini_realloc(ptr, 256);

mini_free(ptr);

mini_free_all();
```

## Project Status

Current functionality includes:

* ✅ `malloc()`
* ✅ `free()`
* ✅ `free_all()`
* ✅ `calloc()`
* ✅ `realloc()`

Future improvements may include:

* Block splitting
* Block coalescing
* Alignment optimizations
* Thread safety
* `mmap()` support for large allocations

## Purpose

The goal of this project is to understand how dynamic memory allocation works by implementing a simple allocator from scratch. Rather than relying on the C standard library, the project demonstrates the low-level mechanisms used to manage heap memory and highlights the design decisions behind `malloc`, `free`, `calloc`, and `realloc`.

## Related Video Series

This repository accompanies a YouTube series that develops the allocator step by step, explaining each component and the underlying concepts in detail.
https://www.youtube.com/playlist?list=PLLQuH0euTVZNwQXkUfMpujyaliTUFz4HS
## License

Released under the MIT License.

