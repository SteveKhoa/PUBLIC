
# C++ memory leak detector. :mag: (C++11 and before)

**To use:**

1. Download `memleak.h` from this repository.
2. Put it and your source code in the same folder.
3. Include the header using: `#include "memleak.h"`.

**:bulb: Functions:**

`void leak_print();` : print leakage information.
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
  leak_print();
  
  return 0;
}
```

`bool isLeak();` : return boolen value indicating whether the memory is leaked or not.

**:ledger: Example:**

```C++
#include <iostream>
#include "memleak.h"

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
  leak_print();
  
  if (isLeak())
    std::cout << "The memory is leaked!" << std::endl;
  
  return 0;
}
```
Result:
```
--- Leakage Check Result ---
[0] : Memory leakage detected!
Total leakage      : 40 bytes.
-> Called 'new'    : 1 times.
-> Called 'delete' : 0 times.
```
