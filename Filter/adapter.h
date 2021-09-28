//
// Created by 骏辉 on 2021/9/27.
//
#include "G_Node.h"
#include "../share/sw_basetypes.h"

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ADAPTER_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ADAPTER_H

G_Edge sw_edge_adapter( link_info_t linkInfo, EdgeID oid, map<NodeID, NodeID> id_map );
G_Node sw_node_adapter( node_info_t nodeInfo, NodeID oid );

#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_ADAPTER_H
