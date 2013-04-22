#include "node.h"
Node::Node() : parent(this), children()
{

}

Node::Node(const Pointer<Node>&p) : parent(p, this), children()
{

}

void Node::add(Pointer<Node>& child)
{
    children.emplace_front(child, this);
    child->set_parent(this);
}

void Node::add(Node * child)
{
    children.emplace_front(child, this);
    child->set_parent(this);
}

void Node::set_parent(Pointer<Node>& p)
{
    parent = p;
}


void Node::set_parent(Node* p)
{
    parent = p;
}
