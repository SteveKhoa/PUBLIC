#ifndef _SIMPLEB
#define _SIMPLEB

#include <chrono>

using std::cout;
using std::endl;

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
    if (constr - destr == 0 && used - deleted == 0)
        return false;
    return true;
}

void checkleak()
{
    cout << "[" << attempt++ << "]"
         << " simpleB: ";

    if (isLeak())
    {
        cout << "Leakage detected. [ Total: " << used - deleted << " bytes | Average: " << (used - deleted) / (constr - destr) << " bytes ]" << endl;
    }
    else
    {
        cout << "No leakage found." << endl;
    }

    used = 0;
    deleted = 0;
    constr = 0;
    destr = 0;
}

class watch // Singleton
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> t_end;

    double t_exec;

    watch(const watch &); // Prevents copy constructor
    watch() {}            // Prevents constructor
public:
    static watch &instance()
    {
        static watch instance;
        return instance;
    }

    static void begin()
    {
        instance().t_exec = 0;
        instance().t_start = std::chrono::high_resolution_clock::now();
    }
    static void end()
    {
        instance().t_end = std::chrono::high_resolution_clock::now();
        instance().t_exec = std::chrono::duration<double>(instance().t_end - instance().t_start).count();

        cout << "[" << attempt++ << "]"
             << " simpleB: ";
        cout << "watch [ " << instance().t_exec * 1000 << " ms"
             << " ]" << endl;
    }
};

watch &stopwatch = watch::instance();

#endif
