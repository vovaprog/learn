#ifndef TRIVIAL_ALLOCATOR_H
#define TRIVIAL_ALLOCATOR_H

#include <limits>
#include <stdio.h>

#define PRINT(...) printf(__VA_ARGS__)

static int TrivialAllocatorCounter = 0;

template <class T>
class TrivialAllocator
{
public:
    typedef T        value_type;
    typedef T*       pointer;
    typedef const T* const_pointer;
    typedef T&       reference;
    typedef const T& const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    // rebind allocator to type U
    template <class U>
    struct rebind
    {
        typedef TrivialAllocator<U> other;
    };

    TrivialAllocator(): id(++TrivialAllocatorCounter)
    {
        PRINT("TrivialAllocator::TrivialAllocator()   sizeof(T)=%zu   id=%d\n", sizeof(T), id);
    }

    TrivialAllocator(const TrivialAllocator&): id(++TrivialAllocatorCounter)
    {
        PRINT("TrivialAllocator::TrivialAllocator(const TrivialAllocator&)   sizeof(T)=%zu   id=%d\n", sizeof(T), id);
    }

    template <class U>
    TrivialAllocator(const TrivialAllocator<U>& source): id(++TrivialAllocatorCounter)
    {
        PRINT("TrivialAllocator::TrivialAllocator(const TrivialAllocator<U>&)   sizeof(U)=%zu   sizeof(T)=%zu   sourceId = %d   id=%d\n",
              sizeof(U), sizeof(T), source.id, id);
    }

    ~TrivialAllocator()
    {
        PRINT("TrivialAllocator::~TrivialAllocator()   id=%d\n", id);
    }


    // return address of values
    pointer address(reference value) const
    {
        PRINT("TrivialAllocator::address\n");
        return &value;
    }

    const_pointer address(const_reference value) const
    {
        PRINT("TrivialAllocator::address const\n");
        return &value;
    }

    // return maximum number of elements that can be allocated
    size_type max_size() const
    {
        PRINT("TrivialAllocator::max_size\n");
        return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

    // allocate but don't initialize num elements of type T
    pointer allocate(size_type num, const void* hint = 0)
    {
        PRINT("TrivialAllocator::allocate(num=%zu, hint=%llu, size=%zu, id=%d) ======================\n",
              num, (unsigned long long int)hint, sizeof(T), id);

        return (pointer)(::operator new(num * sizeof(T)));
    }

    // initialize elements of allocated storage p with value value
    void construct(pointer p, const T& value)
    {
        PRINT("TrivialAllocator::construct   id=%d\n", id);

        new((void*)p) T(value);
    }

    // destroy elements of initialized storage p
    void destroy(pointer p)
    {
        PRINT("TrivialAllocator::destroy   id=%d\n", id);

        p->~T();
    }

    // deallocate storage p of deleted elements
    void deallocate(pointer p, size_type num)
    {
        PRINT("TrivialAllocator::deallocate(p=%llu   num=%zu   id=%d)\n", (unsigned long long int)p, num, id);

        ::operator delete((void*)p);
    }

    int id;
};

// return that all specializations of this allocator are interchangeable
template <class T1, class T2>
bool operator==(const TrivialAllocator<T1>&, const TrivialAllocator<T2>&)
{
    PRINT("TrivialAllocator::operator==\n");
    return true;
}

template <class T1, class T2>
bool operator!=(const TrivialAllocator<T1>&, const TrivialAllocator<T2>&)
{
    PRINT("TrivialAllocator::operator!=\n");
    return false;
}

#undef PRINT

#endif // TRIVIAL_ALLOCATOR_H


