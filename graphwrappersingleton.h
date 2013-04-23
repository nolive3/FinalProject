#ifndef GRAPHWRAPPERSINGLETON_H
#define GRAPHWRAPPERSINGLETON_H
#include "boost/graph/adjacency_list.hpp"
#include "boost/bimap.hpp"
#include <string>

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
        unsigned int index;
        boost::adjacency_list<boost::listS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, unsigned int>> graph;
        boost::bimap
        <
            boost::adjacency_list
            <
                boost::listS,
                boost::listS
            >::vertex_descriptor,
            void*
        > node_addr_map; // maps from node id to memory address (left) and back (right)
        boost::bimap
        <
            boost::adjacency_list
            <
                boost::listS,
                boost::listS
            >::vertex_descriptor,
            unsigned int
        > node_index_map;
        std::string graph_file_base;
        int graph_num;
        void print_stats();
        void reclaim_memory();
        GraphWrapper();
};

#endif // GRAPHWRAPPERSINGLETON_H
