#include <iostream>
#include "pointer.h"
#include "graphwrappersingleton.h"
#include "node.h"

Pointer<Node>& tree(int depth, int bf)
{
    Pointer<Node> node(new Node, nullptr);
    Pointer<Node> tmp(nullptr);
    for(int i = 0; i < bf; ++i){
        tmp = tree(depth-1, bf);
        node->add(tmp);
    }
    return node;
}

int main(void)
{{
    Pointer<Node> poop = tree(3, 2);
}//end main body
//reclaim any remaining memory
GraphWrapper::get().collect();
}
