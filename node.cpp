#include "node.h"
Node::Node() : parent(this), children(new (malloc(sizeof(List<Node>))) List<Node>(), this)
{

}

Node::Node(const Pointer<Node>&p) : parent(p, this), children(new (malloc(sizeof(List<Node>))) List<Node>(), this)
{

}

void Node::add(Pointer<Node>& child) 
{
    Pointer<Node> copy = Pointer<Node>(child, this);
    children->add(copy);
    copy->set_parent(this);
}

void Node::add(Node * child)
{
    Pointer<Node> copy = Pointer<Node>(child, this);
    children->add(copy);
    copy->set_parent(this);
}

void Node::set_parent(Pointer<Node>& p)
{
    parent = p;
}


void Node::set_parent(Node* p)
{
    parent = p;
}
