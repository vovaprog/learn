#ifndef SIMPLE_ALLOCATOR_H
#define SIMPLE_ALLOCATOR_H

#include <stdio.h>

#include <stdlib.h>

template <typename T>
class SimpleAllocator
{
public:
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef const T *const_pointer;
    typedef const T &const_reference;
    typedef unsigned size_type;
    typedef unsigned difference_type;

    template <typename U>
    struct rebind
    {
      typedef FixedAllocator<U> other;
    };


    pointer allocate(unsigned n)
    {
        printf("\nalloc(%d)\n", n);
      return
        reinterpret_cast<T *>
        (malloc(sizeof(T) * n));
    }

    void deallocate(pointer p, unsigned n)
    {
        printf("\nfree(%d)\n", n);
      free(p);
    }

    void construct(pointer p, const_reference clone)
    {
        printf("ctr\n");
      new (p) T(clone);
    }

    void destroy(pointer p)
    {
        printf("destroy\n");
      p->~T();
    }

    pointer address(reference x) const
    {
      return &x;
    }

    const_pointer address(const_reference x) const
    {
      return &x;
    }

    bool operator==(const FixedAllocator &rhs)
    {
        return true;
    }

    bool operator!=(const FixedAllocator &rhs)
    {
      return !operator==(rhs);
    }
};

#endif
