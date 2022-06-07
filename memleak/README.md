
# C++ memory leak detector.

To use:
1. Download `memleak.h` from this repository.
2. Put it and your source code in the same folder.
3. Include the header using: `#include "memleak.h"`.

**Functions:**

`void leak_print();` : print out the information about possible memory leakage.
> It is recommended to put your code into a block `{}`, and use this function right after it.
> For example:
```C++
{
int *Foo = new int[10];
char *ptr = new char[17];

delete Foo;
}
leak_print();
```

`bool isLeak();` : Check whether if the code is memory-leaked or not.
