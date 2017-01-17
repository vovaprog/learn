#ifndef BLOCK_ALLOCATOR_H
#define BLOCK_ALLOCATOR_H

#include <limits>
#include <stdio.h>

#define PRINT(...) //printf(__VA_ARGS__)

static int BlockAllocatorCounter = 0;

template <class T, size_t blockSize = 0x400>
class BlockAllocator
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
        typedef BlockAllocator<U> other;
    };

    BlockAllocator(): id(++BlockAllocatorCounter)
    {
        PRINT("BlockAllocator::BlockAllocator()   sizeof(T)=%zu   id=%d\n", sizeof(T), id);
    }

    BlockAllocator(const BlockAllocator&): id(++BlockAllocatorCounter)
    {
        PRINT("BlockAllocator::BlockAllocator(const BlockAllocator&)   sizeof(T)=%zu   id=%d\n", sizeof(T), id);
    }

    template <class U>
    BlockAllocator(const BlockAllocator<U>& source): id(++BlockAllocatorCounter)
    {
        PRINT("BlockAllocator::BlockAllocator(const BlockAllocator<U>&)   sizeof(U)=%zu   sizeof(T)=%zu   sourceId = %d   id=%d\n",
              sizeof(U), sizeof(T), source.id, id);
    }

    ~BlockAllocator()
    {
        PRINT("BlockAllocator::~BlockAllocator()   id=%d\n", id);

        Block *cur = blocks;
        while(cur)
        {
            Block *temp = cur->next;
            delete cur;
            cur = temp;
        }
    }


    // return address of values
    pointer address(reference value) const
    {
        PRINT("BlockAllocator::address\n");
        return &value;
    }

    const_pointer address(const_reference value) const
    {
        PRINT("BlockAllocator::address const\n");
        return &value;
    }

    // return maximum number of elements that can be allocated
    size_type max_size() const
    {
        PRINT("BlockAllocator::max_size\n");
        return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

    // allocate but don't initialize num elements of type T
    pointer allocate(size_type num, const void* hint = 0)
    {
        PRINT("BlockAllocator::allocate(num=%zu, hint=%llu, size=%zu, id=%d) ======================\n",
              num, (unsigned long long int)hint, sizeof(T), id);

        if(freeListHead == nullptr)
        {
            allocateBlock();
        }

        Item *result = freeListHead;
        freeListHead = result->next;

        return reinterpret_cast<pointer>(result->data);
    }

    // initialize elements of allocated storage p with value value
    void construct(pointer p, const T& value)
    {
        PRINT("BlockAllocator::construct   id=%d\n", id);

        new((void*)p) T(value);
    }

    // destroy elements of initialized storage p
    void destroy(pointer p)
    {
        PRINT("BlockAllocator::destroy   id=%d\n", id);

        p->~T();
    }

    // deallocate storage p of deleted elements
    void deallocate(pointer p, size_type num)
    {
        PRINT("BlockAllocator::deallocate(p=%llu   num=%zu   id=%d)\n", (unsigned long long int)p, num, id);

        Item *it = reinterpret_cast<Item*>(p);
        it->next = freeListHead;
        freeListHead = it;
    }

protected:

    void allocateBlock()
    {
        Block *newBlock = new Block();
        newBlock->items[blockSize - 1].next = nullptr;
        for(size_t i=0;i<blockSize -1;++i)
        {
            newBlock->items[i].next = &(newBlock->items[i+1]);
        }
        freeListHead = newBlock->items;
    }

    union Item {
        char data[sizeof(T)];
        Item *next;
    };

    struct Block
    {
        Block *next = nullptr;
        Item items[blockSize];
    };

    Block *blocks = nullptr;
    Item *freeListHead = nullptr;
    int id;
};

// return that all specializations of this allocator are interchangeable
template <class T1, class T2>
bool operator==(const BlockAllocator<T1>&, const BlockAllocator<T2>&)
{
    PRINT("BlockAllocator::operator==\n");
    return true;
}

template <class T1, class T2>
bool operator!=(const BlockAllocator<T1>&, const BlockAllocator<T2>&)
{
    PRINT("BlockAllocator::operator!=\n");
    return false;
}

#undef PRINT

#endif // TRIVIAL_ALLOCATOR_H


