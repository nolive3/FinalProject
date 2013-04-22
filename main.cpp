#include <iostream>
#include "pointer.h"
#include "graphwrappersingleton.h"
#include "node.h"

Pointer<Node> tree(int depth, int bf)
{
    if(depth == 1) return Pointer<Node>(new Node, nullptr);
    Pointer<Node> node(new Node, nullptr);
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
    Pointer<Node> poop = tree(4, 2);
}//end main body
//reclaim any remaining memory
GraphWrapper::get().collect();
}
