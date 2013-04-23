#include <iostream>
#include "pointer.h"
#include "graphwrappersingleton.h"
#include "node.h"
#include <new>
 
Pointer<Node> tree(int depth, int bf)
{
    Pointer<Node> node(new(malloc(sizeof(Node))) Node(), nullptr);
    if(depth == 1) return node;
    Pointer<Node> tmp(nullptr);
    tree(depth-1, bf);
    for(int i = 0; i < bf; ++i){
        tmp = tree(depth-1, bf);
        node->add(tmp);
    }
    return node;
}

int main(void)
{{
    Pointer<Node> test = tree(6, 3);
}//end main body
//reclaim any remaining memory
GraphWrapper::get().collect();
}
