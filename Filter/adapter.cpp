#include "adapter.h"

G_Edge sw_edge_adapter( link_info_t linkInfo ) {
    NodeID id = linkInfo.sw_link_id, source = linkInfo.start_node_id, target = linkInfo.end_node_id;
    G_Edge edge(id, source, target);
    return edge;
}

G_Node sw_node_adapter( node_info_t nodeInfo ) {
    NodeID id = nodeInfo.sw_node_id;
    G_Node node(id);
    return node;
}

//
// Created by 骏辉 on 2021/9/28.
//

