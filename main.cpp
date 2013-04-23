#include <iostream>
#include "pointer.h"
#include "graphwrappersingleton.h"
#include "node.h"
#include <new>
#include <functional>


Pointer<Node> oktree(int depth, int bf)
{
    Pointer<Node> node(new(malloc(sizeof(Node))) Node(), nullptr);
    if(depth == 1) return node;
    Pointer<Node> tmp(nullptr);
    for(int i = 0; i < bf; ++i){
        tmp = oktree(depth-1, bf);
        node->add(tmp);
    }
    return node;
}
 
Pointer<Node> badtree(int depth, int bf)
{
    Pointer<Node> node(new(malloc(sizeof(Node))) Node(), nullptr);
    if(depth == 1) return node;
    Pointer<Node> tmp(nullptr);
    badtree(depth-1, bf);
    for(int i = 0; i < bf; ++i){
        tmp = badtree(depth-1, bf);
        node->add(tmp);
    }
    return node;
}

void list_add(Pointer<List<Node>> list, int count, std::function<Pointer<Node>(void)> get_node)
{
    if(count == 0) return;
    list_add(list, count-1, get_node);
    Pointer<Node> t = get_node();
    list->add(t);
}

int main(void)
{{
    Pointer<List<Node>> list(new (malloc(sizeof(List<Node>))) List<Node>, nullptr);
    list_add(list, 5, std::bind(badtree, 2, 2));
}//end main body
//reclaim any remaining memory
GraphWrapper::get().collect();
}
