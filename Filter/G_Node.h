#ifndef __G_NODE_H__
#define __G_NODE_H__

#include <vector>
#include <map>

using namespace std;

#include "G_Edge.h"
#include "../share/sw_basetypes.h"

class G_Node{

public:

	~G_Node(){
	}
	G_Node(NodeID id): nid(id){
	}

	const NodeID get_id() const{
		return this->nid;
	}

//    const geo_point_t get_geo_info() const{
//        return this->geo_info;
//    }

	vector<G_Edge*> &get_adj_list(){
		return this->adj_list;
	}

private:

	const NodeID nid;
	//map< NodeID, G_Edge* > adj_list;
	vector<G_Edge*> adj_list;
	//NodeSize sz;
};


#endif __G_NODE_H__