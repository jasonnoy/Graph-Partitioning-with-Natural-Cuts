#ifndef _CRP_TYPES_H_
#define _CRP_TYPES_H_

#include "base_def.h"
#include <vector>

using std::pair;
using namespace std;
#define CRP_LEVEL_COUNT 5
#define THREAD_NUM 16
#define CORRECTNESS_THREAD_NUM 32
namespace navi{
    namespace crp 
    {
        using uint64_t = navi::base::uint64_t;
        using uint32_t = navi::base::uint32_t;
        using uint16_t = navi::base::uint16_t;
        using bool_t = navi::base::bool_t;
        using int64_t = navi::base::int64_t;
        typedef uint32_t cell_id_t;
        typedef uint64_t weight_t;
        typedef uint32_t topo_weight_t;
        typedef uint32_t vertex_id_t;
        typedef uint32_t edge_id_t;
        typedef int32_t level_t;
        typedef uint32_t vertex_t;
        typedef pair<vertex_t, vertex_t> edge_t;

        const vertex_id_t INVALID_VERTEX_ID = std::numeric_limits<vertex_id_t>::max();
        const level_t INVALID_LEVEL_ID = 10001;
        const edge_id_t INVALID_EDGE_ID = std::numeric_limits<edge_id_t>::max();
        const weight_t INVALID_WEIGHT = std::numeric_limits<weight_t>::max();
        struct edge_hash {
            size_t operator()(const edge_t &e) const noexcept {
                return size_t(e.first) << 32 | e.second;
            }
        };


        struct path_t {
            weight_t weight;
            std::vector<vertex_id_t> vertices;
        };

        struct crp_edge_attr_t {
            weight_t weight;
            vertex_id_t vertex_id;
        };

        struct crp_compiler_edge_attr_t {
            weight_t weight;
            vertex_id_t vertex_id;
            crp_compiler_edge_attr_t(weight_t w, vertex_id_t v){
                weight = w;
                vertex_id = v;
            }
        };

        struct table_node_t
        {
            vertex_id_t vertex_id = -1;
            vertex_id_t prev_vertex_id = -1;
            weight_t weight = -1;
            table_node_t() = default;
            ~table_node_t() = default;
            table_node_t(vertex_id_t vertex_id_, vertex_id_t prev_vertex_id_, weight_t weight_) : vertex_id(vertex_id_), prev_vertex_id(prev_vertex_id_), weight(weight_) {}
            bool operator<(const table_node_t &other) const
            {
                return weight < other.weight;
            }
            bool operator>(const table_node_t &other) const
            {
                return weight > other.weight;
            }
        };

        struct vertex_compiler_attr_t {
            vertex_id_t vertex_id; // vertex id in crp graph (normal vertex id)
            level_t level;
            cell_id_t cell_id;
            vector<crp_compiler_edge_attr_t> in_edges;
            vector<crp_compiler_edge_attr_t> out_edges;
            vertex_compiler_attr_t() {
                vertex_id = INVALID_VERTEX_ID;
                level = -1;
                cell_id = INVALID_LEVEL_ID;
            }
            vertex_compiler_attr_t (vertex_id_t v, level_t l,cell_id_t c){
                vertex_id = v;
                level = l;
                cell_id = c;
            } 
            vertex_compiler_attr_t (vertex_id_t v, level_t l,cell_id_t c,vector<crp_compiler_edge_attr_t>& in_edge,vector<crp_compiler_edge_attr_t>& out_edge){
                vertex_id = v;
                level = l;
                cell_id = c;
                in_edges.assign(in_edge.begin(),in_edge.end());
                out_edges.assign(out_edge.begin(),out_edge.end());
            } 
        };

        struct crp_vertex_attr_t {
            cell_id_t cell_id[CRP_LEVEL_COUNT];
            uint32_t in_start;
            uint32_t out_start;
        };

        struct crp_overlay_edge_attr_t {
            weight_t weight;
            vertex_id_t vertex_id; //overlay graph id
        };

        struct crp_overlay_vertex_attr_t {
            vertex_id_t vertex_id; //normal crp graph vertex id,not id in  crp overlay graph
            level_t level; //graph partition level
            cell_id_t cell_id; //cell id in this level
            uint32_t in_start;
            uint32_t out_start;
        };

        struct crp_cell_attr_t {
            uint32_t in_vertex_start_id; //normal id
            uint32_t out_vertex_start_id; //normal id
            uint32_t weight_start;
            uint32_t in_start;
            uint32_t out_start;
        };

        struct edge_weight_t
        {
            vertex_id_t s_node_ = -1;
            vertex_id_t e_node_ = -1;
            topo_weight_t weight_ = -1; //注意此处为32位无符号
            edge_weight_t() = default;
            edge_weight_t(vertex_id_t s_node,vertex_id_t e_node,topo_weight_t weight)
            {
                s_node_ = s_node;
                e_node_ = e_node;
                weight_ = weight;
            }
        };

        struct topo_link_head_weight_t
        {
            uint32_t total_topo_link;
            uint32_t max_vertex_id;
            edge_weight_t topo_link_weight;

        };

        template<typename T>
        class Singleton
        {
        public:
            static T* get_instance(){
                static T instance_;
                return &instance_;
            }
            Singleton(const Singleton &) = delete;
            Singleton &operator=(const Singleton &) = delete;
        private:
            Singleton() = default;
            ~Singleton() = default;
        };
        
    }// namespace crp
}//namespace navi
#endif
