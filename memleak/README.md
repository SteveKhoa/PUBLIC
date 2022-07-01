
# C++ memory leak detector. :mag: (C++11 and before)

**To use:**

1. Download `memleak.h` from this repository.
2. Put it and your source code in the same folder.
3. Include the header using: `#include "memleak.h"`.

**Features**

1. You can use `check_leak();` at different part of your code.
2. Nested 'check_leak();' is not available.

**:bulb: Functions:**

1. `void check_leak();` : print leakage information.
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
  check_leak();
  
  return 0;
}
```

2. `bool isLeak();` : return boolen value indicating whether the memory is leaked or not.

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
  check_leak();
  
  if (isLeak())
    std::cout << "The memory is leaked!" << std::endl;
  
  return 0;
}
```
Result:
```
---   Leakage Check Result   ---
[0] : [!] Leakage detected!
Total leakage      : 40 bytes.
Memory used        : 40 bytes.
Memory deleted     : 0 bytes
---   Infor                  ---
-> 'new'    : 1 times.
-> 'delete' : 0 times.
```
