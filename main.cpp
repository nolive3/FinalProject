#include <iostream>
#include "pointer.h"

int main(void)
{
    Pointer<int> p(nullptr);
    {
        Pointer<int> pint(new int, nullptr);
        *pint = 7;
        p = pint;
    }
    std::cout << *p;
}
