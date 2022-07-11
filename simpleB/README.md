
# :abacus: simpleB - simple C++ benchmarking (c++11 and below)

Comprehensive and simple C++ benchmarking functions.

# **How to use**

1. Download `simpleB.h` from this repository.
2. Put it and your source code in the same folder.
3. Include the header using: `#include "simpleB.h"`.

# **Features**

1. Check for memory leakage.
2. Observe execution time.

# ** Functions:**

**1. Check for memory leakage**

1.1 `void checkleak();` : print leakage information.
> We should put our code for testing into a block `{}`, and use this function right after it.
> For example:
```C++
int main()
{
  {
    int *Foo = new int[10];
    char *ptr = new char[17];

    delete Foo;
  }
  checkleak();
  
  return 0;
}
```

**:ledger: Example:**

```C++
#include <iostream>
#include "simpleB.h"

class Object
{
  char* name;
  int size;
public:
  Object() : name(NULL), size(0) {}
  ~Object() {}
};

int main()
{
  {
    int *arr = new int[10];
    Object foo;
  }
  checkleak();
  
  return 0;
}
```
Result:
```
[0] simpleB: Leakage detected. [ Total: 40 bytes | Average: 40 bytes ]
```

**2. Observe execution time**

2.1 `stopwatch.begin();` : begin the stopwatch.
2.2 `stopwatch.end();` : end the stopwatch, and print the time out.

**:ledger: Example:**
```C++
class Object
{
    char *name;
    int size;

public:
    Object() : name(NULL), size(0) {}
    ~Object() {}
};

int main()
{
    stopwatch.begin();
    {
        int *arr = new int[10];
        Object foo;
    }
    stopwatch.end();

    return 0;
}
```
Result:
```
[0] simpleB: watch [ 0.008168 ms ]
```
