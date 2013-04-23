#ifndef NODE_H
#define NODE_H
#include "pointer.h"
#include <cstdlib>

template <typename T> 
class List
{
    public:
        List() : head(this), rest(this) {}
        List(const List<T>& o) : head(o.head, this), rest(o.rest, this) {}
        void add(Pointer<T>& child){
		rest = new(malloc(sizeof(List<T>))) List<T>(*this);
		head = Pointer<T>(child, this);
	}
        void add(T* child){
		rest = new(malloc(sizeof(List<T>))) List<T>(*this);
		head = Pointer<T>(child, this);
	}
    private:
        Pointer<T> head;
        Pointer<List<T>> rest;
};


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
        Pointer<List<Node>> children;
};
#endif // NODE_H
