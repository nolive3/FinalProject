#ifndef POINTER_H
#define POINTER_H
#include <utility>
#include "graphwrappersingleton.h"
template <typename T>
class Pointer
{
    public:
        Pointer() = delete;
        Pointer(void* newowner) : target(nullptr), owner(newowner), mem_map(GraphWrapper::get()){
            mem_map.add_edge(owner, target);
            mem_map.collect();
        }
        Pointer(const Pointer& o) : target(o.target), owner(o.owner), mem_map(GraphWrapper::get()){
            mem_map.add_edge(owner, target);
            mem_map.collect();
        };
        Pointer(const Pointer& other, void*newowner) : target(other.target), owner(newowner), mem_map(GraphWrapper::get()){
            // move may be a problem
            mem_map.add_edge(owner, target);
            mem_map.collect();
        }
        Pointer(T* newtarget, void*newowner) : target(newtarget), owner(newowner), mem_map(GraphWrapper::get()){
            mem_map.add_edge(owner, target);
            mem_map.collect();
        }
        Pointer& operator=(const Pointer& other){
            // move may be a problem here too
            mem_map.remove_edge(owner, target);
            target = other.target;
            mem_map.add_edge(owner, target);
            mem_map.collect();
        }
        Pointer& operator=(T* other){
            // move may be a problem here too
            mem_map.remove_edge(owner, target);
            target = other;
            mem_map.add_edge(owner, target);
            mem_map.collect();
        }
        T* operator->(){
            // move may be a problem here too
            return target;
        }
        ~Pointer(){
            mem_map.remove_edge(owner, target);
            mem_map.collect();
        }
        T& operator*(){
            return *target;
        }
    protected:
    private:
        T* target;
        void* owner;
        GraphWrapper &mem_map;
};

#endif // POINTER_H
