#ifndef _LEAK_DETECTOR
#define _LEAK_DETECTOR

// https://github.com/SteveKhoa/PUBLIC/edit/main/memleak/memleak.h

size_t used = 0;
size_t deleted = 0;

size_t constr = 0;
size_t destr = 0;

unsigned int attempt = 0;

void *operator new(size_t size) throw(std::bad_alloc)
{
    ++constr;
    used += size;
    size_t *ptr = (size_t *)malloc(sizeof(size_t) + size);
    ptr[0] = size;
    return (void *)&ptr[1];
}

void operator delete(void *ptr) throw()
{
    ++destr;
    deleted += ((size_t *)ptr)[-1];

    free(&(((size_t *)ptr)[-1]));
}

bool isLeak()
{
    if (constr - destr > 0)
        return true;

    return false;
}

void leak_print()
{
    std::cout << "--- Leakage Check Result ---\n";
    std::cout << "[" << attempt++ << "] : ";
    if (isLeak())
    {
        std::cout << "Memory leakage detected!"
                  << "\n";
        std::cout << "Total leakage      : " << used - deleted << " bytes."
                  << "\n";
        std::cout << "-> Called 'new'    : " << constr << " times."
                  << "\n";
        std::cout << "-> Called 'delete' : " << destr << " times."
                  << "\n";
    }
    else
    {
        std::cout << "No leakage found."
                  << "\n";
    }

    used = 0;
    deleted = 0;
    constr = 0;
    destr = 0;
}
#endif
