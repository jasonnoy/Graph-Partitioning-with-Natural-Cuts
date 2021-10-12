#ifndef POOL_ITEM
#define POOL_ITEM

#include "../share/common.h"

class Pool_Item{

public:

	vector< vector<NodeID> > node_clusters;
	set<EdgeID> cut_edges;
	EdgeWeight item_weight;

};


#endif //POOL_ITEM