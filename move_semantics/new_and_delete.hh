#pragma once

auto end_block = "\n\n";

inline int& heap_allocations ()
{
    static int allocations_ = 0;
    return allocations_;
}

inline void reset_heap_allocations ()
{
    heap_allocations() = 0;
}


void* operator new (std::size_t size)
{
    ++heap_allocations();
    return malloc(size);
}

void* operator new[] (std::size_t size)
{
    ++heap_allocations();
    return malloc(size);
}

void operator delete (void* ptr) noexcept
{
    free(ptr);
}

void operator delete[] (void* ptr) noexcept
{
    free(ptr);
}
