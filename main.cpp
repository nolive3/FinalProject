#include <iostream>
#include "pointer.h"
#include "graphwrappersingleton.h"
int main(void)
{{
    Pointer<int> p(nullptr);//1 ctor
    {
        Pointer<int> pint(new int, nullptr);//2 ctor
        *pint = 1;
        p = pint;//3 opr=
    }//4 dtor
    std::cout << *p;
    {
        Pointer<int> pint(new int, nullptr);//5 ctor
        *pint = 2;
        p = pint;//6 opr=
    }//7 dtor
    std::cout << *p;
    {
        Pointer<int> pint(new int, nullptr); //8 ctor
        *pint = 3;
        p = pint; //9 opr=
    }//10 dtor
    std::cout << *p;
    {
        Pointer<int> pint(new int, nullptr);
        *pint = 4;
        p = pint;
    }
    std::cout << *p;
    {
        Pointer<int> pint(new int, nullptr);
        *pint = 5;
        p = pint;
    }
    std::cout << *p;
    {
        Pointer<int> pint(new int, nullptr);
        *pint = 6;
        p = pint;
    }
    std::cout << *p;
    {
        Pointer<int> pint(new int, nullptr);
        *pint = 7;
        p = pint;
    }
    std::cout << *p;
}//end main body
//reclaim any remaining memory
GraphWrapper::get().collect();
}
