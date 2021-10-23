#ifndef A_NODE_H
#define A_NODE_H

#include <vector>
#include <map>

using namespace std;

#include "../Common/common.h"
#include "A_Edge.h"

class A_Node{

public:

	~A_Node(){
	}

    A_Node( NodeID id, NodeSize sz ): nid(id), sz(sz) {
    }

	const NodeID get_id() const{
		return this->nid;
	}

	const NodeSize get_size() const{
		return this->sz;
	}

	vector<A_Edge*>& get_adj_list(){
		return this->adj_list;
	}

private:

	const NodeID nid;
	vector<A_Edge*> adj_list;
	const NodeSize sz;
};


#endif //G_NODE_H