#include <iostream>
#include "pointer.h"
#include "graphwrappersingleton.h"
int main(void)
{{
    Pointer<int> p(nullptr);
    {
        Pointer<int> pint(new int, nullptr);
        *pint = 7;
        p = pint;
    }
    p = new int;
    std::cout << *p;
}//end main body
//reclaim any remaining memory
GraphWrapper::get().collect();
}
