#include <boost/graph/graphviz.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <boost/graph/breadth_first_search.hpp>
#include "graphwrappersingleton.h"

typedef boost::adjacency_list<boost::listS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, unsigned int>> graph_type;
typedef graph_type::vertex_descriptor vert_type;


typedef boost::bimap<vert_type, void *> bimap_type;
typedef bimap_type::value_type bimap_val;
typedef boost::bimap<vert_type, unsigned int> indexmap_type;
typedef indexmap_type::value_type indexmap_val;

template <typename L, typename R>
bool lcontains(const L& val, const boost::bimap<L,R>& bmap)
{
    return bmap.left.count(val) != 0;
}
template <typename L, typename R>
bool rcontains(const R& val, const boost::bimap<L,R>& bmap)
{
    return bmap.right.count(val) != 0;
}


GraphWrapper::GraphWrapper() : index(0), graph(), node_addr_map(), node_index_map(), graph_file_base("map"), graph_num(1)
{
    std::cerr << "Calling " << "ctor" << std::endl;
    // the node representing main is required for all algorithms, so dont risk it not existing when reclaim_memory() is called
    add_node(nullptr);
}

GraphWrapper::~GraphWrapper()
{
    std::cerr << "Calling " << "dtor" << std::endl;
    std::cerr << "Nodes still in system at end: " << std::endl;
    for(auto i : node_addr_map.left){
        std::cerr << i.first << " " << i.second << std::endl;
    }
}
void GraphWrapper::add_node(void*node){
    std::cerr << "Calling " << "add_node" << node << std::endl;
    const vert_type& v = boost::add_vertex(graph);
    node_addr_map.insert(bimap_val(v, node));
    node_index_map.insert(indexmap_val(v, index));
    boost::put(boost::get(boost::vertex_index, graph), v, index);
    ++index;
}
void GraphWrapper::add_edge(void*src, void*dst){
    std::cerr << "Calling " << "add_edge" << src  << "  "  << dst;
    if(dst==nullptr) return;
    if(!rcontains(src,node_addr_map)){
        add_node(src);
    }
    if(!rcontains(dst,node_addr_map)){
        add_node(dst);
    }
    std::cerr << "adding edge " << node_addr_map.right.at(src) << "-->" << node_addr_map.right.at(dst) << std::endl;
    boost::add_edge(node_addr_map.right.at(src), node_addr_map.right.at(dst), graph);
}
void GraphWrapper::remove_edge(void*src, void*dst){
    std::cerr << "Calling " << "remove_edge" << src  << "  "  << dst << std::endl;
    if(dst==nullptr) return;
    //we know the edge has to exist since it was inserted
    //during the constructor and now the destructor is deleting it
    //otherwise we would need to check second, not just first of edge
    boost::remove_edge(boost::edge(node_addr_map.right.at(src), node_addr_map.right.at(dst), graph).first, graph);
}
void GraphWrapper::collect()
{

    std::cerr << std::endl << std::endl;
    std::cerr << "Calling " << "collect" << std::endl;
    print_stats();
    reclaim_memory();
    //print_stats();
    std::cerr << std::endl << std::endl;
}

class bfs_visited_visitor:public boost::default_bfs_visitor {
private:
    std::unordered_set<vert_type>& vis_set;
public:
    bfs_visited_visitor(std::unordered_set<vert_type>& target_list):vis_set(target_list) { }
    template < typename Vertex, typename Graph >
    void discover_vertex(Vertex u, const Graph & g) const
    {
    std::cerr << "Calling " << "discover " << u << std::endl;
    vis_set.insert(u);
    }
    /* This wuz debugging
    template < typename Edge, typename Graph >
    void examine_edge(Edge e, Graph g) const
    {
        std::cerr << "Examining edge: " << boost::source(e, g) <<"-->"<<boost::target(e, g)<<std::endl;
    }
    template < typename Vertex, typename Graph >
    void initialize_vertex(Vertex u, const Graph & g) const
    {
    std::cerr << "Calling " << "initialize " << u << std::endl;
    }
    template < typename Vertex, typename Graph >
    void examine_vertex(Vertex u, const Graph & g) const
    {
    std::cerr << "Calling " << "examine " << u << std::endl;
    }
    template < typename Vertex, typename Graph >
    void finish_vertex(Vertex u, const Graph & g) const
    {
    std::cerr << "Calling " << "finish " << u << std::endl;
    }
    template < typename Edge, typename Graph >
    void grey_target(Edge e, Graph g) const
    {
        std::cerr << "Ignoring grey edge: " << boost::source(e, g) <<"-->"<<boost::target(e, g)<<std::endl;
    }
    template < typename Edge, typename Graph >
    void black_target(Edge e, Graph g) const
    {
        std::cerr << "Ignoring black edge: " << boost::source(e, g) <<"-->"<<boost::target(e, g)<<std::endl;
    }
    template < typename Edge, typename Graph >
    void tree_edge(Edge e, Graph g) const
    {
        std::cerr << "Tree edge: " << boost::source(e, g) <<"-->"<<boost::target(e, g)<<std::endl;
    }
    template < typename Edge, typename Graph >
    void non_tree_edge(Edge e, Graph g) const
    {
        std::cerr << "Non-Tree edge: " << boost::source(e, g) <<"-->"<<boost::target(e, g)<<std::endl;
    }
    */
};

void GraphWrapper::print_stats()
{
    std::stringstream s;
    s<<graph_file_base<<(graph_num++)<<".dot";
    std::ofstream ofile(s.str());
    auto e = boost::edges(graph);
    std::cerr<<"edges:"<< std::endl;
    for_each(e.first, e.second, [&](const graph_type::edge_descriptor& edge){
        std::cerr << boost::source(edge, graph) <<"-->"<<boost::target(edge, graph)<<std::endl;
    });
    std::cerr << "Nodes in system at now: " <<s.str()<< std::endl;
    for(auto i : node_addr_map.left){
        std::cerr << i.first << " " << i.second << std::endl;
    }
    write_graphviz(ofile, graph);
}
void GraphWrapper::reclaim_memory()
{
    std::unordered_set<vert_type> reachable_set;
    std::unordered_set<vert_type> unreachable_set;
    bfs_visited_visitor vis(reachable_set);
    vert_type main_vert(node_addr_map.right.at(nullptr));
    boost::breadth_first_search(graph, main_vert, boost::visitor(vis));
    std::for_each(std::begin(node_addr_map), std::end(node_addr_map), [&](const bimap_val& vert){
        if(reachable_set.count(vert.left) == 0){
            unreachable_set.insert(vert.left);
        }
    });
    std::for_each(std::begin(unreachable_set), std::end(unreachable_set), [&](const vert_type& vert){
                  std::cerr << "deleting node " << node_addr_map.left.at(vert) << " id " << vert << " at index " << node_index_map.left.at(vert) << std::endl;
        boost::clear_vertex(vert, graph);
        boost::remove_vertex(vert, graph);
        delete node_addr_map.left.at(vert);
        node_addr_map.erase(bimap_val(vert, node_addr_map.left.at(vert)));
        unsigned int idx = node_index_map.left.at(vert);
        node_index_map.erase(indexmap_val(vert, idx));
        --index;
        if(idx!=index){
            vert_type v = node_index_map.right.at(index); //move the last node to the newly freed index
            node_index_map.erase(indexmap_val(v, index)); // remove it from the map
            node_index_map.insert(indexmap_val(v, idx)); // put it back with its new index
            boost::put(boost::get(boost::vertex_index, graph), v, idx); //update the index in the graph
        }

    });
}
