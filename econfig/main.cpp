#include <iostream>
#include <string>
#include "memleak.h"

using std::boolalpha;
using std::cout;
using std::endl;

// Mechanism:
//      use isFull() to check whether an orbital is full or not, if yes, then it finds the next orbital, and fill that next orbital.

// Klechkowski's list
std::string path[] =
    {
        "1s", "2s", "2p", "3s", "3p", "4s", "3d",
        "4p", "5s", "4d", "5p", "6s", "4f", "5d",
        "6p", "7s", "5f", "6d", "7p", "8s"};
const int path_size = sizeof(path) / sizeof(std::string);

class orbital
{
protected:
    int shell;
    int cnt;
    char _type;
    int max_cap;

public:
    orbital(int shell) : shell(shell), cnt(0) {}
    ~orbital() {}

    virtual bool isFull()
    {
        if (cnt >= max_cap)
            return true;
        return false;
    }
    virtual std::string what()
    {
        return std::to_string(shell) + _type + std::to_string(cnt);
    }
    bool isEmpty()
    {
        if (cnt <= 0)
            return true;
        return false;
    }
    bool push()
    {
        if (isFull())
            return false;
        ++cnt;
        return true;
    }
    bool pop()
    {
        if (isEmpty())
            return false;
        --cnt;
        return true;
    }
    int getShell() const
    {
        return shell;
    }
    char getType() const
    {
        return _type;
    }
};

class s : public orbital
{
public:
    s(int shell) : orbital(shell)
    {
        max_cap = 2;
        _type = 's';
    }
};

class p : public orbital
{
public:
    p(int shell) : orbital(shell)
    {
        max_cap = 6;
        _type = 'p';
    }
};

class d : public orbital
{
public:
    d(int shell) : orbital(shell)
    {
        max_cap = 10;
        _type = 'd';
    }
};

class f : public orbital
{
public:
    f(int shell) : orbital(shell)
    {
        max_cap = 14;
        _type = 'f';
    }
};

orbital next(const orbital &last)
{
    for (int i = 0; i < path_size - 1; ++i)
    {
        int this_shell = path[i][0] - 48;
        char this_type = path[i][1];
        if (this_shell == last.getShell() && this_type == last.getType())
        {
            int next_shell = path[i + 1][0] - 48;
            char next_type = path[i + 1][1];
            switch (next_type)
            {
            case 's':
            {
                return s(next_shell);
            }
            case 'p':
            {
                return p(next_shell);
            }
            case 'd':
            {
                return d(next_shell);
            }
            case 'f':
            {
                return f(next_shell);
            }
            }
        }
    }

    cout << "Getting next orbital failed!!\n";
    return s(1);
}
/*
orbital prev(const orbital &last)
{
    for (int i = 1; i < path_size; ++i)
    {
        int this_shell = path[i][0] - 48;
        char this_type = path[i][1];
        if (this_shell == last.getShell() && this_type == last.getType())
        {
            int prev_shell = path[i - 1][0] - 48;
            char prev_type = path[i - 1][1];
            switch (path[i - 1][1])
            {
            case 's':
            {
                return s(prev_shell);
            }
            case 'p':
            {
                return p(prev_shell);
            }
            case 'd':
            {
                return d(prev_shell);
            }
            case 'f':
            {
                return f(prev_shell);
            }
            }
        }
    }

    cout << "Getting previous orbital failed!!\n";
    return s(1);
}
*/

// Electron configuration
class e_config
{
    orbital curr;
    std::string seq;

public:
    e_config() : curr(s(1)) {}
    ~e_config() {}

    void set(int z) // the same as adding electron, defined recursively.
    {
        if (z <= 0)
            return;

        add();
        set(z - 1);
    }
    void add() // add electron
    {
        if (curr.isFull())
        {
            if (seq.size() > 0)
                seq.append(" ");
            seq.append(curr.what());
            curr = next(curr);
            curr.push();
            return;
        }

        curr.push();
    }
    std::string what()
    {
        std::string res;
        res.append(seq);
        if (seq.size() > 0)
            res += " ";
        res += curr.what();
        return res;
    }
};

int main()
{
    // Test:
    // Z = 42
    // 1s2 2s2 2p6 3s2 3p6 4s2 3d10 4p6 5s2 4d4
    e_config e;
    e.set(42);
    cout << e.what() << "\n";

    return 0;
}
