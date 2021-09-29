#include "adapter.h"
#include <iostream>

G_Edge sw_edge_adapter( link_info_t linkInfo, EdgeID nid) {
    NodeID oid = linkInfo.sw_link_id, source = linkInfo.start_node_id, target = linkInfo.end_node_id;
    if (nid < 100) {
        cout<<"id: "<<nid<<" source: "<<source<<" target: "<<target<<endl;
    }
    G_Edge edge(source, target, nid, oid);
    return edge;
}

G_Node sw_node_adapter( node_info_t nodeInfo, unsigned int nid) {
    NodeID oid = nodeInfo.sw_node_id;
    G_Node node(nid, oid);
    return node;
}

//
// Created by 骏辉 on 2021/9/28.
//

