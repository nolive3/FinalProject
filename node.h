#ifndef NODE_H
#define NODE_H
#include "pointer.h"
#include <list>

class Node
{
    public:
        Node();
        Node(const Pointer<Node>& parent);
        void add(Pointer<Node>&child);
        void set_parent(Pointer<Node>& p);
        void add(Node*child);
        void set_parent(Node* p);
    private:
        Pointer<Node> parent;
        std::list<Pointer<Node>> children;
};

#endif // NODE_H
