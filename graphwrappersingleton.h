#ifndef GRAPHWRAPPERSINGLETON_H
#define GRAPHWRAPPERSINGLETON_H
#include "boost/graph/adjacency_list.hpp"

class GraphWrapper
{
    public:
        static GraphWrapper& get(){
            static GraphWrapper inst;
            return inst;
        }
        void add_node(void*node);
        void add_edge(void*src, void*dst);
        void remove_edge(void*src, void*dst);
        void collect();

        virtual ~GraphWrapper();
        GraphWrapper(const GraphWrapper&) = delete;
        GraphWrapper& operator=(const GraphWrapper&) = delete;
    protected:
    private:
        boost::adjacency_list graph;
        //the map between vertex num and memory address
        GraphWrapper();
};

#endif // GRAPHWRAPPERSINGLETON_H
