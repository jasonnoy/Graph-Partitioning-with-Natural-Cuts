#include "adapter.h"

G_Edge sw_edge_adapter( link_info_t linkInfo, unsigned int oid, map<NodeID, NodeID> &id_map) {
    NodeID id = linkInfo.sw_link_id, source = id_map[linkInfo.start_node_id], target = id_map[linkInfo.end_node_id];
    G_Edge edge(id, source, target, oid);
    return edge;
}

G_Node sw_node_adapter( node_info_t nodeInfo, unsigned int oid) {
    NodeID id = nodeInfo.sw_node_id;
    G_Node node(id, oid);
    return node;
}

//
// Created by 骏辉 on 2021/9/28.
//

