#include "adapter.h"
#include <iostream>

G_Edge sw_edge_adapter( link_info_t linkInfo, EdgeID nid) {
    NodeID oid = linkInfo.sw_link_id, source = (NodeID)linkInfo.start_node_id, target = (NodeID)linkInfo.end_node_id;
//    if (source < 100) {
//        cout<<"id: "<<nid<<" source: "<<source<<" target: "<<target<<endl;
//    }
    G_Edge edge(source, target, nid, oid);
    if (nid == 317855) {
        cout<<"id: "<<nid<<" source: "<<source<<" target: "<<target<<endl;
    }
    if (target == 0) {
        cout<<"target0, source id: "<<source<<endl;
        cout<<"edge source: "<<edge.get_source()<<endl;
    }
    return edge;
}

G_Node sw_node_adapter( node_info_t nodeInfo, unsigned int nid) {
    geo_point_t geo_info = nodeInfo.geo_point;
    G_Node node(nid, geo_info);
    return node;
}

//
// Created by 骏辉 on 2021/9/28.
//

